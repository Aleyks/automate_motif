/* ***************************************************************
*
*  Hashcoding
*
*  F. Balmas 2021
*
******************************************************************/
// valeur standard
// #define N 53
// valeur de demo
#define N 500
#define MAX_MOTIF_LENGTH 20

extern LINKED tabhash[N];

LINKED search_nom(char *nom);
void add_nom(char *s);
void init_tabhash(void);
void print_tabhash(void);
int compute_hash(char *word);
void afficher_occurrences(void);

