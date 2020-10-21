#include <stdlib.h>
#include <stdio.h>
#define true 1
#define false 0

typedef int bool;
typedef int TIPOPESO;

typedef struct adjacencia {
    int vertice;
    //TIPOPESO peso;
    struct adjacencia* prox;    
} ADJACENCIA;

/*Dados armazenados vão aqui*/
typedef struct vertice { 
    ADJACENCIA* cab;
} VERTICE;

typedef struct grafo{
    int vertices;
    int arestas;
    VERTICE* vert;
}GRAFO;

int main(){

}