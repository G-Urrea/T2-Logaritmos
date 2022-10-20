#ifndef GRAPH_DOT_H    
#define GRAPH_DOT_H 

typedef struct edge
{ //Representa una arista
    double w; // peso de la arista
    int node; // indice del vecino
} edge;

typedef struct node
{/* Cada nodo contiene un arreglo de aristas representadas por pares que contienen un
    puntero a uno de sus vecinos (o su índice dentro del arreglo) y el peso de esa
    arista. */

    edge* links; // Lista de adyacencia con vertices
    int id; // id del nodo, en la lista de nodos sería su indice
    int n; // Parámetro extra, para conocer el largo de la lista de adyacencia

} node;

node* createGraph(int n); // Crea un grafo (arreglo de nodos) de tamaño n, requiere liberar memoria.
void addEdge(node** graph, int n, int from, int to, double w); // Añade una arista al grafo
void freeGraph(node** graph, int n); //Libera la memoria pedida por un grafo y sus componentes
#endif