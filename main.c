#include <stdlib.h>
#include <stdio.h>
#define true 1
#define false 0

typedef int bool;
typedef int TIPOPESO;

/*Nesse contexto adjacencia é lista de arestas*/ 
typedef struct adjacencia {
    int vertice; // vértice final
    //TIPOPESO peso;
    struct adjacencia* prox;    
} ADJACENCIA;

/*Dados armazenados vão aqui*/
typedef struct vertice { 
    ADJACENCIA* cab; // o vértice possui apenas a cabeça da lista de adjacencias
} VERTICE;

typedef struct grafo{
    int vertices; // numero de vertices
    int arestas; // numero de arestas
    VERTICE* adj;
} GRAFO; 

GRAFO* criaGrafo(int n){
    GRAFO* g = (GRAFO*)malloc(sizeof(GRAFO));
    g->vertices = n;
    g->arestas = 0;//inicialmente o grafo não possui arestas
    g->adj = (VERTICE*)malloc(n*sizeof(VERTICE));
    int i;
    for(i=0; i<n; i++){
        g->adj[i].cab = NULL; //Todas as adjacencias são null pois não existe aresta
    }
    return g;
}

bool verificaGrafoVazio(GRAFO* g){
    return(g == NULL);
}

/*Função responsavel por alocar as arestas*/
/*Recebe como parametro o vertice final da aresta e o peso dela, caso este exista*/
ADJACENCIA* criaAdj(int vertice){
    ADJACENCIA* aux = (ADJACENCIA*)malloc(sizeof(ADJACENCIA));
    aux->vertice = vertice;
    aux->prox = NULL;
    return aux;
}

/*Cria efetivamente a aresta, uma vez que a adjacencia é apenas "a ponta da seta"*/
/*Para se ter uma aresta completa, é necessario conecta-la ao vertice inicial*/
/*Esse caso é feito para grafos dirigidos*/
bool criaAresta(GRAFO* g, int vi, int vf){
    if(verificaGrafoVazio(g))
        return false;
    if((vf<0)||(vf>=g->vertices))
        return false;
    if((vi<0)||(vi>=g->vertices))
        return false;

    ADJACENCIA* aresta = criaAdj(vf);
    aresta->prox = g->adj[vi].cab;
    g->adj[vi].cab = aresta;
    g->arestas++;
    return (true);
}

void imprimeGrafo(GRAFO* g){
    if(!verificaGrafoVazio(g)){
        printf("Vertices: %d. Arestas: %d\n", g->vertices, g->arestas);
        int i;
        for(i=0; i<g->vertices; i++){
            printf("v%d: ", i);
            ADJACENCIA* ad = g->adj[i].cab;
            while(ad!=NULL){
                printf("v%d ", ad->vertice);
                ad=ad->prox;
            }
            printf("\n");
        }
    }
}

int main(){
    GRAFO* g = criaGrafo(5);
    criaAresta(g, 0, 1);
    criaAresta(g, 1, 2);
    criaAresta(g, 2, 0);
    criaAresta(g, 2, 4);
    criaAresta(g, 3, 1);
    criaAresta(g, 4, 3);

    imprimeGrafo(g);
}