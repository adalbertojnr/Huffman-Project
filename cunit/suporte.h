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

    //Cria um NO com seu respectivo item e frequencia.
    NO* criar_no(unsigned char item, int frequencia);

    //Retorna 1 caso a FILA seja vazia e 0 caso contrario.
    bool fila_vazia(FILA *fila);

    //Cria uma FILA vazia.
    FILA* criar_fila_vazia();

    //Adiciona um NO na fila.
    void enfileirar(FILA *fila, NO *no);

    //Retorna um NO e o remove da fila.
    NO* desenfileirar(FILA *fila);

    //Partindo de uma fila vazia a transforma na fila de prioridade de huffman, enfileirando seus itens e respectivas frequencias.
    FILA* criar_fila_prioridade(HT *ht, FILA *fila);

    //Recebe um no e retorna true caso seja um no folha.
    bool eh_folha(NO *no);

    //Transforma a fila de prioridade em um formato de arvore de huffman.
    void criar_arvore_huffman(FILA *fila);

    //Calcula o tamanho da arvore.  
    void calcula_tam_arvore(NO *raiz_arvore, unsigned short *tamanho);

    //Imprime a arvore em pre ordem no arquivo saida.
    void imprimir_pre_ordem(FILE *arquivo, NO *raiz_arvore);

    //Cria um ELEMENTO vazio.
    ELEMENTO* criar_elemento();

    //Cria uma hash table vazia.
    HT* criar_hash_table();

    //Calcula o valor da frequencia de cada caractere e adiciona em seus respectivos elementos na hash table.
    void adicionar_cada_frequencia(FILE *arquivo, HT *ht);

    //Adiciona uma strings na hash.
    void adicionar_strings_na_hash(HT *ht, void *item, char *caminho);

    //Cria e salva todos os caminhos em seu respectivo lugar da hash.
    void criar_caminho_na_hash(NO *raiz_arvore, HT *ht, char *caminho, int contador);

    //Seta apenas um bit desginado.
    unsigned char setar_um_bit(unsigned char c, int i);

    //Seta determinado conjunto de bits.
    unsigned short setar_bits(unsigned short c, unsigned short *tamanho);

    //Calcula o tamanho do lixo a partir da hash.
    int calcula_tam_lixo(HT *ht);

    //Printa todos os bits de dados no arquivo saida.
    void imprimir_bits_dados(FILE *entrada, FILE *saida, HT *ht);
    
    //DESCOMPACTAR - FUNCOES

    //Realiza as chamadas das funções para descompactar.
    void descompactar();

    //Realiza a descompressão propriamente dita.
    int descompressao(FILE *compactado, char *nome);

    //Monta a árvore a partir do arquivo compactado.
    NO *montar_arvore(FILE *compactado);

    //Cria um NO com um caractere inserido.
    NO *criar_no_arvore(unsigned char caractere);

    //Escreve o arquivo descompactado
    void printar_byte(FILE* compactado, FILE* descompactado, NO *raiz, short tamanho_arvore, short tamanho_lixo, int tamanho_arquivo);

    //Verifica se o bit dado está setado.
    bool bit_esta_setado(unsigned char c, int i);
#endif