#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

struct Jogador{
	char Nome[20], Posicao[20];
    int idade;
    float Altura, Peso, VelocidadeMax;
};
  
typedef struct Jogador TpJogador;

TpJogador RgJogador;
  
FILE *ArqJogadores;

long int Tamanho = sizeof(TpJogador);



long int TArquivo() {
	
	fseek(ArqJogadores, 0, 2);
	long int R = ftell(ArqJogadores)/Tamanho;
	return R;

}


void Incluir() {

	char R;
	char NomeJogador[20], PosicaoJogador[20];
	int IdadeJogador;
	float AlturaJogador, PesoJogador, VelocidadeMax;
	
	do {
		
	    system("cls");
	    printf("*** INCLUSAO DE JOGADOR ***\n\n");
	    
	    printf("Nome do jogador: ");
	    scanf("%s", &NomeJogador);
	    
	    printf("Posicao do jogador: ");
	    scanf("%s", &PosicaoJogador);
	    
	    printf("Idade do jogador: ");
	    scanf("%d", &IdadeJogador);
	    
	    printf("Altura do jogador: ");
	    scanf("%f", &AlturaJogador);
	    
	    printf("Peso do jogador: ");
	    scanf("%f", &PesoJogador);
	    
	    printf("Velocidade maxima do jogador: ");
	    scanf("%f", &VelocidadeMax);
	    
	    if(TArquivo()!=0){
	    	
			fclose(ArqJogadores);
			ArqJogadores = fopen("Jogadores.dat", "r+b");
			fseek(ArqJogadores, 0, 0);
			int Achou = 0;
			
			do {
				
				fread(&RgJogador, Tamanho, 1, ArqJogadores);
				
				if (strcmp(RgJogador.Nome, NomeJogador) == 0) {
					
					Achou = 1;
					
					sprintf(RgJogador.Posicao, "%s", PosicaoJogador);
					RgJogador.idade = IdadeJogador;
					RgJogador.Altura = AlturaJogador;
					RgJogador.Peso = PesoJogador;
					RgJogador.VelocidadeMax = VelocidadeMax;
					
					fseek(ArqJogadores, -Tamanho, 1);
			    	fwrite(&RgJogador, Tamanho, 1, ArqJogadores);
			    	
				}
				
				if (feof(ArqJogadores)) {
				
					fseek(ArqJogadores, 0, 2);
					
					sprintf(RgJogador.Nome, "%s", NomeJogador);
					sprintf(RgJogador.Posicao, "%s", PosicaoJogador);
					RgJogador.idade = IdadeJogador;
					RgJogador.Altura = AlturaJogador;
					RgJogador.Peso = PesoJogador;
					RgJogador.VelocidadeMax = VelocidadeMax;
					
				    fwrite(&RgJogador, Tamanho, 1, ArqJogadores);
				    
				    break;
				    
				}
			} while (Achou == 0);
		}
		
		else {
			
			fseek(ArqJogadores,0,2);
			
			sprintf(RgJogador.Nome, "%s", NomeJogador);
			sprintf(RgJogador.Posicao, "%s", PosicaoJogador);
			RgJogador.idade = IdadeJogador;
			RgJogador.Altura = AlturaJogador;
			RgJogador.Peso = PesoJogador;
			RgJogador.VelocidadeMax = VelocidadeMax;
			
		    fwrite(&RgJogador, Tamanho, 1, ArqJogadores);
	    
		}
		
		printf("\nNova inclusao? S/N ");
	    scanf(" %c", &R);
	    R = toupper(R);
	    
	} while (R != 'N');
  
  return;
  
}

void Excluir(){}

void Alterar(){}

void Consultar() {}

void LTodos() {}

int main(){
	
	ArqJogadores = fopen("Jogadores.dat", "a+b");
	char Opcao;

	do {

		system("cls");
		
		printf("\n\n> > > REGISTRO E CONSULTA DE JOGADORES < < < \n\n");
		
		printf("O QUE DESEJA FAZER AGORA? \n\n");
		printf("I - Incluir novo jogador\n");
		printf("A - Alterar dados de jogador\n");  
		printf("E - Remover jogador c\n");
		printf("C - Consultar jogador\n"); //Usuário será levado a outro menu perguntando se a consulta será por nome ou por posição
		printf("T - Listar todos os jogadores\n");
		printf("S - Sair do programa\n\n");
		
		scanf(" %c", &Opcao);
		Opcao = toupper(Opcao);
		
		switch (Opcao){
			case 'I': Incluir(); break;
			case 'E': Excluir(); break;
			case 'A': Alterar(); break;
			case 'C': Consultar(); break;
			case 'T': LTodos(); break;}	
			}

	while (Opcao != 'S');
	fclose(ArqJogadores);
	return 0;
  }
