#include <stdio.h>

int main() {
    // Hello World (1. Feladat)
    printf("Hello World!\n");

    // Beérkező mérések
    double measurements[6] = {0.0, 1.0, 2.0, 3.0, 4.0, 5.0};
    int meas_size = 6;
    
    // Méréseket tároló tömb (2. Feladat), reinit 0-vá (3. Feladat)
    double distances[4] = {0.0, 0.0, 0.0, 0.0};
    int dist_size = 4;
    
    // Beérkező mérések eltárolása (3. Feladat)
    for(int i=0; i<meas_size; i++){
        distances[i%dist_size] = measurements[i];

        // Átlagszámítás (2. Feladat)
        double dist_sum = 0;
        for(int i=0; i<dist_size; i++){
            dist_sum += distances[i];
        }
        double dist_avg = dist_sum / dist_size;
        printf("Average of distances: %f\n", dist_avg);
        // Átlagszámítás vége

    }


    // Loopban várakozás a program végén (1. Feladat)
    char terminate;
    while(1){
        if(scanf("%c", &terminate)){
            break;
        }
    }
    return 0;
}