/*
    *** Willian Yudi Ohara
    *** ponteiro.h
*/

/*
    *** carregaIndex é a função que carrega o index do arquivo indexado na forma de ponteiros
    * PARAMETRO raiz é o inicio da lista encadeada do index
    * CHAVE *aux é o ponteiro da struct CHAVE que armazena structs temporariamente
    * CHAVE *novo é o ponteiro da struct CHAVE que contém todos os dados de cada arquivo salvo.
    * *arq é o FILE que contém o arquivo indexado
    * int comeco é a variavel que salva a posição dentro do arquivo indexado
    * int cont é o contador que indica qual é o numero da chave.
    * int fim é a variavel que guarda o final do arquivo, serve para comparar e verificar se o arquivo chegou ao fim
*/

int carregaIndex(CHAVE *raiz){

    raiz->proxChave=NULL;
    CHAVE *aux;
    CHAVE *novo;

    int comeco,cont=0,fim;

    FILE *arq;
    arq=fopen("arquivo.bin","rb");

    //antes de relistar o index apaga-se toda a lista encadeada, se houver
    liberaMemoria(raiz);

    //Descobrindo o final do arquivo
    fseek(arq,0,SEEK_END);
    fim = ftell(arq);
    //printf("\n\nPosição do final do arquivo: %d", fim);

    //posicionando o inicio;
    fseek(arq,0,SEEK_SET);
    //lendo o indice inicial
    fread(&comeco, sizeof(int), 1,arq);

    //verifica se há um valor no cabeçalho, no caso comeco
    if(comeco == 0){
        printf("\nArquivo vazio, não há indice.");
        return;
    }else{
        //printf("\ninicio do index na posição: %d\n", comeco);

        aux = raiz;

        //caso haja valor aux aponta para a raiz e inicia o encadeamento
        while (comeco<fim){
            novo =(CHAVE*)malloc(sizeof(CHAVE));

            aux->proxChave = novo;
            novo->antChave = aux;
            fseek(arq,comeco,SEEK_SET);

            novo->codigo = cont;
            fread(&novo->nome,sizeof(char),TAM,arq);

            fread(&novo->inicio,sizeof(int),1,arq);

            novo->proxChave=NULL;

            comeco= ftell(arq);

            aux=aux->proxChave;
            novo=novo->proxChave;
            cont++;
        }
    }
    fclose (arq);
}


/*
    *** listarPonteiro Lista todas as chaves que estao salvas no index
    * aux é o ponteiro que se movimenta ao longo da struct
*/
void listarPonteiro(CHAVE *raiz){
    CHAVE *aux;
    aux=raiz->proxChave;

    while (aux!=NULL){

        printf("\nCodigo: %d", aux->codigo);
        printf("\nNome: %s", aux->nome);
        printf("\ninicio: %d", aux->inicio);
        printf("\n\n...\n");
        aux=aux->proxChave;
    }
    liberaMemoria(raiz);
}


/*
    *** liberaMemoria é a função que apaga os valores da lista encadeada
    * PARAMETRO raiz - é o ponteiro que aponta para o inicio da lista encadeada

*/

void liberaMemoria(CHAVE *raiz){
    CHAVE *aux=raiz->proxChave, *deleta;
    if (aux== NULL){
        return;
    }else{
        while (aux->proxChave!=NULL){
            deleta=aux;
            aux=aux->proxChave;
            free(deleta);
            //atribui deleta como NULL para nao deixar ponteiro vazio, isto gera brecha de segurança
            deleta=NULL;
        }
    }
}
