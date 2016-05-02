/*
    *** Willian Yudi Ohara
    *** arquivo.h
*/

#include "ponteiro.h"
/*
    *** Arquivo da biblioteca que contém as funções para manipular o arquivo de texto
    ** arq é o ponteiro do tipo FILE que guarda todos o arquivo que esta sendo usado
    * São salvos no index apenas o valor do dado, o nome e seu inicio, os demais dados dos ponteiros são obtidos por comparação
*/


/*
    *** A função void inicializar cria um arquivo index vazio
    **inicChave é o valor inicial para comparar se o arquivo e vazio ou não
*/
void inicializar(){
    int sel;

    printf("\nDeseja apagar o arquivo e criar um novo (1 = sim/0 = não)? ");

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
    *** A função gravando grava os arquivos no arquivo index e também salva um ponteiro com o index

    * PARAMETRO val é o valor de entrada que será gravado no arquivo index
    * int pos é a variavel que guarda a POSICAO DO INDEX do arquivo indexado
    * char nome [TAM] é a variavel que lê o nome do arquivo e salva no arquivo index
    * int comeco indica onde começou o NOVO DADO, ele posteriormente e salvo no indice

*/
void gravando (int val, CHAVE *raiz){
    CHAVE *aux;
    int pos,comeco,newCodigo = 1;
    char nome[TAM];
    printf("\nGravando o valor %i",val);

    FILE *arq;
    arq = fopen("arquivo.bin","r+b");

    //posicionando o inicio do arquivo
    fseek(arq,0, SEEK_SET);
    fread(&pos,sizeof(int),1,arq);

    //salvando index no ponteiro
    carregaIndex(raiz);

    //caso o valor da posição pos for 0, ela sera mudada para o espaço seguinte após o cabeçalho
    if (pos==0){pos=4;}

    //posiciona o cursor na posição do novo valor, no caso pos
    fseek(arq,pos,SEEK_SET);

    //gravando novo valor no arquivo
    //OBS quando for inserir a gravação de arquivo externo mexer somente nesta variavel
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

    //executa a gravação do index antigo
    while(aux != NULL){
        fwrite(&aux->nome,sizeof(char),TAM,arq);
        fwrite(&aux->codigo,sizeof(int),1,arq);
        fwrite(&aux->inicio,sizeof(int),1,arq);

        if(aux->codigo>=newCodigo){
            newCodigo = aux->codigo + 1;
        }
        aux=aux->proxChave;
    }

    //grava o index do novo valor
    printf("\nDigite o nome do novo elemento: ");
    scanf("%20s",nome);
    fwrite(&nome,sizeof(char),TAM,arq);
    fwrite (&newCodigo,sizeof(int),1,arq);
    fwrite(&pos,sizeof(int),1,arq);

    fclose(arq);

}

/*
    *** função para retornar o valor salvo com base na lista encadeada.
    *** opção 4 do main
*/

void retornaValor(CHAVE *raiz){
    FILE *arq = fopen("arquivo.bin","rb");
    CHAVE *aux = raiz;
    int codigo = 0,valor;

    //retorna informação
    carregaIndex(raiz);
    listarPonteiro(raiz);
    while(codigo == 0){
        printf("\n.....................................\nDigite o codigo do valor a ser lido: ");

        //captura o codigo do valor buscado
        scanf("%i",&codigo);
        if(codigo!=0){
            printf("\nBuscando: %i\n\n",codigo);
        }else{
            printf("\nNão é possivel buscar o valor 0, ele é marcado para deleção.\n\n");
        }
    }

    while(aux != NULL){
        if(aux->codigo == codigo){
            //caso o codigo buscado seja achado, o valor é salvo na variavel valor
            fseek(arq,aux->inicio,SEEK_SET);
            fread (&valor,sizeof(int),1,arq);
            printf("O valor é: %d\n\n",valor);
        return;
        }
        //anda na chave
        aux=aux->proxChave;
    }
    //caso o loop encerre significa que nao foi achado o valor
    printf("\nValor não achado.\n\n");
}

/*
    ***função para marcar deleção no arquivo indexado com base na lista encadeada
    ***Para saber se um arquivo foi marcado para deleção e só ver o CODIGO. Se for 0 entao é marcado para deleção
    * PARAMETRO raiz é o inicio da lista indexada
*/

void deletar(CHAVE *raiz){
    CHAVE *aux=raiz->proxChave;
    FILE *arq = fopen("arquivo.bin","r+b");
    int codigo,comeco;

    //Gerando a exibição
    carregaIndex(raiz);
    listarPonteiro(raiz);

    //capturando o codigo a ser deletado
    printf("\nDigite o codigo a ser deletado: ");
    scanf("%d",&codigo);

    while(aux != NULL){
        //busca-se o codigo que bate com o valor buscado
        if(aux->codigo == codigo){
            //é atribuido valor 0 e é regravado
            aux->codigo=0;
            fseek(arq,aux->initCodigo,SEEK_SET);
            fwrite(&aux->codigo,sizeof(int),1,arq);
            //fecha o arquivo para salvar as mudanças
            fclose(arq);
            return;
        }
        aux=aux->proxChave;
    }
    //caso aux==null o valor nao foi achado
    printf("\nCodigo não achado");

    //encerrando
    fclose(arq);

}

/*
    *** Função para compactar os dados marcados para a deleção. Usa como base o Index salvo no ponteiro Raiz
*/
void compactar(CHAVE *raiz){
    FILE *ler = fopen("arquivo.bin","rb");
    //Cria um novo file chamado arq.bin e depois o fecha
    FILE *escr = fopen("arq.bin","w");
    fclose(escr);

    //reabre o file arq.bin em modo leitura e escrita
    escr = fopen("arq.bin","r+b");
    CHAVE *aux = raiz->proxChave,*mov;
    int val=10;

    //Gera o index de chaves
    carregaIndex(raiz);

    //escreve um valor simbolico em arq.bin, futuramente esse valor será o cabeçalho;
    fwrite(&val, sizeof(int),1,escr);

    printf("\nEscrevendo valor e lendo Index");

    //Loop que recria o arquivo de dados. Ele:
        ///* Salva em arq.bin os dados que não foram marcados para a deleção
        ///* Altera o aux->inicio para o valor da nova posição em arq.bin
        ///* remove os elementos do index que foram deletados (codigo = 0)

    while(aux!=NULL){
        //caso o elemento nao seja marcado para deleção
        if(aux->codigo != 0){
            //posiciona ao final do arquivo arq.bin
            fseek(escr,0,SEEK_END);
            //Altera o valor de aux->inicio
            fseek(ler,aux->inicio,SEEK_SET);
            aux->inicio = ftell(escr);
            //reescreve o valor em arq.bin
            fread(&val,sizeof(int),1,ler);
            printf("\nVAL: %d",val);
            fwrite(&val,sizeof(int),1,escr);
            //caminha com a chave
            aux=aux->proxChave;
        //caso seja marcado para a deleção remove o index e nao escreve o valor
        }else{
            //a chave do elemento anterior (mov) aponta para o prox elemento de aux(aux->proxChave)
            mov = aux->antChave;
            mov->proxChave=aux->proxChave;
            //remove o elemento que aux aponta
            free(aux);
            //atribui novo valor para aux
            aux=mov->proxChave;
        }
    }

    aux=raiz->proxChave;

    //posiciona o ponteiro no final de arq.bin e salva em val, depois posiciona no inicio de arq.bin para escrever  o cabeçalho
    fseek(escr,0,SEEK_END);
    val=ftell(escr);
    fseek(escr,0,SEEK_SET);
    fwrite(&val,sizeof(int),1,escr);

    printf("\nEscrevendo Index");

    //reescreve o index normalmente
    while(aux!=NULL){
        fseek(escr,0,SEEK_END);
        fwrite(&aux->nome,sizeof(char),TAM,escr);
        fwrite(&aux->codigo,sizeof(int),1,escr);
        fwrite(&aux->inicio,sizeof(int),1,escr);
        aux=aux->proxChave;
    }
    //usa a função para apagar os ponteiros
    liberaMemoria(raiz);
    //fecha arquivos
    fclose(ler);
    fclose(escr);
    //remove o arquivo antigo
    remove("arquivo.bin");
    //nomeia arq.bin com o nome do arquivo antigo
    rename ("arq.bin", "arquivo.bin");
    printf("\nCompactado.\n\n");

    return;
}
