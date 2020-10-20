#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <time.h>
#include<sys/time.h>
#define TIME_UTC 1

typedef struct arvore{
    int info;
    struct arvore* esq;
    struct arvore* dir;
}Arvore;

Arvore* cria_arvore_vazia (void) {
   return NULL;
}

int verificaArvoreVazia(Arvore* a){
    return (a==NULL);
}

void LiberaArvore(Arvore* a){
    if(!verificaArvoreVazia(a)){
        LiberaArvore(a->esq);
        LiberaArvore(a->dir);
        free(a);
    }
}

void in_order(Arvore *a)
{
  if (a != NULL)
  {
    in_order(a->esq);
    printf("%d ", a->info);
    in_order(a->dir);
  }
}

void pre_order (Arvore* a) {
   if (a != NULL) {
      printf("%d ", a->info);
      pre_order (a->esq);
      pre_order (a->dir);
   } 
}

//Exercicio 1
int Buscar(Arvore* a, int key){
    if(verificaArvoreVazia(a))
        return 0;
    else if(a->info == key){
        return 1;
    }
    else if (key < a->info){
        return Buscar(a->esq, key);
    }
    else{
        return Buscar(a->dir, key);
    }
}

Arvore* Inserir(Arvore* a, int key){
    if(verificaArvoreVazia(a)){
        a = (Arvore*)malloc(sizeof(Arvore));
        a->info = key;
        a->esq = NULL;
        a->dir = NULL;
    }
    //caso de nao deixar elementos repetidos serem anexados
    else if(Buscar(a, key)){
        return a;
    }
    else if(key < a->info){
        a->esq = Inserir(a->esq, key);
    }
    else{
        a->dir = Inserir(a->dir, key);
    }
    return a;
}

Arvore* Remover (Arvore* a, int key){
    if(verificaArvoreVazia(a))
        return NULL;
    //Caso em que o elemento não pode ser removido pois não pertence à arvore
    else if(!Buscar(a, key)){
        printf("Esse elemento nao existe na arvore!\n");
    }
    else{
        if(a->info > key){
            a->esq = Remover(a->esq, key);
        }else if(a->info < key){
            a->dir = Remover(a->dir, key);
        }else{
            if(verificaArvoreVazia(a->esq)&&(verificaArvoreVazia(a->dir))){
                free(a);
                a = NULL;
            }else if(verificaArvoreVazia(a->dir)){
                Arvore* aux = a;
                a = a->esq;
                free(aux);
            }else if(verificaArvoreVazia(a->esq)){
                Arvore* aux = a;
                a = a->dir;
                free(aux);
            }else{
                Arvore* aux = a->esq;
                while(!verificaArvoreVazia(a->dir)){
                    aux = aux->dir;
                }
                a->info = aux->info;
                aux->info=key;
                a->esq = Remover(a->esq, key);
            }
        }
    }
    return a;
}

//Exercício 2
int min (Arvore* a){
    int m = a->info;
    if(!verificaArvoreVazia(a)){
        if(!verificaArvoreVazia(a->esq)){
            m = min(a->esq);
        }
        return m;
    }else{
        return INT_MAX;
    }
}

int max(Arvore* a){
    int m = a->info;
    if(!verificaArvoreVazia(a)){
        if(!verificaArvoreVazia(a->dir))
            m = max(a->dir);
        return m;
    }else{
        return INT_MIN;
    }
}

//Exercício 3
Arvore* ArvoreOrd(int n){
    Arvore* a = cria_arvore_vazia();
    int i;
    for(i=0; i<n; i++){
        a = Inserir (a, i);
    }
    
    return a;
}

//Exercício 4
Arvore* ArvoreNaoOrd(int n){
    srand(time(NULL));
    Arvore* a = cria_arvore_vazia();
    int i;
    for(i=0; i<n; i++){
        a = Inserir (a, rand());
    }
    
    return a;
}

//Exercício 5
void imprime_decrescente (Arvore *a){
    if( !verificaArvoreVazia(a)){
        imprime_decrescente(a->dir);
        printf("%d ", a->info);
        imprime_decrescente(a->esq);
    }
}

//Exercício 6
int maior_ramo(Arvore* a){
   if(!verificaArvoreVazia(a)){
        int esq = maior_ramo(a->esq);
        int dir = maior_ramo(a->dir);
        if(esq > dir)
            return a->info + esq;
        else
            return a->info + dir;
   }
   return 0;
}

//Exercício 7
int ancestral (Arvore *a, int e1, int e2){
    if(a == NULL)
        return INT_MIN;
    if(a->info == e1 || a->info == e2){
        return a->info;
    }
    int esq = ancestral(a->esq, e1, e2);
    int dir = ancestral(a->dir, e1, e2);
    if(esq != INT_MIN && dir != INT_MIN)
        return a->info;
    if(esq == INT_MIN && dir == INT_MIN)
        return INT_MIN;
    return (esq != INT_MIN ? esq : dir);
}

int main () {
    Arvore *a;
    a = Inserir (a, 50);
    a = Inserir (a, 30);
    a = Inserir (a, 90);
    a = Inserir (a, 20);
    a = Inserir (a, 40);
    a = Inserir (a, 95);
    a = Inserir (a, 10);
    a = Inserir (a, 35);
    a = Inserir (a, 45);

    imprime_decrescente(a);
  
}



