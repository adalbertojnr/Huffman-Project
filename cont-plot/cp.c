#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//----------------ABB-----------------//

typedef struct arvore_binaria ABB;

struct arvore_binaria{
    int item;
    ABB *esq;
    ABB *dir;
};

ABB *criar_no_abb(int item)
{
    ABB *no_abb = (ABB*)malloc(sizeof(ABB));
    
    no_abb->item = item;
    no_abb->esq = NULL;
    no_abb->dir = NULL;
    
    return no_abb;
}

ABB *add_no_abb(ABB *raiz_arvore, int item)
{
    if(raiz_arvore == NULL){
        raiz_arvore = criar_no_abb(item);
    }else if(item < raiz_arvore->item){
        raiz_arvore->esq = add_no_abb(raiz_arvore->esq, item);
    }else{
        raiz_arvore->dir = add_no_abb(raiz_arvore->dir, item);
    }
    
    return raiz_arvore;
}


//----------------AVL-----------------//

typedef struct arvore_avl AVL;

struct arvore_avl{
    int item;
    int altura;
    AVL *esq;
    AVL *dir;
};

int maior(int a, int b)
{
    return(a > b) ? a : b;
}

int altura_arvore(AVL *raiz)
{
    if(raiz == NULL){
        return -1;
    }
    return 1 + maior(altura_arvore(raiz->esq), altura_arvore(raiz->dir));
}

int equilibrio_arvore(AVL *raiz)
{
    if(raiz != NULL){
        return (altura_arvore(raiz->esq) - altura_arvore(raiz->dir));
    }
    return 0;
}

AVL *criar_no_avl(int item)
{
    AVL *no_avl = (AVL*)malloc(sizeof(AVL));
    
    no_avl->item = item;
    no_avl->esq = NULL;
    no_avl->dir = NULL;
    no_avl->altura = altura_arvore(no_avl);
    
    return no_avl;
}

AVL *rotacionar_para_esquerda(AVL *raiz)
{
    AVL *sub_arvore = NULL;
    
    if(raiz != NULL && raiz->dir != NULL){
        sub_arvore = raiz->dir;
        raiz->dir = sub_arvore->esq;
        sub_arvore->esq = raiz;
    }
    sub_arvore->altura = altura_arvore(sub_arvore);
    raiz->altura = altura_arvore(raiz);
    
    return sub_arvore;
}

AVL *rotacionar_para_direita(AVL *raiz)
{
    AVL *sub_arvore = NULL;
    
    if(raiz != NULL && raiz->esq != NULL){
        sub_arvore = raiz->esq;
        raiz->esq = sub_arvore->dir;
        sub_arvore->dir = raiz;
    }
    sub_arvore->altura = altura_arvore(sub_arvore);
    raiz->altura = altura_arvore(raiz);
    
    return sub_arvore;
}

AVL *add_no_avl(AVL *raiz, int item)
{
    if(raiz == NULL){
        return criar_no_avl(item);
    }else if(item < raiz->item){
        raiz->esq = add_no_avl(raiz->esq, item);
    }else{
        raiz->dir = add_no_avl(raiz->dir, item);
    }
    
    raiz->altura = altura_arvore(raiz);
    
    AVL *filho;
    
    if(equilibrio_arvore(raiz) == 2 || equilibrio_arvore(raiz) == -2){
        if(equilibrio_arvore(raiz) == 2){
            filho = raiz->esq;
            
            if(equilibrio_arvore(filho) == -1){
                raiz->esq = rotacionar_para_esquerda(filho);
            }
            
            raiz = rotacionar_para_direita(raiz);
        }else if(equilibrio_arvore(raiz) == -2){
            filho = raiz->dir;
            
            if(equilibrio_arvore(filho) == 1){
                raiz->dir = rotacionar_para_direita(filho);
            }
            
            raiz = rotacionar_para_esquerda(raiz);
        }
    }
    
    return raiz;
}


//---------------COMPARAÇÕES---------------//

int comparacoes(AVL *raiz, int item)
{
    if(item == raiz->item || raiz == NULL){
        return 1;
    }else if(item < raiz->item){
        return (1 + comparacoes(raiz->esq, item));
    }else{
        return (1 + comparacoes(raiz->dir, item));
    }
}

int main()
{
    ABB *arvore_binaria = NULL;
    AVL *arvore_avl = NULL;

    FILE *plotagem = fopen("plotagem.txt", "w");

    fprintf(plotagem, "%s\t%s\t%s\n", "Posicao", "ABB", "AVL");

    int i, x, indice, comp_abb = 0, comp_avl = 0;
    int tamanho_array, qnt_buscas;

    srand(time(NULL));
    printf("Digite o tamanho do array:\n");
    scanf("%d", &tamanho_array);
    printf("Digite quantas buscas serao feitas:\n");
    scanf("%d", &qnt_buscas);

    int *array = (int*)malloc(sizeof(int) * tamanho_array);
	int *array_visitados = (int*)calloc(tamanho_array, sizeof(int));

    for(i = 0; i < tamanho_array; i++){
        x = rand();
        array[i] = x;
        arvore_binaria = add_no_abb(arvore_binaria, x);
        arvore_avl = add_no_avl(arvore_avl, x);
    }

    for(i = 0; i < qnt_buscas; i++){
        indice = rand() % tamanho_array;

        if(!array_visitados[indice]){
            comp_abb = comparacoes(arvore_binaria, array[indice]);
            comp_avl = comparacoes(arvore_avl, array[indice]);
            array_visitados[indice] = 1;

            fprintf(plotagem, "%d\t%d\t%d\n", indice+1, comp_abb, comp_avl);
        }
    }

    free(array);
    free(array_visitados);

    return 0;
}