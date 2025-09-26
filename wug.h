#ifndef WUG_H
#define WUG_H

#include <stdbool.h>
#include "data.h"
#include "util.h"

wug_t* create_wug(int genome[16], gender_t g);

void print_wug(wug_t *w);
void print_population(wug_t** population, const int size);

void genome2features(const int genome[16], int features[4]);

int  report_population(wug_t** population, const int size);
int  rank(const wug_t* w);

bool insert_ranked(wug_t** population, wug_t* w, int* size, int capacity);

#endif // WUG_H