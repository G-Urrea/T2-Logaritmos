#include <stdio.h> 
#include <stdlib.h>
#include <math.h> 
#include "graph.h"
#include "alg1.h"
#include "normal.h"

void normalDijkstra(node* graph, int n, int root, double** dist, int** prev){
    
    int visited[n];
    int n_aux = n;
    node auxiliar[n]; //lista auxiliar de los vértices del grafo
    
    // Inicializar arreglos dist, prev y visited
    for (int i=0; i<n;i++){
        (*dist)[i] = INFINITY; //la distancia a la raiz se define como infinita
        (*prev)[i] = -1; //los nodos previos no estan definidos
        visited[i] = 0;
    }
    if (root>=n){
        root=0;
        }

    (*dist)[root] = 0; //la distancia del nodo raiz a sí mismo es 0
    
    // Se insertan los nodos en un arreglo auxiliar
    for (int i=0; i<n;i++){
        auxiliar[i] = graph[i];
    }
    
    while (auxiliar != NULL){ //mientras tengamos elementos en el arreglo aux
        int min = Min((*dist),visited,n); //id del minimo
        visited[min] = 1; //ya no será parte del aux, se considera visitado      

        elimElement(auxiliar, n_aux, min);
        n_aux-=1;  
        if (graph[min].links!=NULL){ // Si el nodo no está aislado
            edge* neighbours = graph[min].links;
            for (int i=0;i<graph[min].n;i++){
                edge current = neighbours[i];
                int uid = current.node; //id del nodo objetivo (u)
                if (!visited[uid]){
                    //Si el vecino no ha sido visitado
                    double alt = (*dist)[min]+current.w; //dist[v] + d(u,v)
                    if (alt < (*dist)[uid]){ // alt<dist[u]
                        (*dist)[uid] = alt; //dist[u] <- alt
                        (*prev)[uid] = min; // prev[u] <- v
                    }
                }
            }
        }
    }
}
