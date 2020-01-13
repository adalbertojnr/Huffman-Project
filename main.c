#include "suporte.h"
#include "compactar.h"
#include "descompactar.h"

int main()
{
    int escolha, i;
    while(1){
        printf("Escolha o procedimento a ser realizado\n(1 para Compactar, 2 para Descompactar e 3 para Finalizar):\n");
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