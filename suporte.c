#include "suporte.h"

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

//Cria uma Fila simples vazia.
FILA* criar_fila_basica()
{
    FILA *nova_fila = (FILA*) malloc(sizeof(FILA));
    nova_fila->cabeca = NULL;
    return nova_fila;
}

//Retorna 1 caso a FILA seja vazia e 0 caso contrario.
int fila_vazia(FILA *fila)
{
    return (fila->cabeca == NULL);
}

//Adiciona um no na fila.
void enfileirar(FILA *fila, NO *no)
{
    if( (fila_vazia(fila)) || ( no->frequencia <= (fila->cabeca->frequencia) ) ){
        no->prox = fila->cabeca;
        fila->cabeca = no;
    }else{
        NO *auxiliar = fila->cabeca;
        while ( (auxiliar->prox != NULL) && ( auxiliar->prox->frequencia < no->frequencia) ) {
            auxiliar = auxiliar->prox;
        }
        no->prox = auxiliar->prox;
        auxiliar->prox = no;
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

//Calcula o valor da frequencia de cada caractere e adiciona em seus respectivos elementos na hash table.
void adicionar_cada_frequencia(FILE *arquivo, HT *ht)
{
    int num;
    while( (num = fgetc(arquivo) ) != EOF){
        ht->tabela[num]->frequencia += 1;
    }
}

//Partindo de uma fila vazia a transforma na fila de prioridade de huffman, enfileirando seus itens e respectivas frequencias.
FILA* criar_fila_prioridade(HT *ht, FILA *fila)
{
    int i;
    for(i=0; i<256; i++){
        if(ht->tabela[i]->frequencia != 0){
            unsigned char *caractere = (unsigned char*) malloc(sizeof(unsigned char));
            *caractere = i;
            NO *no = criar_no(caractere, ht->tabela[i]->frequencia);
            enfileirar(fila, no);
        }
    }
    return fila;
}

//Transforma a fila de prioridade em um formato de arvore de huffman.
NO* criar_arvore_huffman(FILA *fila)
{
    if(fila->cabeca->prox != NULL){
        NO *no_1 = desenfileirar(fila);
        NO *no_2 = desenfileirar(fila);
        NO *new_node = (NO*) malloc(sizeof(NO));

        unsigned char *caracter = (unsigned char*) malloc(sizeof(unsigned char)); //Para setar como '*' utilizando os 8 bits.
        *caracter = '*';
        new_node->item = caracter;

        new_node->frequencia = no_1->frequencia + no_2->frequencia;
        new_node->dir = no_2;
        new_node->esq = no_1;
        enfileirar(fila, new_node);
        criar_arvore_huffman(fila);
    }else{
        return fila->cabeca;
    }
}