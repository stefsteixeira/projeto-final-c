#ifndef UTIL_H
#define UTIL_H

#include <stdint.h>

char*   array_string(const int arr[], const int size);
uint8_t features2bits(const int feats[4]);
void    bits2features(const uint8_t value, int features[4]);

#endif // UTIL_H