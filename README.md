# arquivoIndexado

Pequeno treino da aula de Algoritmos e Estrutura de dados II, onde eu criei um arquivo binário simples que contém valores de inteiros e seu nome, além de sua respectiva chave de localização. Apesar de ser muito simples eu pretendo inserir uma função para carregar arquivos e escrevê-los no arquivo indexado, armazendo de forma segura os dados.

###Ele é composto de 3 arquivos:

####Arquivo "file.c":
Contém o metodo main e permite o controle das funcionalidades do programa, suas principais características são:
 - por meio de um "switch case" resetar o arquivo, listar ou inserir dados;
 - inicializa o ponteiro "inic" que é a base onde se lista todos os ponteiros.


####Arquivo "ponteiro.h":
Contém as principais ferramentas de manipulação de ponteiros e sua manipulação. É dividido em funções:
- __carregaIndex( ):__ função para ler o arquivo indexado e salvar as chaves em uma lista encadeada;
- __listarPonteiro( ):__ pequena função que percorre com um while mostrando os dados dos ponteiros.


####Arquivo "arquivo.h":
São as funções reposáveis pela manipulação do arquivo indexado, é aqui que se insere e deleta os valores. É dividido em funções:
- __inicializar( ):__ apaga qualquer outro arquivo indexado e cria um novo arquivo vazio (no caso com valor -1, que sinaliza que não há valor);
- __gravando( ):__ função para gravar um novo valor e sua respectiva chave;
- __reescreveIndex( ):__ função que é usada dentro de gravando() como subrotina, ele serve para reescrever as chaves do index dentro do arquivo indexado, incorporando os novos valores. Ela foi criada separadamente para evitar erros de reescrita do arquivo, caso haja alguma mudança de valores.


##Aguardo retorno caso haja duvidas ou opinioes.
