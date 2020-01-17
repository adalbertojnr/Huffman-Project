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
FILA* criar_fila_vazia()
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

//Recebe um no e retorna true caso seja um no folha.
bool eh_folha(NO *no)
{
    return(no->dir == NULL && no->esq == NULL);
}

//Adiciona uma strings na hash.
void adicionar_strings_na_hash(HT *ht, void *item, char *caminho)
{
    int h = (unsigned char*)item;
    strcpy(ht->tabela[h]->caminho, caminho);
}

//Cria e salva todos os caminhos em seu respectivo lugar da hash.
void criar_caminho_na_hash(NO *raiz_arvore, HT *ht, char *caminho, int contador)
{
    if(eh_folha(raiz_arvore)){
        caminho[contador] = '\0';
        adicionar_strings_na_hash(ht, raiz_arvore->item, caminho);
    }else{
        caminho[contador] = '0';
        criar_caminho_na_hash(raiz_arvore->esq, ht, caminho, contador+1);
        caminho[contador] = '1';
        criar_caminho_na_hash(raiz_arvore->dir, ht, caminho, contador+1);
    }
}

//Calcula o tamanho do lixo a partir da hash.
int calcula_tam_lixo(HT *ht)
{

}

//Calcula o tamanho da arvore.
void calcula_tam_arvore(NO *raiz_arvore, int *tamanho)
{
    if(eh_folha(raiz_arvore)){
        return;
    }else{
        tamanho += 2;
        calcula_tam_arvore(raiz_arvore->dir, &tamanho);
        calcula_tam_arvore(raiz_arvore->esq, &tamanho);
    }
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
            unsigned char *caracter = (unsigned char*) malloc(sizeof(unsigned char));
            *caracter = i;
            NO *no = criar_no(caracter, ht->tabela[i]->frequencia);
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
        NO *novo_no = (NO*) malloc(sizeof(NO));

        unsigned char *caracter = (unsigned char*) malloc(sizeof(unsigned char)); //Para setar como '*' utilizando os 8 bits.
        *caracter = '*';
        novo_no->item = caracter;

        novo_no->frequencia = no_1->frequencia + no_2->frequencia;
        novo_no->dir = no_2;
        novo_no->esq = no_1;
        enfileirar(fila, novo_no);
        criar_arvore_huffman(fila);
    }else{
        return fila->cabeca;
    }
}