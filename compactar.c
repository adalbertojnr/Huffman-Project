#include "compactar.h"

//Realiza todo o procedimento para compactar.
void compactar()
{
    char nome_do_arquivo[100], caminho[ALTURA_MAX];
    int i, contador=0, *tamanho = 0;
    unsigned char lixo, cabecalho;

    printf("Digite o nome do arquivo a ser compactado:\n");
    scanf("%s", nome_do_arquivo);
    fflush(stdin); //TALVEZ DÊ ERRO

    FILE *arquivo = fopen(nome_do_arquivo, "rb");

    if(arquivo == NULL){
        printf("Erro no arquivo.\nERRO 017\n");
        return;
    }
    printf("Iniciando processo de compactação...\n##############[0%]\n##############[13,7%]\n");

    HT *ht = criar_hash_table();
    adicionar_cada_frequencia(arquivo, ht);
    rewind(arquivo);
    printf("\nProcesso em andamento...\n##############[21,9%]\n");
    
    FILA *fila = criar_fila_vazia();
    fila = criar_fila_prioridade(ht, fila); //Fila aponta para a raiz da arvore.
    NO *arvore = criar_arvore_huffman(fila);
    criar_caminho_na_hash(arvore, ht, caminho, contador);
    printf("\nProcesso em andamento...\n##############[67,31%]\n");

    lixo = calcula_tam_lixo(ht);
    calcula_tam_arvore(arvore, &tamanho);
    lixo = lixo << 13;
    cabecalho = setar_bits(lixo, tamanho);
    *nome_do_arquivo = strtok(nome_do_arquivo, ".");
    *nome_do_arquivo = strcat(nome_do_arquivo, ".huff");
    FILE *saida = fopen(nome_do_arquivo, "wb");
    unsigned char aux = cabecalho;
    fprintf(saida, "%c%c", cabecalho>>8, aux);
    imprimir_pre_ordem(saida, arvore);
    
}