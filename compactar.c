#include "compactar.h"

//---------------------------------TESTES-------------------------------------//

void print_pre_order(NO *tree)
{
	if(tree != NULL){
    	printf("%c", (char*)(tree->item) );
        print_pre_order(tree->esq);
    	print_pre_order(tree->dir);
	}
}

void printar_fila(FILA *fila){
    NO *auxiliar = fila->cabeca;

    while(auxiliar->prox != NULL){
        printf("%c-", (char*)(auxiliar->item));
        auxiliar = auxiliar->prox;
    }
    printf("%c", (char*)(auxiliar->item));
}

void printar_hash(HT *ht){
    int i;

    for(i=0; i<256; i++){
        if((ht->tabela[i]->frequencia)>0){
            printf("Caracter: %c\nCaminho: %s\nFrequencia: %d\n\n", i, ht->tabela[i]->caminho, ht->tabela[i]->frequencia);
        }
    }
}

//-------------------------------FIM TESTES----------------------------------//



//Realiza todo o procedimento para compactar.
void compactar()
{
    char nome_do_arquivo[100], caminho[ALTURA_MAX];
    int i, contador=0, inteiro, auxiliar;
    unsigned short lixo, cabecalho, tamanho=0;

    printf("\nDigite o nome do arquivo a ser compactado:\n");
    scanf("%s", nome_do_arquivo);

    FILE *arquivo = fopen(nome_do_arquivo, "rb");

    if(arquivo == NULL){
        printf("Erro no arquivo.\nERRO 017\n");
        return;
    }
    printf("Iniciando processo de compactação...\n##############[0%%]\n\n");

    HT *ht = criar_hash_table();
    adicionar_cada_frequencia(arquivo, ht);
    rewind(arquivo);
    printf("\nProcesso em andamento...\n##############[21,9%%]\n\n");
    
    FILA *fila = criar_fila_vazia();
    fila = criar_fila_prioridade(ht, fila); //Fila aponta para a raiz da arvore.

    criar_arvore_huffman(fila);
    NO *arvore = fila->cabeca;

    criar_caminho_na_hash(arvore, ht, caminho, contador);
    printf("\nProcesso em andamento...\n##############[47,3%%]\n\n");

    lixo = calcula_tam_lixo(ht);
    inteiro = lixo;
    calcula_tam_arvore(arvore, &tamanho);

    inteiro = inteiro << 13;
    inteiro = setar_bits(inteiro, &tamanho);
    printf("\nProcesso em andamento...\n##############[75,2%%]\n\n");

    *nome_do_arquivo = *strtok(nome_do_arquivo, ".");
    *nome_do_arquivo = *strcat(nome_do_arquivo, ".huff");
    FILE *saida = fopen(nome_do_arquivo, "wb");
    printf("\nProcesso em andamento...\n##############[90%%]\n\n");

    auxiliar = inteiro>>8;
    fputc(auxiliar, saida);
    fputc(inteiro, saida);
    imprimir_pre_ordem(saida, arvore);
    fseek(saida, (2 + tamanho), SEEK_SET);
    imprimir_bits_dados(arquivo, saida, ht); // esta printando todos os bits dentro do arquivo.
    printf("\nProcesso concluido com sucesso!...\n\n\n\n");
}