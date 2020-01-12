#ifndef suporte.h
    #define suporte.h
    #include <stdio.h>
    #include <string.h>
    #define MAX 256
    #define H_MAX 31

    typedef struct NO{
        void *item;
        int freq;
        struct NO *prox;
        struct NO *esq;
        struct NO *dir;
    }NO;

    typedef struct FILA{
        struct NO *cabeca;
    }FILA;

    typedef struct ELEMENTO{
        char caminho[31]; // 31 = altura máxima
        long long int frequencia;
    }ELEMENTO;

    typedef struct HT{
        ELEMENTO* tabela[MAX];
    }HT;


    //Cria um NO com seu respectivo item e frequencia.
    NO* criar_no(void *item, int frequencia);

    //Cria uma FILA vazia.
    FILA* criar_fila();

    //Adiciona um NO na fila.
    void enfileirar(FILA *fila, NO *no);

    //Retorna um NO e o remove da fila.
    NO* desenfileirar(FILA *fila);

    //Cria um ELEMENTO vazio.
    ELEMENTO* criar_elemento();

    //Cria uma hash table vazia.
    HT* criar_hash_table();

    //Adciona um ELEMENTO na tabela.
    void adcionar_na_hash(HT *ht, int chave, char *caminho, int frequencia);

    //Retorna 1 se o ELEMENTO encontra-se na tabela.
    int contem_chave(HT *ht, int chave);

    //Retorna 1 caso a FILA seja vazia e 0 caso contrario.
    int fila_vazia(FILA *fila);
#endif