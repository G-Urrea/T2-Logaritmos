#include <stdio.h> 
#include <stdlib.h>
#include <math.h>
#include "graph.h"
#include "normal.h"


//elimina un elemento en un array con vertices de un grafo
void elimElement(node* arr, int n, int id){ //n es el largo del arreglo
    if(id == -1){
        printf("salió un -1 ;(");
        exit(2);
    }
    node **tem = &arr; //puntero al array
    for(int i = 0; i<n;i++){
        if(arr[i].id ==id){
            tem++;
            arr[i]= **tem;
            for(int j=i+1;j<n-1;j++){
                tem++;
                arr[j] = **tem;
            }
            break;
        }
        tem++;
    }
}

// Retorna indice del minimo de un array
//si todos fueron visitados o no hay elementos en el array retorna -1
int Min(double* arr, int* visited,int n){ //n es el largo del arreglo
    int min= arr[0];
    int minIx=-1;
    if (n>0){
        for(int i=0;i<n;i++){
            if(min<arr[i] && visited[i]==0){
                min=arr[i];
                minIx = i;
            }
        }
        return minIx;
    }
    return -1;
}



