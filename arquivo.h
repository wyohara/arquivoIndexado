/*
    *** Willian Yudi Ohara
    *** arquivo.h
*/

#include "ponteiro.h"
/*
    *** Arquivo da biblioteca que cont�m as fun��es para manipular o arquivo de texto
    ** arq � o ponteiro do tipo FILE que guarda todos o arquivo que esta sendo usado
    * S�o salvos no index apenas o valor do dado, o nome e seu inicio, os demais dados dos ponteiros s�o obtidos por compara��o
*/


/*
    *** A fun��o void inicializar cria um arquivo index vazio
    **inicChave � o valor inicial para comparar se o arquivo e vazio ou n�o
*/
void inicializar(){
    int sel;

    printf("\nDeseja apagar o arquivo e criar um novo (1 = sim/0 = n�o)? ");

    scanf("%i",&sel);

    if (sel != 1){
        printf("\nArquivo nao apagado\n");
        return;
    }

    printf("\nInicializando um arquivo vazio\n\n");
    FILE *arq;
    arq = fopen("arquivo.bin","wb");

    int inicChave = 0;
    fwrite(&inicChave,sizeof(int),1,arq);
    fclose(arq);
}

/*
    *** A fun��o gravando grava os arquivos no arquivo index e tamb�m salva um ponteiro com o index

    * PARAMETRO val � o valor de entrada que ser� gravado no arquivo index
    * int pos � a variavel que guarda a POSICAO DO INDEX do arquivo indexado
    * char nome [TAM] � a variavel que l� o nome do arquivo e salva no arquivo index
    * int comeco indica onde come�ou o NOVO DADO, ele posteriormente e salvo no indice

*/
void gravando (int val, CHAVE *raiz){
    CHAVE *aux;
    int pos,comeco;
    char nome[TAM];
    printf("\nGravando o valor %i",val);

    FILE *arq;
    arq = fopen("arquivo.bin","r+b");

    //posicionando o inicio do arquivo
    fseek(arq,0, SEEK_SET);
    fread(&pos,sizeof(int),1,arq);

    //salvando index no ponteiro
    carregaIndex(raiz);

    //caso o valor da posi��o pos for 0, ela sera mudada para o espa�o seguinte ap�s o cabe�alho
    if (pos==0){pos=4;}

    //posiciona o cursor na posi��o do novo valor, no caso pos
    fseek(arq,pos,SEEK_SET);

    //gravando novo valor no arquivo
    //OBS quando for inserir a grava��o de arquivo externo mexer somente nesta variavel
    fwrite(&val,sizeof(int),1,arq);

    //captura o novo inicio do index
    comeco=ftell(arq);

    //gravando o inicio do indice
    //OBS pos=inicio do novo valor e comeco=inicio do index
    fseek(arq,0,SEEK_SET);
    fwrite(&comeco,sizeof(int),1,arq);

    //ponteiro aux ira apontar para a lista encadeada raiz que contem o index
    aux=raiz->proxChave;

    //posiciona no novo inicio do index
    fseek(arq,comeco,SEEK_SET);

    //executa a grava��o do index antigo
    while(aux != NULL){
        fwrite(&aux->nome,sizeof(char),TAM,arq);
        fwrite(&aux->inicio,sizeof(int),1,arq);
        aux=aux->proxChave;
    }

    //grava o index do novo valor
    printf("\nDigite o nome do novo elemento: ");
    scanf("%20s",nome);
    fwrite(&nome,sizeof(char),TAM,arq);
    fwrite(&pos,sizeof(int),1,arq);

    fclose(arq);

}

/*
    *** fun��o para retornar o valor salvo com base na lista encadeada.
*/

void retornaValor(CHAVE *raiz){
    FILE *arq = fopen("arquivo.bin","rb");
    CHAVE *aux = raiz;
    int codigo,valor;

    //retorna informa��o
    carregaIndex(raiz);
    listarPonteiro(raiz);

    printf("\n.....................................\nDigite o codigo do valor a ser lido: ");

    //captura o codigo do valor buscado
    scanf("%i",&codigo);
    printf("\nBuscando: %i\n\n",codigo);

    while(aux != NULL){
        if(aux->codigo == codigo){
            //caso o codigo buscado seja achado, o valor � salvo na variavel valor
            fseek(arq,aux->inicio,SEEK_SET);
            fread (&valor,sizeof(int),1,arq);
            printf("O valor �: %d\n\n",valor);
        return;
        }
        //anda na chave
        aux=aux->proxChave;
    }
    //caso o loop encerre significa que nao foi achado o valor
    printf("\nValor n�o achado.\n\n");
}
