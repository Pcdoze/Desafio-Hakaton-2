#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 4 // N?mero de Pe?as por Pino | Tamanho do Pino
#define NUM 3  // N?mero de Pinos
#define REGRA_TAMANHO 1 // Pinos de tamanho maior n?o podem ficar em cima de pinos menores se REGRA_TAMANHO == 1

/* Tipos */
typedef struct {
 int Top;
 int * Lista;
} Pinos;

typedef Pinos * Pino;
/* Tipos */

/* M?todos */
int Push();
int Pop();
int show();
int showLista();

int gerarMesa();
int mostrarMesa();

Pino gerarPino();
int gerarPinos();
int moverPeca();
int checarPecas();
int checarPinos();
int checarTamanho();

int jogo();
int getPinoUsuario();
/* M?todos */

/* Vari?veis */
Pino pino;
Pino * lista_pinos;
/* Vari?veis */

int main()
{
 lista_pinos = (Pino *) malloc(sizeof(Pino));
 gerarPinos(lista_pinos, NUM);

 mostrarMesa(lista_pinos);
 jogo();

 printf("\n\n");
 return 0;
}

int jogo(){
    int pino1 = getPinoUsuario(1);
    int pino2 = getPinoUsuario(2);

    moverPeca(lista_pinos, pino1, pino2);
    mostrarMesa(lista_pinos);

    if(checarPinos(lista_pinos)){
        return 1;
    }

    jogo();
}

int getPinoUsuario(int pino){
    printf("\nDigite o n?mero do Pino %d: ", pino);

    int entrada;
    int isnum = scanf("%d", &entrada);

    if(isnum <= 0 || isnum == EOF){
        fflush(stdin);

        printf("\nEntrada Inv?lida!");
        entrada = getPinoUsuario(pino)+1;
    }
    else if(entrada <= 0 || entrada > NUM){
        printf("Pino n?o Existe!\n");
        entrada = getPinoUsuario(pino)+1;
    }

    return entrada-1;
}

int Push(Pino p, int entrada)
{
    if(p != NULL){
        if ((p -> Top) == SIZE - 1)
        {
            return 0;
        }
        else
        {
            (p -> Top) = (p -> Top) + 1;
            (p->Lista)[(p->Top)] = entrada;
        }
        return 1;
    }
    return 0;
}

int Pop(Pino p)
{
 if ((p -> Top) == -1)
 {
  return 0;
 } else
 {
  (p -> Top) = (p -> Top) - 1;
 }

 return 1;
}

int show(Pino p)
{
 if ((p -> Top) == -1)
 {
  return 0;
 } else
 {

  for (int i = (p -> Top); i >= 0; --i)
   printf("%d\n", p -> Lista[i]);

 }

 return 1;
}

Pino gerarPino() {
 Pino p = (Pino) malloc(sizeof(Pinos));

 p -> Top = -1;
 p -> Lista = (int *) malloc(sizeof(int) * SIZE);

 return p;
}

int gerarPinos(Pino * lista, int numero_de_pinos) {
 lista = (Pino*) realloc(lista, sizeof(Pino) * numero_de_pinos);

 for (int i = 0; i < numero_de_pinos; i++) {

  if (i == 0) {
   lista[0] = gerarPino();

    for(int i = SIZE; i >= 1; i--){
       Push(lista[0], i);
    }

    } else {

        lista[i] = gerarPino();

    }

 }

 return 0;
}

int checarTamanho(int pino_acima, int pino_abaixo, int pino2_top){
    if(REGRA_TAMANHO){
        if(pino2_top > -1 && pino_acima > pino_abaixo){
            return 0;
        }
    }

    return 1;
}

int moverPeca(Pino * lista, int pin1, int pin2) {
 Pino pino1 = lista[pin1];
 Pino pino2 = lista[pin2];


 if(pino2->Top < SIZE-1 && pino1->Top >= 0){

    if(checarTamanho(pino1->Lista[pino1->Top],
                     pino2->Lista[pino2->Top],
                     pino2->Top))
    {
        Push(pino2, pino1->Lista[pino1->Top]);
        Pop(pino1);

        return 1;
    }
 }
 return 0;
}

int checarPecas(Pino pino, int peca){
    if(peca >= (pino->Top)){
        if(pino->Lista[peca] == 1 && peca == SIZE-1){
            return 1;
        }
    }
    else{
        if(pino->Lista[peca] > pino->Lista[peca+1]){
            return checarPecas(pino, peca+1);
        }
    }

    return 0;
}
int checarPinos(Pino * lista){
    if(NUM > 1){
        for(int i = 0; i < NUM; i++)
            checarPecas(lista[i], 0);
    }
}

int mostrarMesa(Pino* lista){
    printf("\n");

    for(int y = 0; y < SIZE; y++){
        printf("\n");

        int ypos = SIZE-1-y;

        for(int x = 0; x < NUM; x++){
            printf("\t");
            for(int i = SIZE; i >= 1; i--){
                if((lista[x]->Top)-ypos >= 0 && lista[x]->Lista[ypos] >= i){
                    printf(".");
                }
                else{
                    printf(" ");
                }
            }

            printf("|");

            for(int i = 1; i <= SIZE; i++){
                if(lista[x]->Top-ypos >= 0 && lista[x]->Lista[ypos] >= i){
                    printf(".");
                }
                else{
                    printf(" ");
                }
            }

        }
    }

    return 1;
}
