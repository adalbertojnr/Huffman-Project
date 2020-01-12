#include "suporte.h"

//APAGAR TUDO ISSO QUANDO ACABAR O SUPORTE.C
/*typedef struct NO{
    void *item;
    int frequencia;
    struct NO *prox;
    struct NO *esq;
    struct NO *dir;
}NO;

typedef struct FILA{
    struct NO *cabeca;
}FILA;  

typedef struct ELEMENTO{
    char caminho[H_MAX];  // H_MAX = altura máxima
    long long int frequencia;
}ELEMENTO;

typedef struct HT{
    ELEMENTO *tabela[MAX];
}HT;*/
// APAGAR TUDO ISSO ACIMA


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
    nova_fila->cabeca = NULL;
    return nova_fila;
}

int fila_vazia(FILA *fila)
{
    return (fila->cabeca == NULL);
}

//Adiciona um no na fila.
void enfileirar(FILA *fila, void *item, int frequencia)
{
    NO *novo_no = criar_no(item, frequencia);

    if( (fila_vazia(fila)) || ( frequencia <= (fila->cabeca->frequencia) ) ){
        novo_no->prox = fila->cabeca;
        fila->cabeca = novo_no;
    }else{
        NO *auxiliar = fila->cabeca;
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
    NO *auxiliar = fila->cabeca;
    fila->cabeca = fila->cabeca->prox;
    auxiliar->prox = NULL;
    return auxiliar;
}

//Cria um ELEMENTO vazio.
ELEMENTO* criar_elemento()
{
    ELEMENTO *novo_elemento = (ELEMENTO*) malloc(sizeof(ELEMENTO));
    novo_elemento->frequencia = 0;
    return novo_elemento;
}

//Cria uma hash table vazia.
HT* criar_hash_table()
{
    HT *nova_ht = (HT*) malloc(sizeof(HT));
    int i;
    for(i=0; i<MAX; i++){
        nova_ht->tabela[i] = criar_elemento();
    }
    return nova_ht;
}

//Adciona um elemento na tabela.
void adcionar_na_hash(HT *ht, int chave, char *caminho, int frequencia)
{
}

//Retorna 1 se o elemento encontra-se na tabela.
int contem_chave(HT *ht, int chave)
{
    int h = chave%MAX;
    return( !(ht->tabela[h] == NULL) );
}