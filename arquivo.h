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

    printf("\nInicializando um arquivo vazio\n\n");
    FILE *arq;
    arq = fopen("arquivo.bin","wb");
    int inicChave = -1;

    fwrite(&inicChave,sizeof(int),1,arq);
    fclose(arq);
}

/*
    *** A fun��o gravando grava os arquivos no arquivo index e tamb�m salva um ponteiro com o index

    * O PARAMETRO val � o valor de entrada que ser� gravado no arquivo index
    * int pos � a variavel que guarda a POSICAO DO INDEX do arquivo indexado
    * char nome [TAM] � a variavel que l� o nome do arquivo e salva no arquivo index
    * int comeco indica onde come�ou o NOVO DADO, ele posteriormente e salvo no indice

*/

void gravando (int val, CHAVE *raiz){
    int pos,comeco;
    char nome[TAM];
    printf("\nGravando o valor %i",val);

    FILE *arq;
    arq = fopen("arquivo.bin","r+b");

    //posicionando o inicio do arquivo
    fseek(arq,0, SEEK_SET);
    fread(&pos,sizeof(int),1,arq);
    printf("\nvalor incial: %d",pos);

    if(pos == -1){
        //posicionando o cursor no final do arquivo para gravar o valor
        fseek(arq,0,SEEK_END);

        //salvando o inicio do dado e escrevendo o valor
        comeco = ftell(arq);
        fwrite(&val,sizeof(int),1,arq);

        //pos agora receber� a posi��o do final da grava��o do arquivo e inicio do index
        pos = ftell(arq);
        fseek(arq,0,SEEK_SET);
        fwrite(&pos,sizeof(int),1,arq);

        printf("\nDigite o nome: ");
        scanf("%20s", nome);

        //GRAVANDO O INDEX
        //gravando o nome do arquivo
        fseek(arq,pos,SEEK_SET);
        fwrite(&nome,sizeof(char),TAM,arq);

        //realizando a releitura do nome para garantir a integridade
        fseek(arq,pos,SEEK_SET);
        fread(&nome,sizeof(char),TAM,arq);
        printf("\nA string salva e %s",nome);

        //gravando o endere�o de inicio
        fseek(arq,0,SEEK_END);
        printf("\ncomeco: %d",comeco);
        fwrite(&comeco,sizeof(int),1,arq);

        fclose(arq);

    }else{
        //salvando index no ponteiro
        carregaIndex(raiz);

        //gravando novo valor no arquivo
        fseek(arq,pos,SEEK_SET);
        fwrite(&val,sizeof(int),1,arq);
        comeco=ftell(arq);

        //gravando o inicio do indice
        //OBS pos=inicio do novo valor e comeco=inicio do index
        fseek(arq,0,SEEK_SET);
        fwrite(&comeco,sizeof(int),1,arq);

        reescreveIndex(raiz, arq, comeco,pos);


        fclose(arq);
    }
}

int reescreveIndex(CHAVE *raiz, FILE *arq,int comeco,int pos){
    CHAVE *aux;
    char nome[TAM];
    aux=raiz->proxChave;
    fseek(arq,comeco,SEEK_SET);
    while(aux != NULL){
        fwrite(&aux->nome,sizeof(char),TAM,arq);
        fwrite(&aux->inicio,sizeof(int),1,arq);
        aux=aux->proxChave;
    }
        printf("\nDigite o nome: ");
        scanf("%20s",nome);
        fwrite(&nome,sizeof(char),TAM,arq);
        fwrite(&pos,sizeof(int),1,arq);
}
