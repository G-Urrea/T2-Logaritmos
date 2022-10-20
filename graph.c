#include <stdio.h> 
#include <stdlib.h>
#include "graph.h"

void addEdge(node** graph, int n, int from, int to, double w){
    // Añade/modifica una arista
    // Recibe puntero a arreglo de nodos, tamaño actual del grafo,
    // desde que nodo a que nodo se quiere añadir la arista y el peso de esta
    if (to<n && to>=0 && from<n && from>=0){
     
        if ((*graph)[from].links==NULL){
            edge * newlink = malloc(sizeof(*newlink));
            newlink[0] = (edge){w, to};
            (*graph)[from].links = newlink;
            (*graph)[from].n+=1;
        }
        else{
            int nlink = (*graph)[from].n;
            int exists = 0;
            for (int i=0; i<nlink;i++){
                if ((*graph)[from].links[i].node==to){
                    //Ya existe conexión al nodo "to", se cambia el peso
                    (*graph)[from].links[i].w = w;
                    exists = 1;
                    break;
                }
            }
            if(!exists){
                // No existe conexión, se expande el arreglo de aristas
                (*graph)[from].n+=1;
                int nlink = (*graph)[from].n;
                (*graph)[from].links = (edge*)realloc((*graph)[from].links, nlink*sizeof(edge));
                (*graph)[from].links[nlink-1] = (edge){w, to};
            }
        }
        
    }
}

node* createGraph(int n){
    // Crea un grafo (arreglo de nodos) de tamaño n
    // Requiere liberar memoria
    node* graph = malloc(n*sizeof(*graph));
    for (int i=0; i<n; i++){
        graph[i] = (node) {NULL, i, 0};
    }
    return graph;
}

void freeGraph(node** graph, int n){
    for (int i=0; i<n; i++){
        free((*graph)[i].links);
    }
    free(*graph);
}