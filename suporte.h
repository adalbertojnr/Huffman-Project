#ifndef suporte_h
    #define suporte_h
    #include <stdio.h>
    #include <string.h>
    #include <stdlib.h>
    #include <stdbool.h>
    #include "compactar.h"
    #include "descompactar.h"
    #define MAX 256
    #define ALTURA_MAX 31

    typedef struct NO{
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
        char caminho[ALTURA_MAX]; //ALTURA_MAX = 31 = altura máxima
        long long int frequencia;
    }ELEMENTO;

    typedef struct HT{
        ELEMENTO* tabela[MAX]; //Numero de elementos na tabela ASCII
    }HT;

    //Verifica se a arvore eh vazia.
    int is_empty(NO *bt);

    //Imprime a arvore em pre ordem no arquivo saida.
    void imprimir_pre_ordem(FILE *arquivo, NO *bt)

    //Printa todos os bits de dados no arquivo saida.
    void imprimir_bits_dados(FILE *arquivo, NO *bt);

    //Seta apenas um bit desginado.
    unsigned char setar_um_bit(unsigned char c, int i);

    //Seta determinados bits.
    unsigned char setar_bits(unsigned char c, int tamanho);

    //Adiciona uma strings na hash.
    void adicionar_strings_na_hash(HT *ht, NO *arvore);

    //Cria um NO com seu respectivo item e frequencia.
    NO* criar_no(void *item, int frequencia);

    //Cria uma FILA vazia.
    FILA* criar_fila_basica();

    //Adiciona um NO na fila.
    void enfileirar(FILA *fila, NO *no);

    //Retorna um NO e o remove da fila.
    NO* desenfileirar(FILA *fila);

    //Cria um ELEMENTO vazio.
    ELEMENTO* criar_elemento();

    //Cria uma hash table vazia.
    HT* criar_hash_table();

    //Recebe um no e retorna true caso seja um no folha.
    bool eh_folha(NO *no);

    //Cria e salva todos os caminhos em seu respectivo lugar da hash.
    void criar_caminho_na_hash(NO *raiz_arvore, HT *ht, char *caminho, int contador);

    //Retorna 1 se o ELEMENTO encontra-se na tabela.
    int contem_chave(HT *ht, int chave);

    //Retorna 1 caso a FILA seja vazia e 0 caso contrario.
    int fila_vazia(FILA *fila);

    //Calcula o valor da frequencia de cada caractere e adiciona em seus respectivos elementos na hash table.
    void adicionar_cada_frequencia(FILE *arquivo, HT *ht);

    //Partindo de uma fila vazia a transforma na fila de prioridade de huffman, enfileirando seus itens e respectivas frequencias.
    FILA* criar_fila_prioridade(HT *ht, FILA *fila);

    //Calcula o tamanho do lixo a partir da hash.
    int calcula_tam_lixo(HT *ht);

    //Calcula o tamanho da arvore.  
    void calcula_tam_arvore(NO *raiz_arvore, unsigned short *tamanho);

    //Transforma a fila de prioridade em um formato de arvore de huffman.
    NO* criar_arvore_huffman(FILA *fila);
#endif