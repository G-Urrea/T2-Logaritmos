#include <stdio.h> 
#include <stdlib.h>
#include <math.h> 
#include "graph.h"
#include "heap.h"
#include "alg2.h"

void heapDijkstra(node* graph, int n, int root, double** dist, int** prev){
    heap *h = malloc(sizeof(*h)); // Inicializar un heap
    h->capacity = n;
    h->size = 0;
    heapElement * vertexs = malloc(n*sizeof(*vertexs));
    h->vertexs = vertexs;
    int* map = malloc(n*sizeof(int));
    h->map = map;
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
    for (int i=0; i<n;i++){
        heapElement he = {graph[i], (*dist)[i]};
        insert(h, he);
    }
    while (h->size>0 && getMin(h)!=NULL){
        heapElement min = *getMin(h);
        int uid = min.v.id; //id del minimo actual (u)
        visited[uid] = 1; //ya no está en el heap, se considera visitado      

        deleteMin(h);  
        if (min.v.links!=NULL){ // Si el nodo no está aislado
            edge* neighbours = min.v.links;
            for (int i=0;i<min.v.n;i++){
                edge current = neighbours[i];
                int vid = current.node; //id del nodo objetivo (v)
                if (!visited[vid]){
                    //Si el vecino no ha sido visitado
                    double alt = (*dist)[uid]+current.w; //dist[u] + d(u,v)
                    if (alt < (*dist)[vid]){ // alt<dist[v]
                        (*dist)[vid] = alt; //dist[v] <- alt
                        (*prev)[vid] = uid; // prev[v] <- u
                        decreaseKey(h, h->map[vid], alt); // Se cambia el peso con decreaseKey
                    }
                }
            }
        }
    }
    free(map);
    free(vertexs);
    free(h);
}
