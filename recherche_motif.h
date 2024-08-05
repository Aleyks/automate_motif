#include <stdbool.h>
#define MAX 2000
#define MAX_MOTIFS 1000  // Maximum number of matches

#define NBETATS 5
#define NBETATS_2 6

#define NBTYPES 5
#define ETATENTREE 0
#define ETATSORTIE 10
#define ETATSORTIE_2 6

#define ETATERREUR -1
int tableau_point_unique[200];
int unique_points_count = 0;

void affiche_ttransit(int (*)[NBTYPES]);
void affiche_ttransit_2(int (*)[NBTYPES]);

enum types get_type(char);
void print_typ(char *);
int automate(char *tableau, int *starts, int *ends);
int automate_2(char *tableau, int *starts, int *ends);
