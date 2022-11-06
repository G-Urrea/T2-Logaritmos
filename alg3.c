#include <stdio.h> 
#include <stdlib.h>
#include <math.h>
#include <stdbool.h> 
#include "graph.h"
#include "fibo.h"
#include "alg3.h"

void fiboDijkstra(node* graph, int n, int root, double** dist, int** prev){
    FIB_HEAP *h;
    h = (FIB_HEAP *)malloc(sizeof(FIB_HEAP));
    FIB_ELEMENT *map[n];
    h = make_fib_heap(n, map); // Inicializar un fibo_heap


    int visited[n];


    // Inicializar arreglos dist, prev y visited
    for (int i=0; i<n;i++){
        (*dist)[i] = INFINITY;
        (*prev)[i] = -1;
        visited[i] = 0;

    }
    if (root>=n){
        root=0;
        }

    (*dist)[root] = 0;
    
    // Se insertan los nodos;
    FIB_ELEMENT *new_elem;
    for (int i=0; i<n;i++){
        insertion(h, new_elem, graph[i], (*dist)[i]);
        if (i==5){
            print_fibo(h);
        }
    }
    //print_fibo(h);
    while (h->n>0 && find_min_node(h)!=NULL){
        FIB_ELEMENT *min = extract_min(h);
        int uid = min->v.id; //id del minimo actual (u)
        visited[uid] = 1; //ya no está en el heap, se considera visitado      
        if (min->v.links!=NULL){ // Si el nodo no está aislado
            edge* neighbours = min->v.links;
            for (int i=0;i<min->v.n;i++){
                edge current = neighbours[i];
                int vid = current.node; //id del nodo objetivo (v)
                if (!visited[vid]){
                    //Si el vecino no ha sido visitado
                    double alt = (*dist)[uid]+current.w; //dist[u] + d(u,v)
                    if (alt < (*dist)[vid]){ // alt<dist[v]
                        (*dist)[vid] = alt; //dist[v] <- alt
                        (*prev)[vid] = uid; // prev[v] <- u
                        decrease_key(h, (h->map[vid]), alt); // Se cambia el peso con decreaseKey
                    }
                }
            }
        }
    }
    free(h);
}
