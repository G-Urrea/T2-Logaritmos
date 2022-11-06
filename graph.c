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
                // Se expande el arreglo de aristas
                (*graph)[from].n+=1;
                int nlink = (*graph)[from].n;
                (*graph)[from].links = (edge*)realloc((*graph)[from].links, nlink*sizeof(edge));
                (*graph)[from].links[nlink-1] = (edge){w, to};
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
node* randomGraph(int v, int e){
    // Crea un grafo  aleatorio con v nodos y e aristas.
    if  (e<=v*(v-1) && v>=2){ 
        //El número de aristas no puede ser mayor v(v-1) en un grafo dirigido

        // Inicializar grafo
        node* graph = createGraph(v);

        // Matriz que contiene las posibles conexiones para cada nodo
        int ** matrix = malloc((v) * sizeof *matrix);
        for (int i = 0; i < v; i++)
            matrix[i] = malloc((v-1) * sizeof *matrix[i]);

        // Inicializar matriz
        int to;
        for (int i=0; i<v; i++){ // O(|V|^2)
            to = 0;
            for (int j=0; j<v-1; j++){
                
                if(i==to){
                    // No puede haber un loop en un nodo.
                    to+=1;
                }
                matrix[i][j]=to;
                to+=1;
            }
        }

        // Arreglo que contiene ids de nodos 
        int * from = malloc((v)* sizeof *from);
        for (int i = 0; i < v; i++)
            from[i] = i;
        // Indica cuantos nodos en from aún pueden tener más aristas    
        int nfrom = v;
        for (int i=0; i<e; i++){ // O(|E|)
            // Escoger un nodo aleatorio
            int choice = rand() % nfrom;
            int u = from[choice];
            // Se puede seleccionar un nodo objetivo de entre los primeros v-2 - número de enlaces de matrix[u]
            int tchoice = rand()% (v-1 - graph[u].n);
            double w = rand() + 1; // Peso aleatorio con un offset para evitar pesos = 0
            int u_to =  matrix[u][tchoice];
            addEdge(&graph, v, u, u_to, w); // Se añade eje
            
            // Se deja en una posición válida el elemento que esta en la posición ya no válida
            matrix[u][tchoice] = matrix[u][v-1-graph[u].n];
            matrix[u][v-1-graph[u].n] = u_to; // El nodo escogido se deja en una posición no válida

            if (graph[u].n==(v-1)){
                nfrom-=1; // Ahora nfrom pasa a ser una posición no válida para escoger
                // El nodo que estaba en nfrom aún podría ser válido, se deja en posición válida (si choice=nfrom da igual)
                from[choice] = from[nfrom]; 
                from[nfrom] = u; // Deja nodo escogido en posición no válida
            }

        }
        //Liberar memoria
        for (int i = 0; i < v; i++)
            free(matrix[i]);
        free(matrix);
        free(from);

        return graph;
    }
    // Por defecto se retorna un puntero nulo
    return NULL;
    
}
void printGraph(node *g, int n){
    printf("Nodo: Lista de adyacencia\n");
    for (int i = 0; i<n;i++){
        printf("Nodo %d: ", g[i].id);
        printf("{");
        for (int j=0; j<g[i].n;j++){
            printf("%d ",g[i].links[j].node);
        }
        printf("}\n");
    }
    printf("\n");
}