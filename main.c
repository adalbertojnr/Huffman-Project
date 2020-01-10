#include <stdio.h>
#include "compactar.h"
#include "descompactar.h"

int main()
{
    int escolha, i;
    while(1){
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