#include <CUnit/Basic.h>
#include <stdio.h>
#include <stdlib.h>
#include "suporte.c"

NO* teste_criar_no()
{
    NO *novo_no = (NO*) malloc(sizeof(NO));
    novo_no->item = (unsigned char*)'a'; // unsigned char qualquer
    novo_no->frequencia = 10; // frequencia qualquer
    novo_no->prox = NULL;
    novo_no->esq = NULL;
    novo_no->dir = NULL;

    CU_ASSERT(novo_no != NULL);
    CU_ASSERT(novo_no->frequencia == 10);
    CU_ASSERT((char*)novo_no->item == 'a');
    CU_ASSERT(novo_no->prox == NULL);
    CU_ASSERT(novo_no->esq == NULL);
    CU_ASSERT(novo_no->dir == NULL);

    return novo_no;
}

FILA* teste_criar_fila_vazia()
{
    FILA *nova_fila = (FILA*) malloc(sizeof(FILA));
    nova_fila->cabeca = NULL;

    CU_ASSERT(nova_fila->cabeca == NULL);
    return nova_fila;
}

ELEMENTO* teste_criar_elemento()
{
    ELEMENTO *novo_elemento = (ELEMENTO*) malloc(sizeof(ELEMENTO));
    novo_elemento->frequencia = 0;

    CU_ASSERT(novo_elemento->frequencia == 0);
    return novo_elemento;
}

void teste_bit_esta_setado()
{
    unsigned char aux = 255;

    CU_ASSERT(bit_esta_setado(aux, 7));
    CU_ASSERT(bit_esta_setado(aux, 6));
    CU_ASSERT(bit_esta_setado(aux, 5));
    CU_ASSERT(bit_esta_setado(aux, 4));
    CU_ASSERT(bit_esta_setado(aux, 3));
    CU_ASSERT(bit_esta_setado(aux, 2));
    CU_ASSERT(bit_esta_setado(aux, 1));
    CU_ASSERT(bit_esta_setado(aux, 0));
}

HT* teste_criar_hash_table()
{
    HT *nova_ht = (HT*) malloc(sizeof(HT));
    int i;
    for(i=0; i<MAX; i++){
        nova_ht->tabela[i] = criar_elemento();
        CU_ASSERT(nova_ht->tabela[i]->frequencia == 0);
    }

    return nova_ht;
}

int main(){
    if (CUE_SUCCESS != CU_initialize_registry()) {
        return CU_get_error();
    }
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_pSuite pSuite = NULL, pSuite2 = NULL;
    pSuite = CU_add_suite("TESTES", 0, 0);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if (NULL == CU_add_test(pSuite, "teste - 1", teste_criar_no)) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    if (NULL == CU_add_test(pSuite, "teste - 2", teste_criar_fila_vazia)) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    if (NULL == CU_add_test(pSuite, "teste - 3", teste_criar_elemento)) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    if (NULL == CU_add_test(pSuite, "teste - 4", teste_bit_esta_setado)){
        CU_cleanup_registry();
        return CU_get_error();
    }
    if (NULL == CU_add_test(pSuite, "teste - 5", teste_criar_hash_table)){
        CU_cleanup_registry();
        return CU_get_error();
    }

    CU_basic_run_tests();
    return CU_get_error();
}