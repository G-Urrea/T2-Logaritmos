#include <stdio.h> 
#include <stdlib.h>
#include <math.h>
#include "graph.h"
#include "alg1.h"
// Programa de testeo con grafos de 8 vertices
int main(){
    // Grafo no dirigido
    node* g = createGraph(8);
    addEdge(&g, 8, 0, 1, 9);
    addEdge(&g, 8, 0, 3, 9);

    addEdge(&g, 8, 1, 0, 9);
    addEdge(&g, 8, 1, 3, 1);
    addEdge(&g, 8, 1, 2, 8);
    addEdge(&g, 8, 1, 6, 3);

    addEdge(&g, 8, 2, 1, 8);
    addEdge(&g, 8, 2, 6, 1);

    addEdge(&g, 8, 3, 0, 9);
    addEdge(&g, 8, 3, 1, 1);
    addEdge(&g, 8, 3, 7, 2);

    addEdge(&g, 8, 4, 7, 9);

    addEdge(&g, 8, 5, 6, 9);

    addEdge(&g, 8, 6, 1, 3);
    addEdge(&g, 8, 6, 2, 1);
    addEdge(&g, 8, 6, 5, 9);

    addEdge(&g, 8, 7, 3, 2);
    addEdge(&g, 8, 7, 4, 9);
    
    double dt[8][8] = {
        {0, 9, 13, 9, 20, 21, 12, 11},
        {9, 0, 4, 1, 12, 12, 3, 3},
        {13, 4, 0, 5, 16, 10, 1, 7},
        {9, 1, 5, 0, 11, 13, 4, 2},
        {20, 12, 16, 11, 0, 24, 15, 9},
        {21, 12, 10, 13, 24, 0, 9, 15},
        {12, 3, 1, 4, 15, 9, 0, 6},
        {11, 3, 7, 2, 9, 15, 6, 0}
        };
    int pt[8][8] = {
        {-1, 0, 6, 0, 7, 6, 1, 3},
        {1, -1, 6, 1, 7, 6, 1, 3},
        {1, 6, -1, 1, 7, 6, 2, 3},
        {3, 3, 6, -1, 7, 6, 1, 3},
        {3, 3, 6, 7, -1, 6, 1, 4},
        {1, 6, 6, 1, 7, -1, 5, 3},
        {1, 6, 6, 1, 7, 6, -1, 3},
        {3, 3, 6, 7, 7, 6, 1, -1}
        };
    // Se reutilizan
    double * d = malloc(8*sizeof(double));
    int * p = malloc(8*sizeof(int));
    
    printf("Probando grafo no dirigido....\n");
        for(int i=0; i<8; i++){
        naiveDijkstra(g, 8, i, &d, &p);
        for (int j=0;j<8;j++){
            if(dt[i][j]!=d[j] ||pt[i][j]!=p[j]){
                printf("Resultado incorrecto con raíz: %d\n", i);
                printf("Nodo: %d\n", j);
                printf("Distancia esperada: %f, obtenida:%f\n", dt[i][j], d[j]);
                printf("Previo esperado: %d, obtenido:%d\n", pt[i][j], p[j]);

                free(d);
                free(p);
                freeGraph(&(g), 8);
                return 1;
            }
        }
    }
    freeGraph(&g, 8);

    // Grafo dirigido
    node* g2 = createGraph(8);

    addEdge(&g2, 8, 0, 3, 5);

    addEdge(&g2, 8, 1, 0, 7);
    addEdge(&g2, 8, 1, 3, 6);
    addEdge(&g2, 8, 1, 2, 3);
    addEdge(&g2, 8, 1, 6, 6);

    addEdge(&g2, 8, 2, 0, 6);
    addEdge(&g2, 8, 2, 4, 3);
    addEdge(&g2, 8, 2, 5, 2);
    addEdge(&g2, 8, 2, 6, 9);
    

    addEdge(&g2, 8, 3, 1, 6);

    addEdge(&g2, 8, 4, 2, 7);
    addEdge(&g2, 8, 4, 6, 7);

    addEdge(&g2, 8, 5, 6, 8);

    addEdge(&g2, 8, 6, 5, 7);

    printf("Probando grafo dirigido....\n");
    double dt2[8][8] = {
        {0, 11, 14, 5, 17, 16, 17, INFINITY},
        {7, 0, 3, 6, 6, 5, 6, INFINITY},
        {6, 17, 0, 11, 3, 2, 9, INFINITY},
        {13, 6, 9, 0, 12, 11, 12, INFINITY},
        {13, 24, 7, 18, 0, 9, 7, INFINITY},
        {INFINITY, INFINITY, INFINITY, INFINITY, INFINITY, 0, 8, INFINITY},
        {INFINITY, INFINITY, INFINITY, INFINITY, INFINITY, 7, 0, INFINITY},
        {INFINITY, INFINITY, INFINITY, INFINITY, INFINITY, INFINITY, INFINITY, 0}
        };
    int pt2[8][8] = {
        {-1, 3, 1, 0, 2, 2, 1, -1},
        {1, -1, 1, 1, 2, 2, 1, -1},
        {2, 3, -1, 0, 2, 2, 2, -1},
        {1, 3, 1, -1, 2, 2, 1, -1},
        {2, 3, 4, 0, -1, 2, 4, -1},
        {-1, -1, -1, -1, -1, -1, 5, -1},
        {-1, -1, -1, -1, -1, 6, -1, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1}
        };
    
    for(int i=0; i<8; i++){
        naiveDijkstra(g2, 8, i, &d, &p);
        for (int j=0;j<8;j++){
            if(dt2[i][j]!=d[j] ||pt2[i][j]!=p[j]){
                printf("Resultado incorrecto con raíz: %d\n", i);
                printf("Nodo: %d\n", j);
                printf("Distancia esperada: %f, obtenida:%f\n", dt2[i][j], d[j]);
                printf("Previo esperado: %d, obtenido:%d\n", pt2[i][j], p[j]);

                free(d);
                free(p);
                freeGraph(&(g2), 8);
                return 1;
            }
        }
    }
    printf("Nice!\n");
    free(d);
    free(p);
    freeGraph(&(g2), 8);
    return 0;
}
