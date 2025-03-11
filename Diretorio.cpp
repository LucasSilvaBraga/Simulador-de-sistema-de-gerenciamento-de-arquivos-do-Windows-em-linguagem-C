#include <iostream>
#include "ArvoreNL.h"

/* 
TRABALHO ESTRUTURA DE DADOS SEGUNDO BIMESTRE
INTEGRANTES: LUCAS SILVA BRAGA, IGOR ANGELO VASCONCELOS
*/


int main() {
	
	int Opcao;
	Dir *Arvore, *DiretorioCriado, *DiretorioAtual, *DiretorioAnterior, *DiretorioAnteriorPai;
	char NomeBuscado[100];
	
	Arvore = criaRaiz();
	DiretorioAtual = Arvore;
	DiretorioAnterior = NULL;
	DiretorioAnteriorPai = NULL;
	
	while(Opcao != 10){
		printf("\n[1]Nome diretorio\n[2]Listar diretorio\n[3]Abrir diretorio\n[4]Voltar para o diretorio anterior\n[5]Criar diretorio\n[6]Excluir diretorio\n[7]Tamanho diretorio\n[8]Criar arquivo\n[9]Excluir um arquivo\n[10]Sair\n");
		scanf("%d", &Opcao);
		//Limpando o buffer para que ele nao interfira na leitura do fgets
		fflush(stdin);
		
		switch(Opcao){
		
			case 1:
				imprimeNomeDiretorio(DiretorioAtual);
				break;	
		
			case 2:
				imprimeFilhosDiretorios(DiretorioAtual);
				break;
			
			case 3:{
				
				//Obtendo o nome do diretorio desejado atravez da funcao fgets e usando fflush para limpar o buffer
				
				printf("Qual o nome do diretorio desejado (favor digitar o caminho completo):");
				fgets(NomeBuscado , sizeof(NomeBuscado), stdin);
				fflush(stdin);
				
				//Mesmo com a funcao fgets a leitura du ultimo caractere esta sendo "\n" por isso precisei implementar esse pequeno bloco para remover esse caractere
				//Alem do mais por conta da "size_t" o switch case buga, pois ele entende que o codigo esta saindo de um caso antes do break por isso foi preciso co-
				//locar colchetes no case 3, 6 e 9.
				
				size_t len = strlen(NomeBuscado);
    			if (len > 0 && NomeBuscado[len - 1] == '\n') {
        		NomeBuscado[len - 1] = '\0';
  				}
  				
  				//Retornando o diretorio atual para uma variavel
  				
				DiretorioAtual = diretorioAtualFilhos(Arvore, NomeBuscado, DiretorioAtual);
				
				break;
				}
				
			case 4:
				DiretorioAtual = voltarDiretorio(Arvore, DiretorioAtual, DiretorioAnterior);
				break;
				
			case 5:
				DiretorioCriado = criaDiretorio(DiretorioAtual);
				insereDiretorioReferencia(Arvore, DiretorioAtual, DiretorioCriado);
				
				break;
				
			case 6:{
				printf("Digite o nome do diretorio que deseja excluir (favor digitar o caminho completo):");
				fgets(NomeBuscado , sizeof(NomeBuscado), stdin);
				fflush(stdin);
				
				size_t len = strlen(NomeBuscado);
    			if (len > 0 && NomeBuscado[len - 1] == '\n') {
        		NomeBuscado[len - 1] = '\0';
  				}
  				
  				excluirDiretorio(DiretorioAtual, NomeBuscado);
				break;
				
			}
			case 7:
				atualizaTamanhos(DiretorioAtual);
				break;
				
			case 8:
				criaArquivo(DiretorioAtual);
				break;
				
			case 9:{
				printf("Digite o nome do arquivo que deseja excluir (favor digitar o caminho completo):");
				fgets(NomeBuscado , sizeof(NomeBuscado), stdin);
				fflush(stdin);
				
				size_t len = strlen(NomeBuscado);
    			if (len > 0 && NomeBuscado[len - 1] == '\n') {
        		NomeBuscado[len - 1] = '\0';
  				}
  				
  				excluirDiretorio(DiretorioAtual, NomeBuscado);
				break;
				
			}
				
	

		
				
		
		
	}
		
		
	}

	
	
	
	
	
	
	return 0;
}
