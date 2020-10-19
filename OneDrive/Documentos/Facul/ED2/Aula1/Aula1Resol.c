#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct arvore{
    char info;
    struct arvore *esq;
    struct arvore *dir;
}Arvore;

Arvore* criaArvoreVazia(){
    return NULL;
}

Arvore* constroiArvore(char info, Arvore* e, Arvore* d){
    Arvore* a = (Arvore*)malloc(sizeof(Arvore));
    a->info = info;
    a->esq = e;
    a->dir = d;
    return a;
}

void destroiArvore (Arvore *a) {
   if (a != NULL) {
      destroiArvore (a->esq); 
      destroiArvore (a->dir);
      free(a); 
   }
}

char verificaArvoreVazia(Arvore* a){
    return (a==NULL);
}

void liberaArv(Arvore* a){
    if(!verificaArvoreVazia(a)){
        liberaArv(a->esq);
        liberaArv(a->dir);
        free(a);
    }
}

int pertenceArv(Arvore* a, char info){
    if(verificaArvoreVazia(a))
        return 0;
    if(info == a->info)
        return 1;
    if(info < a->info)
        return pertenceArv(a->esq, info);
    if(info > a->info)
        return pertenceArv(a->dir, info);

}

void preOrdem(Arvore* a){
    if(a != NULL){
        printf("%c ", a->info);
        preOrdem(a->esq);
        preOrdem(a->dir);
    }
}

void imprimeArvMarcadores(Arvore* a){
    if(a != NULL){
        printf("<");
        printf("%c", a->info);
        imprimeArvMarcadores(a->esq);
        imprimeArvMarcadores(a->dir);
        printf(">");
    }
    else
        printf("<>"); 
}

void inOrdem(Arvore* a){
    if(a != NULL){
        inOrdem(a->esq);
        printf("%c ", a->info);
        inOrdem(a->dir);
    }
}

void posOrdem(Arvore* a){
    if(a != NULL){
        posOrdem(a->esq);
        posOrdem(a->dir);
        printf("%c ", a->info);

    }
}

int max (int a, int b){
    return (a>b ? a:b);
}

int calculaAltura(Arvore* a){
    if(verificaArvoreVazia(a))
        return -1;
    else{
        return (1 + max(calculaAltura(a->esq), calculaAltura(a->dir)));
    }
}

int contaNos(Arvore* a){
    if(verificaArvoreVazia(a))
        return 0;
    else{
        return pow(2, calculaAltura(a)+1)-1;
    }
}

int contaNosFolhas(Arvore* a){
    if(verificaArvoreVazia(a))
        return 0;
    else{
        return pow(2, calculaAltura(a)-1);
    }
}

int main(){
    Arvore *a = constroiArvore ('a', constroiArvore('b', criaArvoreVazia(), constroiArvore('d',criaArvoreVazia(),criaArvoreVazia())),
        constroiArvore('c', constroiArvore('e',criaArvoreVazia(),criaArvoreVazia()), constroiArvore('f',criaArvoreVazia(),criaArvoreVazia())));
    printf("%d", contaNosFolhas(a));
}