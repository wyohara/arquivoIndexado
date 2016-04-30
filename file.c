/*
    *** Willian Yudi Ohara
    *** file.c
*/

/*
    Para um melhor entendimento deste codigo, considera:
    Cabeçalho- primeira parte do arquivo indexado, onde se localiza o inicio do index
    Dados todo o espaço que a informação é gravada, isto é entre o cabeçalho e o index
    index - conjunto de nome e posição de inicio da informação que foi gravada no arquivo indexado
*/

#include <stdio.h>
#include <locale.h>

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
    //setando idioma para português
    setlocale(LC_ALL,"Portuguese");

    int valor,opc=10;

    //Criando o ponteiro do index
    CHAVE *init;
    init = (CHAVE*)malloc(sizeof(CHAVE));
    init->antChave=NULL;

    //switch para escolher a opção
    while (opc!=0){
        printf("\n1- inicia arquivo vazio\n2- grava novo valor\n3-lista ponteiro\n");
        printf("\nDigite a opção: ");
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
        }
    }
}

