#include <stdio.h>

int main() {
    // Hello World (1. Feladat)
    printf("Hello World!\n");

    // Méréseket tároló tömb (2. Feladat)
    double distances[4] = {0.0, 1.0, 2.0, 3.0};
    double dist_size = 4;

    // Átlagszámítás (2. Feladat)
    double dist_sum = 0;
    for(int i=0; i<dist_size; i++){
        dist_sum += distances[i];
    }
    double dist_avg = dist_sum / dist_size;
    printf("Average of distances: %f\n", dist_avg);

    // Loopban várakozás a program végén (1. Feladat)
    char terminate;
    while(1){
        if(scanf("%c", &terminate)){
            break;
        }
    }
    return 0;
}