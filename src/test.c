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

int main() {
    // Hello World (1. Feladat)
    printf("Hello World!\n");

    // Beérkező mérések
    double measurements[6] = {0.0, 1.0, 2.0, 3.0, 4.0, 5.0};
    int meas_size = 6;
    
    // Méréseket tároló tömb (2. Feladat), reinit 0-vá (3. Feladat)
    double distances[4] = {0.0, 0.0, 0.0, 0.0};
    int dist_size = 4;
    
    // Beérkező mérések feldolgozása, átlagszámítással (4. Feladat)
    process_measurements(measurements, meas_size, distances, dist_size);


    // Loopban várakozás a program végén (1. Feladat)
    char terminate;
    while(1){
        if(scanf("%c", &terminate)){
            break;
        }
    }
    return 0;
}