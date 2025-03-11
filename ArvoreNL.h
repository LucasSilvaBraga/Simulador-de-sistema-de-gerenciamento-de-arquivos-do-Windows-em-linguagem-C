#include <iostream>
#include <stdlib.h>
#include <stdio.h>
//Inclusao da biblioteca string.h para ler strings
#include <string.h>


typedef struct dir{
	char nome[100];
	int tam;
	struct dir *pFilho;
	struct dir *prox;
	
}Dir;



/*
Funcao para criar diretorio passando como argumento um ponteiro para o primeiro
Espaco de vetor de Dir->nome[100]
OBS: esse fgets esta lendo o caractere de backspace
*/
Dir* criaDiretorio(Dir* DiretorioAtual){
	
	Dir *d = (Dir*) malloc (sizeof(Dir));
	char Nome[100];
	
	printf("Digite o nome do novo diretorio:");
	fgets(Nome, sizeof(Nome), stdin);
	
	//Removendo o caractere de backspace que o fgets deixa
	size_t len = strlen(Nome);
    if (len > 0 && Nome[len - 1] == '\n') {
        Nome[len - 1] = '\0';
    }
	
	//Juntando ambos os nomes
	snprintf(d->nome, sizeof(d->nome), "%s/%s", DiretorioAtual->nome, Nome);

    
	//Apontando pFilho e prox para Nulo
	d->pFilho = NULL;
	d->prox = NULL;
	
	return d;
	
}

Dir* criaRaiz(){
	
	Dir *d = (Dir*) malloc (sizeof(Dir));
	strcpy(d->nome, "Raiz");
	d->pFilho = NULL;
	d->prox = NULL;
	
	
	return d;
}

void insereDiretorio(Dir* Pai, Dir* DiretorioCriado){
	
	DiretorioCriado->prox = Pai->pFilho;
	Pai->pFilho = DiretorioCriado;
	
}


Dir* diretorioAtual(Dir* Arvore, char* c, Dir* DiretorioAnterior){
	Dir* aux;
	

	if(strcmp(Arvore->nome, c) == 0)
		return Arvore;
		
	else{
		DiretorioAnterior = Arvore;
		for(aux = Arvore->pFilho; aux != NULL; aux = aux->prox){
			Dir* Resultado = diretorioAtual(aux, c, DiretorioAnterior);
			DiretorioAnterior = aux;
			if(Resultado != NULL)
				return Resultado;
		}
	}
	
	return NULL;
}

Dir* diretorioAtualFilhos(Dir* Arvore, char* c, Dir* DiretorioAtual){
	Dir* Aux;

	//Verifica apenas os filhos do diretorio atual, se achar o diretorio correspondente vai retorna-lo
	//Caso nao encontre o loop for ira se encerrar e vai retornar o mesmo diretorio em que estava inicialmente
	//Esta sendo utilizada a funcao strcmp, essa retorna 0 quando um argumento e igual ao outro
	//OBS: utilizei a strcmp na comparacao da maioria das strings(se nao todas) pois foi o jeito que achei de nao bugar
	
	for(Aux = DiretorioAtual->pFilho; Aux != NULL; Aux = Aux->prox){
		if(strcmp(Aux->nome, c) == 0)
			return Aux;	
		}
	printf("\nDiretorio nao encontrado!\n");
	return DiretorioAtual;
}

/*
Funcao para voltar um diretorio
*/

Dir* voltarDiretorio(Dir* Arvore, Dir* DiretorioAtual, Dir* DiretorioAnterior){
	Dir* aux;

	
	if(strcmp(DiretorioAtual->nome, "Raiz") == 0){
		printf("Voce ja esta na Raiz, nao existe diretorio anterior!");
		return DiretorioAtual;
	}
	else{
		if(strcmp(Arvore->nome, DiretorioAtual->nome) == 0)
			return DiretorioAnterior;
		
	else{
		//Procurando o diretorio requisitado porem passando o diretorio atual como anterior
		//Dessa maneira quando o diretorio requisitado for obtido tambem teremos o seu diretorio anterior
		for(aux = Arvore->pFilho; aux != NULL; aux = aux->prox){
			Dir* Resultado = voltarDiretorio(aux, DiretorioAtual, Arvore);
			if(Resultado != NULL)
				return Resultado;
		}
	}
	
	return NULL;
	}
	

}

/*
Funcao para imprimir os subdiretorios
*/

void imprimeFilhosDiretorios(Dir* DiretorioAtual){
	
	Dir* Aux;
	//Verifica se o diretorio esta vazio
	if(DiretorioAtual->pFilho == NULL){
	
		printf("========================================\nCONTEUDO DO DIRETORIO:\n");
		printf("Diretorio vazio!\n========================================");
	}
	else{
		printf("========================================\nCONTEUDO DO DIRETORIO:\n");
		//Passando pelos filhos do diretorio atual
		for (Aux = DiretorioAtual->pFilho; Aux !=NULL; Aux = Aux->prox){
			printf("%s\n", Aux->nome);
		}
	printf("========================================");	
	}

	
}

//Funcao para inserir diretorios

