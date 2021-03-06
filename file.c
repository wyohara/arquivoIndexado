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
#include <stdlib.h>
#include <locale.h>

#define TAM 21

struct chave{
    int codigo;
    int initCodigo;
    char nome[TAM];
    int inicio;
    int antChave;
    int proxChave;
};
typedef struct chave CHAVE;

#include "arquivo.h"
//#include "ponteiro.h"

int main(){
    //setando idioma para portugu�s
    setlocale(LC_ALL,"Portuguese");

    int valor,opc=10;

    //Criando o ponteiro do index
    CHAVE *init;
    init = (CHAVE*)malloc(sizeof(CHAVE));
    init->antChave=NULL;
    init->proxChave=NULL;

    //switch para escolher a op��o
    while (opc!=0){
        printf("\n1 - Inicia arquivo vazio\n2 - Grava novo valor\n3 - Lista ponteiro\n4 - Retorna Valor\n5 - Marca para dele��o\n6 - Compacta��o");
        printf("\nDigite a op��o: ");
        scanf ("%i",&opc);
        switch(opc){
            //gera arquivo vazio
            case 1:
                system("cls");
                inicializar();
                break;

            //adiciona novo elemento
            case 2:
                system("cls");
                printf("\nDigite o novo valor a ser gravado: ");
                scanf("%i",&valor);
                gravando(valor,init);
                break;

            //lista index
            case 3:
                system("cls");
                carregaIndex(init);
                listarPonteiro(init);
                break;

            //exibe valor
            case 4:
                system("cls");
                retornaValor(init);
                break;
            case 5:
                system("cls");
                deletar(init);
                break;
            case 6:
                system("cls");
                compactar(init);
                break;
        }
    }
}

