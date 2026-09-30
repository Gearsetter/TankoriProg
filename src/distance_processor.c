#include "../inc/distance_processor.h"
#include <stdio.h>

// Átlagszámító függvény (4. Feladat)
double get_dist_avg(double d[], int d_size) {
    double dist_sum = 0;
    for(int i=0; i<d_size; i++){
        dist_sum += d[i];
    }
    return dist_sum / d_size;
}

// Méréseket feldolgozó függvény (4. Feladat)
void process_measurements(double m[], int m_size, double d[], int d_size) {
    for(int i=0; i<m_size; i++){
        d[i%d_size] = m[i];
        printf("Average of distances: %f\n", get_dist_avg(d, d_size));
    }
}