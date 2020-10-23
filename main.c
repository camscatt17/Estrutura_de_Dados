#include <stdio.h>
#include <stdlib.h>

#define BRANCO 1
#define CINZA  2
#define PRETO  3
#define INFTY  99999

/*Estrutura para um vértice em uma lista encadeada: */
typedef struct vertice {
   int d;
   int cor;
   int pai;
   int identificador; /*Identificador do vértice armazenado no nó. */   
   struct vertice *proximo; /* Próximo nó na lista encadeada. */
} Vertice;

/*Estrutura do Grafo: */
typedef struct grafo {
   int E; /* Quantidade de arestas. */
   int V; /* Quantidade de vértices. */
   Vertice **listaAdj; /* Lista de adjacências. */
} Grafo;

/*---------------- TAD QUEUE ---------------------*/

typedef struct fila {
   int ini;    /*guarda o inicio da fila*/
   int fim;    /*guarda o fim da fila*/
   int tam;    /*tamanho da fila*/
   int *vetor; /*vetor de elementos*/
} Fila;

int empty (Fila *f) {
   return (f->ini == f->fim);
}

int full (Fila *f) {
   return (f->ini == ((f->fim + 1) % f->tam));
}

Fila* create_queue (int tam) {
   Fila *f = (Fila *)malloc(sizeof(Fila));
   f->ini = 0;
   f->fim = 0;
   f->tam = tam;
   f->vetor = (int*)malloc(tam*sizeof(int));
   return f;
}

void enqueue (Fila *f, int e) {
   if (full(f)) {
      printf("fila cheia: capacidade esgotada!");
      exit(1); /*aborta programa*/
   }
   f->vetor[f->fim] = e; /*insere elemento*/
   f->fim = (f->fim + 1) % f->tam; /*incremento*/
}

int dequeue (Fila *f) {
   if (empty(f)) {
      printf("fila vazia!");
      exit(1); /*aborta programa*/
   }
   int v = f->vetor[f->ini]; /*guarda o elemento*/
   f->ini = (f->ini + 1) % f->tam; /*incremento*/
   return v;
}

void free_queue (Fila *f) {
   free(f->vetor);
   free(f);
}

/*------------END TAD QUEUE---------------*/

/* */
Grafo* criar_grafo (int tamanho) {
   int v;
   Grafo *G = (Grafo *)malloc(sizeof(Grafo));
   G->E = 0;
   G->V = tamanho;
   G->listaAdj = (Vertice **)malloc(tamanho * sizeof(Vertice *));
   for (v = 0; v < G->V; v++) {
      G->listaAdj[v] = NULL; 
   } 
   return G;
}

/* */
void liberar_grafo (Grafo *G) {
   int v;
   for (v = 0; v < G->V; v++) {
      if (G->listaAdj[v] != NULL) {
         free(G->listaAdj[v]);
      }
   }
   free(G->listaAdj);
   free(G);
}

/* */
void inserir_aresta (Grafo *G, int u, int v) {
   Vertice *temp, *ultimo = NULL;
   /* Verificando se o vértice v já existe na lista de adjacência de u: */
   for (temp = G->listaAdj[u]; temp != NULL; temp = temp->proximo) {
      if (temp->identificador == v) {
         return;
      }
      ultimo = temp;
   }
   /* Inserindo a aresta (u,v): */
   Vertice *novo = (Vertice *)malloc(sizeof(Vertice));
   novo->identificador = v;
   novo->proximo = NULL;
   if (ultimo != NULL) {
      /* Inserção na última posição da lista: */
      ultimo->proximo = novo; 
   }
   else { 
      /* Nova cabeça da lista: */
      G->listaAdj[u] = novo; 
   }
   /* Incrementando o número de arestas: */
   G->E++; 
}

/* */
void imprimir_grafo (Grafo *G) {
   printf("Lista de adjacência de G:\n");
   int v;
   for (v = 0; v < G->V; v++) {
      if (G->listaAdj[v] != NULL) {
         Vertice *temp;
         printf("Nó %d : ", v);
         for (temp = G->listaAdj[v]; temp != NULL; temp = temp->proximo) {
            printf(" %d ", temp->identificador);
         }
         printf("\n");
      }
   }
}

/* */
void Busca_Largura (Grafo *G, int s) {
   int u;
   int tempo = 0;
   Vertice *V = (Vertice *)malloc(G->V * sizeof(Vertice));
   for (u = 0; u < G->V; u++) {
       V[u].cor = BRANCO;
       V[u].d = INFTY;
       V[u].pai = -1;

       if(u == s){
           V[u].cor=CINZA;
           V[u].d = 0;
       }
   }
   
   Fila *Q = create_queue (G->V);
   enqueue(Q, s);
   while (!empty(Q)) {
      int u = dequeue (Q);
      Vertice *v = G->listaAdj[u];
      while(v){
          if(V[v->identificador].cor==BRANCO){
              V[v->identificador].cor=CINZA;
              V[v->identificador].d=V[u].d+1;
              V[v->identificador].pai=u;
              enqueue(Q,v->identificador);
          }
          V[u].cor = PRETO;
          v=v->proximo;
      }
   }
   printf("Busca em largura:\n");
   for (u = 0; u < G->V; u++) {
      printf("%d = [d: %d, pai: %d]\n", u, V[u].d, V[u].pai);
   }
   free(V);
}

/* */
int main () {

   int tamanho = 8; /*Número de vértices!*/   

   Grafo *G = criar_grafo (tamanho);

   /* Ordem dos vértices da busca em
      largura vista em aula:
      7  0  1  2
      6  5  4  3
   */

   /*Inserção das arestas conforme a aula: */
   inserir_aresta(G, 0, 7);
   inserir_aresta(G, 7, 0);
   inserir_aresta(G, 0, 5);
   inserir_aresta(G, 5, 0);
   inserir_aresta(G, 1, 2);
   inserir_aresta(G, 2, 1);
   inserir_aresta(G, 1, 4);
   inserir_aresta(G, 4, 1);
   inserir_aresta(G, 1, 5);
   inserir_aresta(G, 5, 1);
   inserir_aresta(G, 2, 3);
   inserir_aresta(G, 3, 2);
   inserir_aresta(G, 2, 4);
   inserir_aresta(G, 4, 2);
   inserir_aresta(G, 3, 4);
   inserir_aresta(G, 4, 3);
   inserir_aresta(G, 4, 5);
   inserir_aresta(G, 5, 4);
   inserir_aresta(G, 6, 7);
   inserir_aresta(G, 7, 6);

   imprimir_grafo (G);

   Busca_Largura (G, 0);

   liberar_grafo (G);

   return 0;
}