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



long int TArquivo() {}

void Incluir() {}

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
