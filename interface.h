#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include <unistd.h>

void print_comp(NO *arvore);
void pontos_saida(int qnt);
void interface();
void carregar();
void welcome();
void final_comp();

void welcome()
{
  system("clear");
  printf("\n\n\a\a BEM");
  sleep(1);
  printf("\a\a-VINDO AO PROGRAMA!\n\n\n\n\n");
  sleep(1);
}
void pontos_saida(int qnt)
{
  printf(" ");
  while(qnt--)
  {
    printf("."); sleep(1); 
  }
  printf("\n");

}

void interface()
{
    system("clear");
    FILE *interface = fopen("interface.txt","r");
    unsigned char c;
    while(fread(&c, 1, 1,interface))
    {
        printf("%c",c);
        usleep(8000);
    }
    int j = 12;
    printf("\n\n\n\n\n\n\n\n");
    printf("\t\t  Pressione ENTER para continuar");
    getchar();
    fclose(interface);
    system("clear");
}

void carregar()
{
  int i, j;
   for (i = 0; i <= 10; i++)
   {                
      printf ("  %d%%\r", i * 10);
      fflush (stdout);                      
      for (j = 0; j < i * 5; j++)
      {
         if (!j) // Da espaco na barra pra nao enconstar na borda da tela
           printf (" ");
           
         printf ("%c", 219);
         usleep(4000);
      }                   
   } 
   printf (" 100%%");
   sleep (2);
}

void print_comp(NO *arvore)
{ 
  if(arvore != NULL)
  {
      printf("%c ", (char*)arvore->item);
      print_comp(arvore->esq);
      print_comp(arvore->dir);
  }
}
void final_comp()
{
  int comando;
  printf("ARQUIVO COMPRIMIDO COM SUCESSO\n\n Escolha sua proxima acao:\n\n");
	puts(" 1. Verificar arvore huffman do arquivo\n");
	puts(" 2. Abrir arquivo\n");
	puts(" 3. Voltar ao inicio\n");
	printf(" 4. Sair do programa\n ");
	scanf("%d", &comando);
	switch (comando)
	{
   		case 1 :
   		system("clear");
   		printf("Arvore do arquivo atual:\n\n");  
     	printf(" \n\n\n\n Pressione Enter para sair");
     	getchar();
     	printf("\n");
   		break;

      case 2:
      break;

   		case 3 :
   		puts(" Voltando a Raiz do programa...");
   		sleep(1);
   		break;

   		default :
     	puts(" \nComando invalido, voltando ao inicio do aplicativo\n ");
     	sleep(3);
      break;
    }
}