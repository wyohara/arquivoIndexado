
/*
    *** carregaIndex � a fun��o que carrega o index do arquivo indexado na forma de ponteiros
    * aux � o ponteiro da struct CHAVE que armazena structs temporariamente
    * novo � o ponteiro da struct CHAVE que cont�m todos os dados de cada arquivo salvo.
    * arq � o FILE que cont�m o arquivo indexado
    * pos � a variavel que salva a posi��o dentro do arquivo indexado
    * cont � o contador que indica qual � o numero da chave.
    * fim � a variavel que guarda o final do arquivo, serve para comparar e verificar se o arquivo chegou ao fim
*/

int carregaIndex(CHAVE *raiz){
    raiz->proxChave=NULL;
    CHAVE *aux;
    CHAVE *novo;

    int pos,cont=0,fim;

    FILE *arq;
    arq=fopen("arquivo.bin","rb");

    //Descobrindo o final do arquivo
    fseek(arq,0,SEEK_END);
    fim = ftell(arq);
    printf("\nFinal: %d", fim);

    //posicionando o inicio;
    fseek(arq,0,SEEK_SET);
    //lendo o indice inicial
    fread(&pos, sizeof(int), 1,arq);

    if(pos == -1){
        printf("\nArquivo vazio, nao h� indice.");
        return;
    }else{
        printf("\ninicio do index na posicao: %d", pos);

        aux = raiz;

        while (pos<fim){
            novo =(CHAVE*)malloc(sizeof(CHAVE));

            aux->proxChave = novo;
            novo->antChave = aux;
            fseek(arq,pos,SEEK_SET);

            novo->codigo = cont;
            fread(&novo->nome,sizeof(char),TAM,arq);

            fread(&novo->inicio,sizeof(int),1,arq);

            novo->proxChave=NULL;

            pos= ftell(arq);

            aux=aux->proxChave;
            novo=novo->proxChave;
            cont++;
        }
    }
}


/*
    *** listarPonteiro Lista todas as chaves que estao salvas no index
    * aux � o ponteiro que se movimenta ao longo da struct
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
}
