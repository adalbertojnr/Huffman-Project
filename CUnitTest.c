#include "compactar.h"
#include "descompactar.h"
#include "suporte.h"
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>

int init_suite(void) {
	return 0;
}

int clear_suite(void) {
	return 0;
}

void hash_tests() {
	HT *newHash = NULL;
	CU_ASSERT(newHash == NULL);
	newHash = criar_hash_table();
	CU_ASSERT(newHash != NULL);
}

void generate_tree_test_string(NO *huffmanRoot, char *string, int *size) {
	if(huffmanRoot == NULL) {
		string[*size] = '\0';
		return;
	} else {
		if(eh_folha(huffmanRoot)) {
			string[*size] = (char*)huffmanRoot->item;
			*size += 1;
		}
		generate_tree_test_string(huffmanRoot->esq,string,size);		
		generate_tree_test_string(huffmanRoot->dir,string,size);
	}
}

NO *build_tree_test(FILA *priorityQueue){

  NO * first_dequeued;
  NO * second_dequeued;
  int frequency;

  while(((NO*)priorityQueue->cabeca)->prox != NULL){                    

    first_dequeued = desenfileirar(priorityQueue);
    second_dequeued = desenfileirar(priorityQueue);

    frequency = (first_dequeued->frequencia) + (second_dequeued->frequencia);

    NO * enqueued = criar_no('*',frequency);

    enqueued->esq = first_dequeued;
    enqueued->dir = second_dequeued;

    enfileirar(priorityQueue,enqueued);
  }

  return (NO*)priorityQueue->cabeca->item;   //DFYGAKUKUGSFUAFYDSSYAKF
}

void  huff_tree_tests () {
	FILA * priorityQueue = criar_fila_vazia();
	char string_test[10], string_compare[10];
	int i, size = 0;
	NO *huffmanRoot;
	NO *auxiliar;

	auxiliar = criar_no('a',5);
	enfileirar(priorityQueue,auxiliar);
	auxiliar = criar_no('b',2);
	enfileirar(priorityQueue,auxiliar);
	auxiliar = criar_no('c',1);
	enfileirar(priorityQueue,auxiliar);
	auxiliar = criar_no('d',3);
	enfileirar(priorityQueue,auxiliar);

	for(i = 0; i < 10; i++) 
	{
		string_test[i] = '0';
		string_compare[i] = '0';
	}
	
	huffmanRoot = build_tree_test(priorityQueue);

	string_compare[0] = 'a';
	string_compare[1] = 'c';
	string_compare[2] = 'b';
	string_compare[3] = 'd';
	string_compare[4] = '\0';

	generate_tree_test_string(huffmanRoot, string_test, &size);
	CU_ASSERT(strcmp(string_test,string_compare) == 0);
}

void p_queue_tests(){
	FILA *priorityQueue = criar_fila_vazia();
	NO *auxiliar = NULL;

	//testando create_p_queue
	CU_ASSERT(priorityQueue != NULL);
	CU_ASSERT(priorityQueue->cabeca == NULL);

	//testando enqueue
	auxiliar = criar_no('a',5);
	enfileirar(priorityQueue,auxiliar);
	auxiliar = criar_no('b',2);
	enfileirar(priorityQueue,auxiliar);
	auxiliar = criar_no('c',1);
	enfileirar(priorityQueue,auxiliar);
	auxiliar = criar_no('d',3);
	enfileirar(priorityQueue,auxiliar);
	auxiliar = criar_no('e', 1);
	enfileirar(priorityQueue,auxiliar);
	
	
	CU_ASSERT((char*)((NO*)priorityQueue->cabeca->item)->item == 'e'); 
	CU_ASSERT(((NO*)priorityQueue->cabeca->item)->frequencia == 1);
	CU_ASSERT((char*)((NO*)priorityQueue->cabeca->prox->item)->item == 'c');
	CU_ASSERT(((NO*)priorityQueue->cabeca->prox->item)->frequencia == 1); 
	

	//testando dequeue
	NO *node_teste = desenfileirar(priorityQueue);
	CU_ASSERT((char*)node_teste->item == 'e');
	CU_ASSERT(node_teste->frequencia == 1);
	node_teste = desenfileirar(priorityQueue);
	CU_ASSERT((char*)node_teste->item == 'c');
	CU_ASSERT(node_teste->frequencia == 1);
	CU_ASSERT((char*)((NO*)priorityQueue->cabeca->item)->item == 'b');
}

int run_tests(){
	p_queue_tests();
	huff_tree_tests();
	hash_tests();
}

int main(){

	CU_pSuite pSuite = NULL;

	if(CUE_SUCCESS != CU_initialize_registry()) {
		return CU_get_error();
	}

	pSuite = CU_add_suite("Basic_Test_Suite", init_suite, clear_suite);
	if(pSuite == NULL){
		return CU_get_error();
	}

	if(NULL == CU_add_test(pSuite, "p_queue_tests", p_queue_tests)) {
		CU_cleanup_registry();
		return CU_get_error();
	}

	if(NULL == CU_add_test(pSuite, "huff_tree_tests", huff_tree_tests)) {
		CU_cleanup_registry();
		return CU_get_error();
	}

	if(NULL == CU_add_test(pSuite, "hash_tests", hash_tests)) {
		CU_cleanup_registry();
		return CU_get_error();
	}

	CU_basic_run_tests();
	CU_cleanup_registry();
	return CU_get_error();

	return CU_get_error();
}