#include <stdio.h>
#include <stdlib.h>
#define MAX 256

typedef struct NO{
    void *item;
    int frequencia;
    struct NO *prox;
    struct NO *esq;
    struct NO *dir;
}NO;

typedef struct FILA{
    struct NO *topo;
}FILA;  

typedef struct ELEMENTO{
    char caminho[30];
    long long int frequencia;
}ELEMENTO;

typedef struct HT{
    ELEMENTO *tabela[MAX];
}HT;

//Cria um no com seu respectivo item e frequencia.
NO* criar_no(void *item, int frequencia)
{
    NO *novo_no = (NO*) malloc(sizeof(NO));
    novo_no->item = item;
    novo_no->frequencia = frequencia;
    novo_no->prox = NULL;
    novo_no->esq = NULL;
    novo_no->dir = NULL;
    return novo_no;
}

//Cria uma Fila vazia.
FILA* criar_fila()
{
    FILA *nova_fila = (FILA*) malloc(sizeof(FILA));
    nova_fila->topo = NULL;
    return nova_fila;
}

int fila_vazia(FILA *fila)
{
    return (fila->topo == NULL);
}

//Adiciona um no na fila.
void enfileirar(FILA *fila, void *item, int frequencia)
{
    NO *novo_no = criar_no(item, frequencia);

    if( (fila_vazia(fila)) || ( frequencia <= (fila->topo->frequencia) ) ){
        novo_no->prox = fila->topo;
        fila->topo = novo_no;
    }else{
        NO *auxiliar = fila->topo;
        while ( (auxiliar->prox != NULL) && ( auxiliar->prox->frequencia < frequencia) ) {
            auxiliar = auxiliar->prox;
        }
        novo_no->prox = auxiliar->prox;
        auxiliar->prox = novo_no;
    }
}

//retorna um no e o remove da fila.
NO* desenfileirar(FILA *fila)
{
    if(fila_vazia(fila)) return;
    NO *auxiliar = fila->topo;
    fila->topo = fila->topo->prox;
    auxiliar->prox = NULL;
    return auxiliar;
}

//Cria uma hash table vazia.
HT* criar_hash_table()
{
    HT *nova_ht = (HT*) malloc(sizeof(HT));
    return nova_ht;
}

//Adciona um elemento na tabela.
void adcionar_na_hash(HT *ht, int key, int valor);

//Retorna um elemento da tabela a partir de sua chave.
int get(HT *ht, int key);

//Remove um elemento da tabela a partir de sua chave.
void remover(HT *ht, int key);

//Retorna 1 se o elemento encontra-se na tabela.
int contem_key(HT *ht, int key);

//Imprime a tabela.
void print_ht(HT *ht);