#include "recherche_motif.h"

enum types { L, A, I, S, AUTRE };

// L+A*I+AS
// L+AI+A?I*S



int ttransit[NBETATS][NBTYPES] = {{1, 0, 0, 0, 0},
                                  {1, 2, 3, 0, 0},
                                  {1, 2, 3, 0, 0},
                                  {1, 4, 3, 0, 0},
                                  {1, 0, 0, 10, 0}};



int ttransit_2[NBETATS_2][NBTYPES] = {
					/* etat 0 */	  { 1, 0, 0, 0, 0} ,
			    /* etat 1*/	   { 1, 2, 0, 0, 0},
					/* etats 2*/	{ 1, 0, 3, 0,0},
					/* etat 3*/		 {1, 4, 3, 6 ,0},
					/* etat 4*/	{1, 0, 5, 6 ,0},
					/*etat 5 */	{1, 0, 5, 6 ,0}};



int debut_1[MAX];
int fin_1[MAX];
int debut_1[MAX];
int fin_1[MAX];

char *strdup(const char *s) {
    char *d = malloc(strlen(s) + 1);
    if (d == NULL) return NULL;
    strcpy(d, s);
    return d;
}




void afficher_motifs(char *tableau, int *debut, int *fin, int nb_motif) {
    printf("Occ [pos pts]\n");
    printf("-------------------------\n");

    for (int i = 0; i < nb_motif; i++) {
        
        char motif[MAX_MOTIFS];
        snprintf(motif, fin[i] - debut[i] + 1, "%s", &tableau[debut[i]]);
        
       
        int points = 0;
        for (int j = debut[i]; j < fin[i]; j++) {
            switch (tableau[j]) {
                case 'A':
                    points += 1;
                    break;
                case 'I':
                    points += 3;
                    break;
                case 'L':
                    points += 15;
                    break;
                case 'S':
                    points += 21;
                    break;
                default:
                    break;
            }
        }

        
        bool point_deja_existant = false;
        for (int k = 0; k < unique_points_count; k++) {
            if (tableau_point_unique[k] == points) {
                point_deja_existant = true;
                break;
            }
        }

        
        if (!point_deja_existant) {
            tableau_point_unique[unique_points_count] = points;
            unique_points_count++;
        }

        
        printf("%s [ %d %d]\n", motif, debut[i], points);
    }

    
    printf("%d occ du motif trouvees\n", nb_motif);
}



int automate(char *tableau, int *debut, int *fin) {
  int nb_motif = 0;
  int etat = ETATENTREE;
  int premier_indice = 0;
  int total_points = 0;

  for (int i = 0; tableau[i] != '\0'; i++) {
    int etat_pre = etat;
    enum types t = get_type(tableau[i]);
    etat = ttransit[etat][t];
    if (etat_pre != 1 && etat == 1) {
      premier_indice = i;
      // printf("test, %c, i: %d \n", tableau[i], i);
    }
    if (etat == ETATSORTIE) {
      
      int points = 0;
      for (int j = premier_indice; j <= i; j++) {
        switch (tableau[j]) {
          case 'A':
            points += 1;
            break;
          case 'I':
            points += 3;
            break;
          case 'L':
            points += 15;
            break;
          case 'S':
            points += 21;
            break;
          default:
            break;
        }
      }

      
      debut[nb_motif] = premier_indice;
      fin[nb_motif] = i + 1;
      nb_motif++;

      /* printf("\tPattern found: %.*s at index %d with length %d and %d points, %d énieme ""motif\n",
          i - premier_indice + 1, &tableau[premier_indice], premier_indice,
          i - premier_indice, points, nb_motif); */
      
      total_points += points; 
      etat = ETATENTREE;
    }
  }
  // printf("Total points: %d\n", total_points); // Print the total points
  return nb_motif;
}



int automate_2(char *tableau, int *debut, int *fin) {
  int nb_motif = 0;
  int etat = ETATENTREE;
  int premier_indice = 0;
  int total_points = 0; // Variable to store the total points

  for (int i = 0; tableau[i] != '\0'; i++) {
    int etat_pre = etat;
    enum types t = get_type(tableau[i]);
    etat = ttransit_2[etat][t];
    if (etat_pre != 1 && etat == 1) {
      premier_indice = i;
      // printf("test, %c, i: %d \n", tableau[i], i);
    }
    if (etat == ETATSORTIE_2) {
      
      int points = 0;
      for (int j = premier_indice; j <= i; j++) {
        switch (tableau[j]) {
          case 'A':
            points += 1;
            break;
          case 'I':
            points += 3;
            break;
          case 'L':
            points += 15;
            break;
          case 'S':
            points += 21;
            break;
          default:
            break;
        }
      }

      // Store the match details
      debut[nb_motif] = premier_indice;
      fin[nb_motif] = i + 1;
      nb_motif++;

      /* printf(
          " \tPattern found: %.*s at index %d with length %d and %d points, %d énieme "
          "motif\n",
          i - premier_indice + 1, &tableau[premier_indice], premier_indice,
          i - premier_indice, points, nb_motif); */
      
      total_points += points; // Update the total points

      etat = ETATENTREE;
    }
  }
  // printf("Total points: %d\n", total_points); 
  return nb_motif;
}




void print_typ(char *s) {
  while (*s != '\0') {
    printf("%c  %d\n", *s, get_type(*s));
    s++;
  }
}

enum types get_type(char l) {
  switch (l) {
    case 'L':
      return L;
    case 'A':
      return A;
    case 'I':
      return I;
    case 'S':
      return S;
    default:
      return AUTRE;
  }
}




void affiche_ttransit(int tab[NBETATS][NBTYPES]) {
  printf("ETAT | L  | A  | I  | S  | AUTRE\n");
  for (int i = 0; i < NBETATS; i++) {
    printf("  %2d | ", i);
    for (int j = 0; j < NBTYPES; j++) {
      printf("%2d | ", tab[i][j]);
    }
    printf("\n");
  }
  printf("\n");
}


void affiche_ttransit_2(int tab[NBETATS_2][NBTYPES]) {
  printf("ETAT | L  | A  | I  | S  | AUTRE\n");
  for (int i = 0; i < NBETATS; i++) {
    printf("  %2d | ", i);
    for (int j = 0; j < NBTYPES; j++) {
      printf("%2d | ", tab[i][j]);
    }
    printf("\n");
  }
  printf("\n");
}

