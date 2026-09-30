#include "../inc/distance_processor.h"
#include <stdio.h>

// distances globális változó (6. Feladat)
double distances[4] = {0.0, 0.0, 0.0, 0.0};
static int dist_size = 4; // distances tömb mérete (6. Feladat)

// Átlagszámító függvény (4. Feladat)
double get_dist_avg() {
    double dist_sum = 0;
    for(int i=0; i<dist_size; i++){
        dist_sum += distances[i];
    }
    return dist_sum / dist_size;
}

// Méréseket feldolgozó függvény (4. Feladat)
void process_measurements(double m[], int m_size) {
    for(int i=0; i<m_size; i++){
        distances[i%dist_size] = m[i];
        printf("Average of distances: %f\n", get_dist_avg());
    }
}