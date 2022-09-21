#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

struct Jogador{
	char Nome[20], Posicao[20];
    int idade;
    float Altura, Peso, VelocidadeMax; //se velocidadeMax == 0 o jogador eh considerado excluido
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

int ehRepetido(char nome[20]){
	fseek(ArqJogadores, 0, 0);

	do{
		fread(&RgJogador, Tamanho, 1, ArqJogadores);
        if ( (strcmp(RgJogador.Nome, nome) == 0) && (RgJogador.VelocidadeMax != 0) )
            return 1;
	}
	while(!feof(ArqJogadores));
	return 0;
}

void Incluir() {

	char R;
	char NomeJogador[20];
	float VelocidadeMax;
	
	do {
		
	    system("cls");
	    printf("*** INCLUSAO DE JOGADOR ***\n\n");
	    
	    printf("Nome do jogador: ");
	    scanf("%s", &NomeJogador);

		if (ehRepetido(NomeJogador)){
			printf("Jogador repetido\n\n");
			printf("Deseja fazer uma nova inclusao? S/N\n");
			scanf(" %c", &R);
			R = toupper(R);
			continue;
		}

		strcpy(RgJogador.Nome, NomeJogador);
	    
	    printf("Posicao do jogador: ");
	    scanf("%s", &RgJogador.Posicao);
	    
	    printf("Idade do jogador: ");
	    scanf("%d", &RgJogador.idade);
	    
	    printf("Altura do jogador: ");
	    scanf("%f", &RgJogador.Altura);
	    
	    printf("Peso do jogador: ");
	    scanf("%f", &RgJogador.Peso);
	    
	    printf("Velocidade maxima do jogador: ");
	    scanf("%f", &VelocidadeMax);
		
		while(VelocidadeMax <= 0){
			system("cls");
			printf("Velocidade maxima invalida\n");
			printf("Digite um valor positivo maior que 0\n");
			printf("Velocidade maxima do jogador: ");
			scanf("%f", &VelocidadeMax);
		}

		RgJogador.VelocidadeMax = VelocidadeMax;

		fseek(ArqJogadores, 0, 2);
		fwrite(&RgJogador, Tamanho, 1, ArqJogadores);
		
		printf("\n\nNova inclusao? S/N ");
		scanf(" %c", &R);
		R = toupper(R);
	    
	} while (R != 'N');
  
  return;
  
}

void Excluir(){}

void Alterar(){}

void Consultar() {}

void LTodos() {
	system("cls");
	printf("**** Consula Total ****\n\n");
	fseek(ArqJogadores, 0, 0);

	do{
		fread(&RgJogador, Tamanho, 1, ArqJogadores);

		if ( !feof(ArqJogadores) && (RgJogador.VelocidadeMax != 0) ){
			printf("Nome: %s\n", RgJogador.Nome);
			printf("Idade: %i\n", RgJogador.idade);
			printf("Altura: %f\n", RgJogador.Altura);
			printf("Peso: %f\n", RgJogador.Peso);
			printf("Posicao: %s\n", RgJogador.Posicao);
			printf("Velocidade Maxima: %f\n\n\n", RgJogador.VelocidadeMax);
		}
	}
	while (!feof(ArqJogadores));

	system("pause");
	return;
}

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
		printf("C - Consultar jogador\n"); //Usuario sera levado a outro menu perguntando se a consulta sera por nome ou por posicao
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
