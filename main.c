#include <stdio.h>
#include <stdlib.h>

typedef struct arvore {  
   int info;
   struct arvore *esq;
   struct arvore *dir;
} Arvore;

Arvore* cria_arvore_vazia (void) {
   return NULL;
}

void arvore_libera (Arvore* a) {
   if (a != NULL) {
      arvore_libera (a->esq);
      arvore_libera (a->dir);
      free(a);
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
int buscar (Arvore *a, int v) {
   if (a == NULL)
       return 0;
   if (v == a->info)
       return 1;
   if (v < a->info) 
       return buscar(a->esq, v);
   else 
       return buscar(a->dir, v);
  return 1; 
    
}

Arvore* inserir (Arvore *a, int v) {
   if(a == NULL){
       a = (Arvore*)malloc(sizeof(Arvore));
       a->info = v;
       a->esq = NULL;
       a->dir = NULL;
   }
   else if(buscar(a, v)){
       return a;
   }
   else if(v < a->info){
       a->esq = inserir(a->esq, v);
   }
   else{
       a->dir = inserir(a->dir, v);
   }
   return a;
}

Arvore* remover (Arvore *a, int v) {
    if(a==NULL)
        return NULL;
    else if(!buscar(a,v)){
        printf ("Esse elemento nao existe na arvore!\n");
    }
    else{
        if(a->info > v)
            a->esq = remover(a->esq, v);
        else if(a->info < v)
            a->dir = remover(a->dir, v);
        else{
            if((a->esq == NULL) && (a->dir == NULL)){
                free(a);
                a = NULL;
            }
            else if(a->dir == NULL){
                Arvore* aux = a;
                a = a->esq;
                free(aux);
            }
            else if(a->esq == NULL){
                Arvore* aux = a;
                a = a->dir;
                free(aux);
            }
            else{
                Arvore* aux = a->esq;
                while (aux->dir != NULL){
                    aux = aux->dir;
                }
                a->info = aux->info;
                aux->info = v;
                a->esq = remover(a->esq, v);
            }
        }
    }
    return a;
}


//Exercicio 2
int min (Arvore* a){
    int m = a->info;
    if(a != NULL){
        if(a->esq != NULL){
            m = min (a->esq);
        }
        return m;
    }
    else{
        return NULL;
    }
}

int max (Arvore *a){
    int m = a->info;
    if(a != NULL){
        if(a->dir != NULL){
            m = max (a->dir);
        }
        return m;
    }
    else{
        return NULL;
    }
}


//Exercicio 3
void inserirNumOrd(){
    Arvore* a = cria_arvore_vazia();
    int i;
    for(i=0; i<100000; i++){
        a = inserir (a, i);
    }
    pre_order(a);
    printf("\n");
    int flag = buscar(a, 100000);
    if(flag)
        printf("Achou o valor!");
    else
        printf("Nao achou o valor!");
    
}


//Exercicio 4 
void inserirNumNaoOrd(){
    int vetor[100000];
    int i;
    for(i=0; i< 100000; i++){
        vetor[i] = rand()% 9;
        printf("%d ", vetor[i]);
    }
    Arvore* a = cria_arvore_vazia();

    printf("\n");
    int j;
    for(j=0; j<100000; j++){        
        a = inserir(a, vetor[j]);
    }
    pre_order(a);
    printf("\n");
    int flag = buscar(a, 10000);
    if(flag)
        printf("Achou o valor!");
    else
        printf("Nao achou o valor!");
}


//Exercicio 5
void inOrdemMod(Arvore *a){
    if( a != NULL){
       inOrdemMod(a->dir);
       printf("%d ", a->info);
       inOrdemMod(a->esq);
    }
}

void imprime_decrescente (Arvore *a){
    if( a != NULL){
        inOrdemMod(a->dir);
        printf("%d ", a->info);
        inOrdemMod(a->esq);
    }
}


//Exercicio 6
int maior_ramo (Arvore *a){
    if(a != NULL){
        int esq = maior_ramo(a->esq);
        int dir = maior_ramo(a->dir);
        if (esq > dir) 
            return a->info + esq;
        
        else 
            return a->info + dir;
        
    }
    return NULL;
}


//Exercicio 7 
int ancestral (Arvore *a, int e1, int e2){
    if(a == NULL)
        return NULL;
    if(a->info == e1 || a->info == e2){
        return a->info;
    }
    int esq = ancestral(a->esq, e1, e2);
    int dir = ancestral(a->dir, e1, e2);
    if(esq != NULL && dir != NULL)
        return a->info;
    if(esq == NULL && dir == NULL)
        return NULL;
    return (esq != NULL ? esq : dir);
}


int main () {

   Arvore *a = cria_arvore_vazia ();

   a = inserir (a, 50);
   a = inserir (a, 30);
   a = inserir (a, 90);
   a = inserir (a, 20);
   a = inserir (a, 40);
   a = inserir (a, 95);
   a = inserir (a, 10);
   a = inserir (a, 35);
   a = inserir (a, 37);


   printf("\n");   

   return 0;
}