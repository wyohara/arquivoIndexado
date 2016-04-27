/*
    *** Willian Yudi Ohara
    *** file.c
*/

/*
    Para um melhor entendimento deste codigo, considera:
    Cabe�alho- primeira parte do arquivo indexado, onde se localiza o inicio do index
    Dados todo o espa�o que a informa��o � gravada, isto � entre o cabe�alho e o index
    index - conjunto de nome e posi��o de inicio da informa��o que foi gravada no arquivo indexado
*/

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
    int valor,opc=10;

    //Criando o ponteiro do index
    CHAVE *init;
    init = (CHAVE*)malloc(sizeof(CHAVE));
    init->antChave=NULL;

    //switch para escolher a op��o
    while (opc!=0){
        printf("\n1- inicia arquivo vazio\n2- grava novo valor\n3-lista ponteiro\n");
        printf("\nDigite a opcao: ");
        scanf ("%i",&opc);
        switch(opc){
            //gera arquivo vazio
            case 1:
                inicializar();
                break;

            //adiciona novo elemento
            case 2:
                printf("\nDigite o novo valor a ser gravado: ");
                scanf("%i",&valor);
                gravando(valor,init);
                break;

            //lista index
            case 3:
                carregaIndex(init);
                listarPonteiro(init);
                break;
        }
    }
}

