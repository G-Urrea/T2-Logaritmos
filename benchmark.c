#include <stdio.h> 
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdbool.h> 
#include "graph.h"
#include "alg1.h"
#include "alg2.h"
#include "alg3.h"

typedef void (*func)(node*, int, int, double**, int**);

void benchmark(int min, int max, int iter, func* f, int nfun, char* filename){

    int n = pow(2, 14);
    node* graph;
    double * dist = malloc(n*sizeof(double));
    int * prev = malloc(n*sizeof(int));
    double ti, tf, delta;
    double mean[nfun];
    FILE *fp;
    fp = fopen(filename, "w");
    fprintf(fp, "n,alg,t\n");

    for (int i = min; i<=max; i++){
        int p = pow(2, i);

        for (int k=0; k<nfun; k++){
            mean[k] = 0;
        }
        
        for (int j=0; j<iter; j++){
            // Crear grafos de largo 2^i
            // Para verificar brevemente la eficiencia de la creación de grafos
            if (j==0)
                ti = (double)clock()/CLOCKS_PER_SEC; 
            graph = randomGraph(n, p);
            if (j==0){
                tf = (double)clock()/CLOCKS_PER_SEC; 
                printf("Tiempo creando grafo: %f\n", tf-ti);
                }
            int root = rand()%n; // Se selecciona una raíz
            for (int k = 0; k<nfun; k++){              
                ti = (double)clock()/CLOCKS_PER_SEC;           
                f[k](graph, n, root, &dist, &prev); // No necesitamos el valor de retorno
                tf = (double)clock()/CLOCKS_PER_SEC;
                delta = tf-ti;
                mean[k] += delta/iter;
            }
            freeGraph(&graph, n);
        }
        
        for (int k = 0; k<nfun; k++){
            printf("n: %d, Alg: %d, T: %f\n", i, k, mean[k]);
            fprintf(fp, "%d,%d,%f\n", i, k, mean[k]);
        }     
    }
    free(dist);
    free(prev);
    fclose(fp);
}

int main(){
    //func f[1] = {&fiboDijkstra};
    //func f[1] = {&heapDijkstra};
    //func f[2] = {&naiveDijkstra, &heapDijkstra};
    func f[3] = {&naiveDijkstra, &heapDijkstra,&fiboDijkstra};
    benchmark(16, 24, 50, f, 3, "resultados.txt");
    return 0;
}