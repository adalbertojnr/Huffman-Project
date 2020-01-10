#include <stdio.h>
#include <string.h>
#define MAX 256

typedef struct NO{
    void *item;
    int freq;
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
    ELEMENTO* tabela[MAX];
}HT;


//Cria um no com seu respectivo item e frequencia.
NO* criar_no(void *item, int frequencia);

//Cria uma Fila vazia.
FILA* criar_fila();

//Adiciona um no na fila.
void enfileirar(FILA *fila, NO *no);

//retorna um no e o remove da fila.
NO* desenfileirar(FILA *fila);

//Cria uma hash table vazia.
HT* criar_hash_table();

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

//Retorna 1 caso a fila seja vazia e 0 caso contrario.
int fila_vazia(FILA *fila);