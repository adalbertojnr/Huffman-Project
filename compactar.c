#include "compactar.h"

void print_pre_order(NO *tree)
{
	if(tree != NULL){
    	printf("%c", (unsigned char*)(tree->item) );
        print_pre_order(tree->esq);
    	print_pre_order(tree->dir);
	}
}

//Realiza todo o procedimento para compactar.
void compactar()
{
    char nome_do_arquivo[100], caminho[ALTURA_MAX];
    int i, contador=0, inteiro;
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

    NO *arvore = criar_arvore_huffman(fila); // APARENTEMENTE A ARVORE ESTA SAINDO ERRADA.
    printf("AQUI ESTA A ARVORE:");
    print_pre_order(arvore); // ERRO ESTA AQUI
    criar_caminho_na_hash(arvore, ht, caminho, &contador);
    printf("\nProcesso em andamento...\n##############[47,3%%]\n\n");

    inteiro = calcula_tam_lixo(ht);
    printf("TESTAR O NEGOCIO%d\n", inteiro);
    lixo = inteiro;
    calcula_tam_arvore(arvore, &tamanho);
    lixo <<= 13;
    lixo += tamanho;
    printf("\nProcesso em andamento...\n##############[75,2%%]\n\n");

    *nome_do_arquivo = *strtok(nome_do_arquivo, ".");
    *nome_do_arquivo = *strcat(nome_do_arquivo, ".huff");
    FILE *saida = fopen(nome_do_arquivo, "wb");
<<<<<<< HEAD
    printf("\nProcesso em andamento...\n##############[90%%]\n\n");

    fputc(cabecalho , saida);
    imprimir_pre_ordem(saida, arvore); //ERRO AQUI
    imprimir_bits_dados(arquivo, saida, ht);
    printf("\nProcesso concluido com sucesso!...\n\n");
}
=======
    unsigned char aux = cabecalho;
    fprintf(saida, "%c%c", cabecalho>>8, aux);
    imprimir_pre_ordem(saida, arvore);
    Teste
}
>>>>>>> b03287bc540cd8e70ba2cc78294fd9bdf46ca90f
