#include <stdio.h> 
#include <stdlib.h>
#include <math.h> 
#include "graph.h"
#include "alg1.h"

void naiveDijkstra(node* graph, int n, int root, double** dist, int** prev){
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
    //Una vez por cada nodo
    int uid;
    double min;
    for (int i=0; i<n; i++){
        // Buscar mínimo
        min = INFINITY;
        for (int j=0; j<n; j++){
            // Se busca y establece como mínimo la menor distancia no marcada
            if ((*dist)[j]<=min && !visited[j]){
                min = (*dist)[j];
                uid = j;
            }
        }
        node u = graph[uid];
        visited[uid] = 1;
        if (u.links!=NULL){ // Si el nodo no está aislado
            edge* neighbours = u.links;
            for (int j=0;j<u.n;j++){
                edge current = neighbours[j];
                int vid = current.node; //id del nodo objetivo (v)
                if (!visited[vid]){
                    //Si el vecino no ha sido visitado
                    double alt = (*dist)[uid]+current.w; //dist[u] + d(u,v)
                    if (alt < (*dist)[vid]){ // alt<dist[v]
                        (*dist)[vid] = alt; //dist[v] <- alt
                        (*prev)[vid] = uid; // prev[v] <- u
                    }
                }
            }
        }
    }
}
