#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "suporte.h"
#include "compactar.h"
#include "descompactar.h"
#include "suporte.c"
#include "compactar.c"
#include "descompactar.c"
#include "interface.h"

int main()
{
    interface();
    welcome();
    int escolha, i;
    while(1){
        printf("Escolha o procedimento a ser realizado:\n1 - Compactar\n2 - Descompactar\n3 - Sair do programa\n");
        scanf("%d", &escolha);
        if(escolha == 1){
            compactar();
        }else if(escolha == 2){
            descompactar();
        }else if(escolha == 3){
            return 0;
        }
    }
}