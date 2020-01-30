#include "descompactar.h"

void descompactar() {
    char nomedoarquivo[50];
    FILE *compactado;
    printf("Entre com o nome do arquivo que deseja descompactar: ");
    scanf("%s", nomedoarquivo);
    compactado = fopen(nomedoarquivo, "rb");
    descompressao(compactado, nomedoarquivo);
}

int descompressao(FILE *compactado, char *nome)
{
	int tamanho_arquivo = 0;
	short tamanho_lixo, tamanho_arvore = 8191; // tamanho_arvore recebe 8191 pois é o maior valor possível de um byte
	char nome_saida[50];
    unsigned char primeirobyte, segundobyte;
    NODE *raiz = NULL;
    FILE *descompactado;
    getchar();
    printf("Digite o nome final do arquivo: ");
    scanf("%[^\n]s", nome_saida);
    compactado = fopen(nome, "rb");          // Lê o arquivo em binário
    descompactado = fopen(nome_saida, "wb"); // Escreve em binário no novo arquivo
    fseek(compactado, 0, SEEK_END);          // Vai até  o final do arquivo


    tamanho_arquivo = ftell(compactado); // tamanho_arquivo recebe o tamanho do arquivo em bytes
	rewind(compactado); // Retorna para o início do arquivo

    primeirobyte = fgetc(compactado); // f_byte recebe o primeiro byte do arquivo
    
    segundobyte = fgetc(compactado); // s_byte recebe o segundo byte do arquivo
	
    tamanho_lixo = primeirobyte >> 5; // tamanho_lixo recebe os 3 bits de tamanho do lixo
	

    tamanho_arvore = ((primeirobyte << 8) | segundobyte) & tamanho_arvore; // tamanho arvore vai receber o tamanho da arvore

    raiz = montar_arvore(compactado); // monta a arvore
	fseek(compactado, tamanho_arvore + 2, SEEK_SET); // Escreve depois da arvore no novo arquivo
	printar_byte(compactado, descompactado, raiz, tamanho_arvore, tamanho_lixo, (tamanho_arquivo-tamanho_arvore-2)); // Escreve tudo no arquivo
	fclose(compactado);
	fclose(descompactado);
    printf("\nArquivo descompactado com sucesso!\n");
	return 0;
}

NODE *montar_arvore(FILE *compactado) //Reconstruir a árvore de huffman do arquivo compactado
{
	unsigned char atual;
    NODE *novo_no;
    atual = fgetc(compactado);
    if (atual == '*')
    {
    	novo_no = criar_no_arvore(atual);
        novo_no->esquerda = montar_arvore(compactado);
        novo_no->direita = montar_arvore(compactado);
    }
    else if (atual == (char)BARRA)
    {
        atual = fgetc(compactado);
        novo_no = criar_no_arvore(atual);
    }
    else
    {
        novo_no = criar_no_arvore(atual);
    }
    return novo_no;
}

NODE *criar_no_arvore(unsigned char caractere)
{
	unsigned char *aux = (unsigned char *)malloc(sizeof(unsigned char));
    *aux = caractere;
	NODE *novo_no = (NODE *)malloc(sizeof(NODE));
    novo_no->frequencia = 0;
    novo_no->item = aux;
    novo_no->direita = NULL;
    novo_no->esquerda = NULL;
    novo_no->proximo = NULL;
    return novo_no;
}

void printar_byte(FILE* compactado, FILE* descompactado, NODE *raiz, short tamanho_arvore, short tamanho_lixo, int tamanho_arquivo) //Escreve o arquivo descompactado
{
    long int i, j, k;
	unsigned char c;
	NODE *atual = raiz;
	for (i = 0; i < tamanho_arquivo; ++i)
	{
		c = fgetc(compactado);
		if (i == tamanho_arquivo - 1) {
			k = 8 - tamanho_lixo;
        }
		else {
			k = 8;
        }
		for (j = 0; j < k; ++j)
		{
			if(bit_esta_setado(c, 7 - j)) {
				atual = atual->direita;
            }
			else {
				atual = atual->esquerda;
            }
			if (atual->esquerda == NULL && atual->direita == NULL)
            {
                fprintf(descompactado, "%c", *(unsigned char*)atual->item);
                atual = raiz;
            }
		}
	}
}