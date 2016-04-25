#include <stdio.h>
#define TAM 21

struct chave{
    int codigo;
    char nome[TAM];
    int inicio;
    int antChave;
    int proxChave;
};
typedef struct chave CHAVE;

#include "arquivo.h"
//#include "ponteiro.h"

int main(){
    CHAVE *init;
    int valor,opc=10;
    init = (CHAVE*)malloc(sizeof(CHAVE));
    init->antChave=NULL;

    while (opc!=0){
        printf("\n1- inicia arquivo vazio\n2- grava novo valor\n3-lista ponteiro\n");
        printf("\nDigite a opcao: ");
        scanf ("%i",&opc);
        switch(opc){
            case 1:
                inicializar();
                break;
            case 2:
                printf("Digite o novo valor a ser gravado: ");
                scanf("%i",&valor);
                gravando(valor,init);
                break;
            case 3:
                carregaIndex(init);
                listarPonteiro(init);
                break;
        }
    }
}

