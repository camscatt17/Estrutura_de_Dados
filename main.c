#include <stdlib.h>
#include <stdio.h>
#define true 1
#define false 0

#define TAMANHO 8

typedef int bool;
typedef int TIPOPESO;

#define BRANCO 0
#define CINZA 1
#define PRETO 2

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

void liberar_grafo (GRAFO* g) {
   int v;
   for (v = 0; v < g->vertices; v++) {
      if (g->adj[v].cab != NULL) {
         free(g->adj[v].cab);
      }
   }
   free(g->adj);
   free(g);
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

void DFS_Visit(GRAFO* g, int u, int* cor){
    printf("%d ", u);
    cor[u]=CINZA;
    ADJACENCIA* v = g->adj[u].cab;
    while(v){
        if(cor[v->vertice]==BRANCO){
            DFS_Visit(g, v->vertice, cor);
        }
        v=v->prox;
    cor[u]=PRETO;
    }
}

void Busca_Profundidade(GRAFO* g){
    int* cor = (int*) malloc(g->vertices*sizeof(int));

    int u;
    for(u=0; u<g->vertices; u++){
        cor[u]=BRANCO;
    }
    for(u=0; u<g->vertices; u++){
        if(cor[u] == BRANCO){
            DFS_Visit(g, u, cor);
            printf("\n");
        }
    }

    free(cor);
}


int main () {

   GRAFO* g = criaGrafo(TAMANHO);


   /*Inserção das arestas conforme a aula: */
   criaAresta(g, 0, 1);   
   criaAresta(g, 0, 4);   
   criaAresta(g, 1, 2);   
   criaAresta(g, 1, 4);   
   criaAresta(g, 2, 3);   
   criaAresta(g, 3, 1);   
   criaAresta(g, 4, 3);   
   criaAresta(g, 5, 7);   
   criaAresta(g, 5, 6);   
   criaAresta(g, 6, 7);   
   criaAresta(g, 6, 5);   
   criaAresta(g, 7, 0);   
   criaAresta(g, 7, 4);   

   Busca_Profundidade(g);

   liberar_grafo(g);

   return 0;
}