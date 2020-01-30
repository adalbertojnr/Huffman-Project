#include "descompactar.h"

//Realiza todo o procedimento para descompactar.
void descompactar()
{
    char nome_do_arquivo[100], caminho[ALTURA_MAX], extensao[3];
    int i, contador=0, inteiro, auxiliar;
    unsigned short lixo, cabecalho, tamanho=0;

    printf("\nDigite o nome do arquivo a ser compactado:\n");
    scanf("%s", nome_do_arquivo);

    FILE *arquivo = fopen(nome_do_arquivo, "rb");

    if(arquivo == NULL){
        printf("Erro no arquivo.\nERRO 017\n");
        return;
    }

    FILE *saida = fopen(arquivo, "rb");
}