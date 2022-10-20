#include <stdio.h> 
#include <stdlib.h>
#include <math.h>
#include "graph.h"
#include "heap.h"

void swap(heapElement* u, heapElement* v, int i, int j, int ** map){
    /* Recibe 2 elementos (u,v), sus indices en el arreglo del heap (i,j) y el mapeo
        de sus ids a indice en el heap. 
    */
    (*map)[(*u).v.id] = j; // map[id de u] = indice j
    (*map)[(*v).v.id] = i; // map[id de v] = indice i
    heapElement temp = *u;
    *u = *v;
    *v = temp;
}

void heapUp(heapElement** v, int** map, int j){
    // El elemento j trepa hasta su prioridad
    int parent = floor((j-1)/2);
    while (j>=1 && (*v)[j].w<(*v)[parent].w){

        swap(&(*v)[j], &(*v)[parent], j, parent, map);
        j = parent; // Se avanza hacia la posición del padre
        parent = floor((j-1)/2);// Se actualiza el padre
    }
}

void heapDown(heapElement** v, int** map, int j, int size){
    while (2*j+1<size){ // Mientras haya al menos un hijo
        int k = 2*j+1; // Hijo izquierdo
        if (k+1<size && (*v)[k+1].w<(*v)[k].w){
            // El hijo derecho existe y tiene mejor prioridad que el izquierdo
            k+=1;
        } 
        if ((*v)[j].w < (*v)[k].w){
            // El padre tiene mejor prioridad que ambos hijos
            break;
        }
        swap(&(*v)[j], &(*v)[k], j, k, map); // Se intercambia con el menor de los hijos       
        j=k;
    }
}

heapElement* getMin(heap* h){
    // Retorna puntero al minimo
    if (h->size>0){
    heapElement *minElement = &(h->vertexs[0]);
    return minElement;
    }
    return NULL;
}

void deleteMin(heap* h){
    if (h->size>0){
        //Extraer mínimo   
        h->size-=1;
        // El elemento sobrante se mueve al casillero vacante
        swap(&(h->vertexs[0]), &(h->vertexs[h->size]), 0, h->size, &(h->map)); 
        heapDown(&(h->vertexs), &(h->map), 0, h->size);
    }
}

void decreaseKey(heap* h, int i, int w){
    /*    
    i-> Indice en el arreglo del heap
    w-> Nuevo peso
    */
   if (i<h->size){
        h->vertexs[i].w = w;
        heapUp(&(h->vertexs), &(h->map), i);
    }
}

void insert(heap* h, heapElement e){
    if (h->size<h->capacity){
         
        // Insertar al final y después subir según prioridad
        (h->vertexs)[h->size] = e;
        (h->map)[e.v.id] = h->size;
        heapUp(&(h->vertexs), &(h->map), h->size);
        h->size+=1;
    }
}
void printHeap(heap *h){
    printf("Arreglo (id, peso): ");
    for (int i=0; i<h->size; i++){
        printf("(%d, %f)", h->vertexs[i].v.id, h->vertexs[i].w);
    }
    printf("\n");
}