void insereDiretorioReferencia(Dir* Arvore, Dir* DiretorioAtual, Dir* DiretorioCriado){
	
	Dir* Aux;
	//Bloco para quando o referido diretorio for achado, assim que isso acontecer o diretorio criado sera inserido
	if (Arvore == DiretorioAtual){
		DiretorioCriado->prox = Arvore->pFilho;
		Arvore->pFilho = DiretorioCriado;
		
	}
		
	else{
		//Funcao para procurar o diretorio de maneira recursiva
		for(Aux = Arvore->pFilho; Aux != NULL; Aux = Aux->prox){
			insereDiretorioReferencia(Aux, DiretorioAtual, DiretorioCriado);
			
		}
	}
	
	Arvore = Aux;
}

/*
Funcao libera diretorios
*/
void liberaDiretorios(Dir* Arvore){
	Dir* aux = Arvore->pFilho;
	Dir* pr;
	
	while(aux != NULL){
		pr = aux->prox;
		liberaDiretorios(aux);
		aux = pr;
	}
	free(Arvore);
	
}


/*
Funcao para excluir diretorios
*/

void excluirDiretorio(Dir* DiretorioAtual, char* NomeDiretorio) {
	//Verificando se o diretorio esta vazio
    if (DiretorioAtual == NULL) {
        printf("Diretório atual é inválido.\n");
        return;
    }

    Dir* anterior = NULL;
    Dir* atual = DiretorioAtual->pFilho;
	
	//Procurando diretorios
    while (atual != NULL && strcmp(atual->nome, NomeDiretorio) != 0) {
        anterior = atual;
        atual = atual->prox;
    }
	
	//Verificacao caso o diretorio nao seja encontrado
    if (atual == NULL) {
        printf("Diretório '%s' não encontrado.\n", NomeDiretorio);
        return;
    }

	//Atualizando os ponteiros para remover o arquivo
    if (anterior == NULL) {
        // O diretório a ser removido é o primeiro filho
        DiretorioAtual->pFilho = atual->prox;
    } else {
        anterior->prox = atual->prox;
    }


    liberaDiretorios(atual);
}

/*
Funcao para criar arquivos
*/

void criaArquivo(Dir* DiretorioAtual) {
    if (DiretorioAtual == NULL) {
        printf("Diretório atual é inválido.\n");
        return;
    }

    // Alocando memoria
    Dir* arquivo = (Dir*)malloc(sizeof(Dir));
    if (arquivo == NULL) {
        printf("Erro ao alocar memória para o arquivo.\n");
        return;
    }
    
    //Solicitando o nome do arquivo ao usuario, guardando em um outro char para juntar o nome ao diretorio atual para no final criar o caminho inteiro do arquivo
	char Nome[100];
    printf("Digite o nome do novo arquivo: ");
    fgets(Nome, sizeof(Nome), stdin);

    // Retirando o backspace
    size_t len = strlen(Nome);
    if (len > 0 && Nome[len - 1] == '\n') {
        Nome[len - 1] = '\0';
    }
	
	//Juntando as duas strings
	snprintf(arquivo->nome, sizeof(arquivo->nome), "%s/%s", DiretorioAtual->nome, Nome);
	
    //Solicitando o tamanho do arquivo ao usuario
    printf("Digite o tamanho do arquivo: ");
    scanf("%d", &(arquivo->tam));
    
    //Limpando buffer por precaucao
    getchar(); 
    

    // Inicializa os ponteiros
    arquivo->pFilho = NULL;
    arquivo->prox = NULL;

    // Insere o arquivo no diretório atual como um filho
    arquivo->prox = DiretorioAtual->pFilho;
    DiretorioAtual->pFilho = arquivo;

    printf("Arquivo '%s' de tamanho %d bytes criado com sucesso!\n", arquivo->nome, arquivo->tam);
}

/*
Funcao para contar o tamanho de um um diretorio e dos seus respectivos subdiretorios
*/

void atualizaTamanhos(Dir* DiretorioAtual) {
    if (DiretorioAtual == NULL) return;

    // Inicializando com 0 por precaucao
    int tamanhoTotal = 0;

    // Percorrendo todos os subdiretorios
    for (Dir* filho = DiretorioAtual->pFilho; filho != NULL; filho = filho->prox) {
        // Se o filho for um diretório, chama recursivamente
        if (filho->pFilho != NULL) {
            atualizaTamanhos(filho);
        }
        // Soma o tamanho do filho ao total
        tamanhoTotal += filho->tam;
    }

    // Atualizando o tamanho
    DiretorioAtual->tam = tamanhoTotal;

    // Exibe o nome do diretório e seu tamanho
    printf("========================================\nDiretorio: %s | Tamanho total: %d bytes\n========================================", DiretorioAtual->nome, DiretorioAtual->tam);
}

/*
Funcao para imprimir apenas o nome do diretorio
*/

void imprimeNomeDiretorio(Dir* DiretorioAtual){
	
	//Imprimindo o nome do diretorio atual
	char* NomePai;
	NomePai = DiretorioAtual->nome;
	printf("========================================\nVOCE ESTA NO DIRETORIO: %s/\n========================================\n", NomePai);
	
}

