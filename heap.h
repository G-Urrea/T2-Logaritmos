#ifndef HEAP_DOT_H    
#define HEAP_DOT_H 

typedef struct heapElement
{
    node v; // El vertice 
    double w; // Peso al origen
} heapElement; 

typedef struct heap
{
    int size; // Tamaño actual del heap
    int capacity; // Capacidad total del heap
    heapElement* vertexs;
    int* map; // Dado un id, guarda en map[id] el indice del elemento vertex[map[id]]
} heap;

void swap(heapElement* u, heapElement* v, int i, int j, int ** map); //Intercambia dos heapElement
void heapUp(heapElement** v, int** map, int j); 
void heapDown(heapElement** v, int** map, int j, int size);
heapElement* getMin(heap* h);
void deleteMin(heap* h);
void decreaseKey(heap* h, int i, int w);
void insert(heap* h, heapElement e);
void printHeap(heap* h);

#endif