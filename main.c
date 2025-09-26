#include <stdio.h>
#include <stdlib.h>
#include "data.h"
#include "util.h"
#include "wug.h"

int main(void) {
    int g1[16] = {1,0,1,1,1,0,0,1,0,1,0,0,1,1,0,0}; // super_wug -> rank 4
    int g2[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}; // rank 0
    int g3[16] = {1,0,1,1,0,0,0,1,0,1,0,0,1,1,0,0}; // rank 3 (como exemplo)

    wug_t *w1 = create_wug(g1, M);
    wug_t *w2 = create_wug(g2, F);
    wug_t *w3 = create_wug(g3, M);

    int size = 0, cap = 3;
    wug_t* pop[3];

    insert_ranked(pop, w1, &size, cap);
    insert_ranked(pop, w2, &size, cap);
    insert_ranked(pop, w3, &size, cap);

    print_population(pop, size);
    printf("superwugs: %d\n", report_population(pop, size));

    for (int i = 0; i < size; i++) free(pop[i]);
    return 0;
}
