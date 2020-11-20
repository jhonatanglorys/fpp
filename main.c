#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <omp.h>


double suma(double x, double y);
double suma_func(double x, double y);

int main(int argc, char* argv[]) {
    long seed;
    int n=100000000;
    double* x = NULL;
    double* y = NULL;
    double* z = NULL;
    double start, end, tiempo;
    int i=0;
    printf("Ingrese semilla para el generador de números aleatorios:\n");
    scanf("%ld", &seed);
    srand(seed);
    x = malloc(sizeof(double) * n);
    y = malloc(sizeof(double) * n);
    z = malloc(sizeof(double) * n);
    for (int i = 0; i < n; i++){
        x[i] = (double) rand() / (double) RAND_MAX;
        y[i] = (double) rand() / (double) RAND_MAX;
        z[i] = 0;
    }

    /*for (int i = 0; i < n; i++){
        printf("Vector X, posicion i=%d valor %f\n", i, x[i]);
        printf("Vector Y, posicion i=%d valor %f\n", i, y[i]);
        printf("Vector Z, posicion i=%d valor %f\n", i, z[i]);  
    }*/

    //Secuencial no funcional
    start = omp_get_wtime();
    for (i = 0; i < n; i++){
        z[i] = suma(x[i],y[i]);
        /*printf("Vector Z, posicion i=%d valor %f\n", i, z[i]);*/
    }
    end = omp_get_wtime();
    tiempo = end - start;
    printf("Tiempo de ejecucion secuencial no funcional: %f s\n\n", tiempo);

    start=0;
    end=0;
    tiempo=0;

    //Secuencial funcional
    start = omp_get_wtime();
    for (i = 0; i < n; i++){
        z[i] = suma_func(x[i],y[i]);
        /*printf("Vector Z, posicion i=%d valor %f\n", i, z[i]);*/
    }
    end = omp_get_wtime();
    tiempo = end - start;
    printf("Tiempo de ejecucion secuencial funcional: %f s\n\n", tiempo);


    start=0;
    end=0;
    tiempo=0;

    //Secuencial paralelo no funcional
    start = omp_get_wtime();
    #pragma omp parallel for private(i)
    for (i = 0; i < n; i++){
        z[i] = x[i] + y[i];
        /*printf("Vector Z, posicion i=%d valor %f\n", i, z[i]);*/
    }
    end = omp_get_wtime();
    tiempo = end - start;
    printf("Tiempo de ejecucion secuencial paralelo no funcional: %f s\n\n", tiempo);


    start=0;
    end=0;
    tiempo=0;

    //Secuencial paralelo funcional
    start = omp_get_wtime();
    #pragma omp parallel for private(i)
    for (i = 0; i < n; i++){
        z[i] = suma_func(x[i],y[i]);
        /*printf("Vector Z, posicion i=%d valor %f\n", i, z[i]);*/
    }
    end = omp_get_wtime();
    tiempo = end - start;
    printf("Tiempo de ejecucion secuencial paralelo funcional: %f s\n\n", tiempo);


}

double suma(double x, double y){
    double z;
    z=x+y;
    return z;
}

double suma_func(double x, double y){
    return x+y;
}
