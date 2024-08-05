/* ***************************************************************
*
*  Hashcoding
*
*  F. Balmas 2021
*
******************************************************************/
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "freel-liste.h"
#include "hashcode.h"

//#define NODEBUG
//#define SIZE BUFSIZ

LINKED tabhash[N];




void init_tabhash(void) {
int i;

        for (i=0 ; i<N ; i++)
        {
           tabhash[i] = alloc_list();;
           init_list (tabhash[i]);
        }
}

int compute_hash (char *word) {
int i, nb;

        nb = 0;
        for (i=0 ; word[i] != '\0' ; i++)
           nb += word[i];
        return (nb % N);
}

// retourne pointeur sur chaînon si trouve
// NULL sinon
LINKED search_nom (char *nom) {
int hash;

	hash = compute_hash (nom);
	return (member(nom, tabhash[hash]));
}

/* void add_nom(char *nom) {
int hash;
LINKED new;

	hash = compute_hash (nom);
	new = alloc_list();
	strcpy(new->nom, nom);
	add_begin (tabhash[hash], new);
} */


void add_nom(char *nom) {
    int hash;
    LINKED new;

    hash = compute_hash(nom);
    
    
    LINKED existant = search_nom(nom);
    if (existant != NULL) {
        
        existant->occurrences++;
    } else {
       
        new = alloc_list();
        strcpy(new->nom, nom);
        new->occurrences = 1; 
        add_begin(tabhash[hash], new);
    }
}


void print_tabhash(void) {
int i, j;
	printf("print tabhash\n");
	for(i=0 ; i<N ; i++) {
        printf("%d : ", i);
		print_list(tabhash[i]);
	}
}








void print_occurrences_with_nb() {
    printf("Ensemble des occurrences differentes (sans doublons)\n");
    printf("Occ              Nb d'occurrences\n");
    printf("---------------------------------\n");

    // Parcourir la hashtable
    for (int i = 0; i < N; i++) {
        LINKED current = tabhash[i]->cell;
        while (current != NULL) {
            printf("%s %d\n", current->nom, current->occurrences);
            current = current->cell;
        }
    }
}




void print_occurrences_with_nb_croissant() {
    printf("Ensemble des occurrences differentes (sans doublons)\n");
    printf("Occ              Nb d'occurrences\n");
    printf("---------------------------------\n");

    
    int total_occurrences = 0;

    
    LINKED occurences_tab[N];

   
    for (int i = 0; i < N; i++) {
        LINKED current = tabhash[i]->cell;
        while (current != NULL) {
            occurences_tab[total_occurrences] = current;
            total_occurrences++;
            current = current->cell;
        }
    }

    
    for (int i = 0; i < total_occurrences - 1; i++) {
        for (int j = 0; j < total_occurrences - i - 1; j++) {
            if (occurences_tab[j]->occurrences > occurences_tab[j + 1]->occurrences) {
                // Swap pointers to linked list nodes
                LINKED temp = occurences_tab[j];
                occurences_tab[j] = occurences_tab[j + 1];
                occurences_tab[j + 1] = temp;
            }
        }
    }

   
    for (int i = 0; i < total_occurrences; i++) {
        printf("%s %d\n", occurences_tab[i]->nom, occurences_tab[i]->occurrences);
    }
}


float calculer_nombre_moyen_points_par_occurrence() {
    int total_occurrences = 0;
    int total_points = 0;

    
    for (int i = 0; i < N; i++) {
        LINKED current = tabhash[i]->cell;
        while (current != NULL) {
            total_occurrences++;
            total_points += current->occurrences; 
            current = current->cell;
        }
    }

    
    if (total_occurrences > 0) {
        
        return (float) total_points / total_occurrences;
    } else {
        return 0; 
    }
}



