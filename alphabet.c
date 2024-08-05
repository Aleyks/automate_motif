#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

void remplirTableau(char tableau[], int taille) {
    
    srand(time(NULL));
    
    
    char lettres[] = {'L', 'A', 'I', 'S'};
    
    
    for (int i = 0; i < taille; ++i) {
        int index = rand() % 4;
        tableau[i] = lettres[index];
    }
    tableau[taille - 1] = '\0';
}




/* int main() {
    char tableau[10000];
    int taille_tab = sizeof(tableau)/sizeof(tableau[0]);
     int motifs[taille_tab];
    int nbMotifs = 0;
    
    remplirTableau(tableau, taille_tab);
    
    
    for (int i = 0; i < taille_tab; ++i) {
        printf("%c", tableau[i]);
    }
    printf("\n");


  
    
    return 0;
} 
 */