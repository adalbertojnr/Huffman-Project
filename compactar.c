#include "compactar.h"
#include <stdio.h>
#include <stdlib.h>

//Realiza todo o procedimento para compactar.
void compactar()
{
    char nome_do_arquivo[100];
    int i, j;

    printf("Digite o nome do arquivo a ser compactado:\n");
    scanf("%s", nome_do_arquivo);
    fflush(stdin); //TALVEZ DÊ ERRO

    FILE *arquivo = fopen(nome_do_arquivo, "rb");

    if(arquivo == NULL){
        printf("Erro no arquivo.\nERRO 001\n");
        return;
    }
    printf("Iniciando processo de compactação...\n##############[0%]\n##############[13,7%]\n");
    
}