#include "compress.h"
#include "decompress.h"
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
	hash *newHash = NULL;
	CU_ASSERT(newHash == NULL);
	newHash = createHash(10);
	CU_ASSERT(newHash != NULL);
}

void generate_tree_test_string(huffmanTree *huffmanRoot, char *string, int *size) {
	if(huffmanRoot == NULL) {
		string[*size] = '\0';
		return;
	} else {
		if(isLeaf(huffmanRoot)) {
			string[*size] = huffmanRoot-> element;
			*size += 1;
		}
		generate_tree_test_string(huffmanRoot->left,string,size);		
		generate_tree_test_string(huffmanRoot->right,string,size);
	}
}

huffmanTree *build_tree_test(pqueue *priorityQueue){

  huffmanTree * first_dequeued;
  huffmanTree * second_dequeued;
  int frequency;

  while(((node*)priorityQueue->head)->next != NULL){                    

    first_dequeued = priorityDequeue(priorityQueue);
    second_dequeued = priorityDequeue(priorityQueue);

    frequency = (first_dequeued->freq) + (second_dequeued->freq);

    huffmanTree * enqueued = newNode('*',frequency);

    enqueued->left = first_dequeued;
    enqueued->right = second_dequeued;

    priorityEnqueue(priorityQueue,enqueued);
  }

  return (huffmanTree*)((node*)priorityQueue->head)->item;
}

void  huff_tree_tests () {
	pqueue * priorityQueue = createPriorityQueue();
	char string_test[10], string_compare[10];
	int i, size = 0;
	huffmanTree *huffmanRoot;
	huffmanTree *auxiliar;

	auxiliar = newNode('a',5);
	priorityEnqueue(priorityQueue,auxiliar);
	auxiliar = newNode('b',2);
	priorityEnqueue(priorityQueue,auxiliar);
	auxiliar = newNode('c',1);
	priorityEnqueue(priorityQueue,auxiliar);
	auxiliar = newNode('d',3);
	priorityEnqueue(priorityQueue,auxiliar);

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
	pqueue *priorityQueue = createPriorityQueue();
	huffmanTree *auxiliar = NULL;

	//testando create_p_queue
	CU_ASSERT(priorityQueue != NULL);
	CU_ASSERT(priorityQueue->head == NULL);

	//testando enqueue
	auxiliar = newNode('a',5);
	priorityEnqueue(priorityQueue,auxiliar);
	auxiliar = newNode('b',2);
	priorityEnqueue(priorityQueue,auxiliar);
	auxiliar = newNode('c',1);
	priorityEnqueue(priorityQueue,auxiliar);
	auxiliar = newNode('d',3);
	priorityEnqueue(priorityQueue,auxiliar);
	auxiliar = newNode('e', 1);
	priorityEnqueue(priorityQueue,auxiliar);
	
	
	CU_ASSERT(((huffmanTree*)priorityQueue->head->item)->element == 'e'); 
	CU_ASSERT(((huffmanTree*)priorityQueue->head->item)->freq == 1);
	CU_ASSERT(((huffmanTree*)priorityQueue->head->next->item)->element == 'c');
	CU_ASSERT(((huffmanTree*)priorityQueue->head->next->item)->freq == 1); 
	

	//testando dequeue
	huffmanTree *node_teste = priorityDequeue(priorityQueue);
	CU_ASSERT(node_teste->element == 'e');
	CU_ASSERT(node_teste->freq == 1);
	node_teste = priorityDequeue(priorityQueue);
	CU_ASSERT(node_teste->element == 'c');
	CU_ASSERT(node_teste->freq == 1);
	CU_ASSERT(((huffmanTree*)priorityQueue->head->item)->element == 'b');
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