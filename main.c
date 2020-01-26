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

int main()
{
    int escolha, i;
    while(1){
        printf("Escolha o procedimento a ser realizado\n(1 para Compactar, 2 para Descompactar e 3 para Sair do programa):\n");
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