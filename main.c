#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "alphabet.c"
#include "recherche_motif.c"
#include "freel-liste.h"
#include "hashcode.h"

#include <stdbool.h>




char tableau[130000];
//char tableau[] = "LIASLLLLAIAISLLLIASLIASLIASLLLLLLLAIAISLAIIIISLIIIIIASLIASLAIIIIIIIISLAIAISLAIAIS";
// char tableau[] = "LIASLAIS";

int taille_tab = sizeof(tableau) / sizeof(tableau[0]);
char motif[20];


void print_occurrences_with_nb();
void print_occurrences_with_nb_croissant();
float calculer_nombre_moyen_points_par_occurrence();



int main(void) {
  


   remplirTableau(tableau, taille_tab);
    printf("Alphabet : LAIS \nMotif 1 : L+A*I+AS \nMotif 2 : L+AI+A?I*S\n");
    printf("Tableau : de %d caractères \n", taille_tab);
    for (int i = 0; i < taille_tab; ++i) {
        printf("%c", tableau[i]);
    }
    printf("\n");

    //affiche_ttransit(ttransit);

    // Déclarer et initialiser les tableaux pour stocker les motifs
    int debut_1[MAX_MOTIFS], fin_1[MAX_MOTIFS];
    int debut_2[MAX_MOTIFS], find_2[MAX_MOTIFS];

    // Appel de la fonction pour détecter les occurrences du motif 1
    int match_count_1 = automate(tableau, debut_1, fin_1);
    if (match_count_1 == 0) {
        printf("Aucun motif trouvé pour le motif 1\n");
    }

    // Affichage des motifs uniques pour le motif 1
    printf("Affichage table des occurrences du motif 1 :\n");
    afficher_motifs(tableau, debut_1, fin_1, match_count_1);

   // affiche_ttransit_2(ttransit_2);

    // Appel de la fonction pour détecter les occurrences du motif 2
    int match_count_2 = automate_2(tableau, debut_2, find_2);
    if (match_count_2 == 0) {
        printf("Aucun motif trouvé pour le motif 2\n");
    }

    // Affichage des motifs uniques pour le motif 2
    printf("Affichage table des occurrences du motif 2:\n");
    afficher_motifs(tableau,debut_2, find_2, match_count_2);


    

    init_freeliste();
  init_tabhash(); 

// Ajouter les motifs du motif 1 à la hashtable
for (int i = 0; i < match_count_1; i++) {
    strncpy(motif, &tableau[debut_1[i]], fin_1[i] - debut_1[i]);
    motif[fin_1[i] - debut_1[i]] = '\0'; 
    add_nom(motif);
}




for (int i = 0; i < match_count_2; i++) {
    strncpy(motif, &tableau[debut_2[i]], find_2[i] - debut_2[i]);
    motif[find_2[i] - debut_2[i]] = '\0'; 
    add_nom(motif);
} 
// print_tabhash();


   print_occurrences_with_nb();

  print_occurrences_with_nb_croissant();




    float nombre_moyen_points_par_occurrence = calculer_nombre_moyen_points_par_occurrence();

    printf("Nombre moyen de points par occurrence : %.2f\n", nombre_moyen_points_par_occurrence);


    int somme = 0;
    int nb_total_trouve = 0;

     // Afficher le tableau des points uniques
    printf("Tableau des points uniques :\n");
    for (int i = 0; tableau_point_unique[i]!=0; ++i) {
        printf("%d ", tableau_point_unique[i]);
        nb_total_trouve++;
    }
    printf("\n");

    printf("%d\n", nb_total_trouve);
    
    // Calculer la somme 
    for (int i = 0; tableau_point_unique[i] != 0; ++i) {
    somme += tableau_point_unique[i];
    nb_total_trouve++;
}

    float moyenne = (float)somme / nb_total_trouve;

    
    printf("Moyenne des valeurs du tableau : %.2f\n", moyenne);

    return 0;
}

