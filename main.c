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
//AAAAAAAAAAAAAA


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
	    
	    printf("Altura do jogador (em metros): ");
	    scanf("%f", &RgJogador.Altura);
	    
	    printf("Peso do jogador (em kg): ");
	    scanf("%f", &RgJogador.Peso);
	    
	    printf("Velocidade maxima do jogador (em m/s): ");
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
  //a
}

void Excluir(){
	char nome[20];
	int achou = 0;

	if (TArquivo()!=0){
		fclose(ArqJogadores);
		ArqJogadores = fopen("Jogadores.dat","r+b");
		fseek(ArqJogadores, 0, 0);

		system("cls");
		printf("**** Excluir jogador ****\n\n");
		printf("Digite o nome do jogador a ser excluido: ");
		scanf("%s", nome);

		do{
			fread(&RgJogador, Tamanho, 1, ArqJogadores);

			if ( (strcmp(nome, RgJogador.Nome) == 0) && (RgJogador.VelocidadeMax != 0) ){
				achou = 1;
			}
		}
		while( !feof(ArqJogadores) && (achou==0) );

		if(achou==0){
			printf("\nRegistro inexistente!\n");
			system("pause");
		}
		else{
			RgJogador.VelocidadeMax = 0;

			fseek(ArqJogadores, -Tamanho, 1);
			fwrite(&RgJogador, Tamanho, 1, ArqJogadores);
			printf("\n\n**** Registro excluido com sucesso! ****\n\n");
			system("pause");

			fclose(ArqJogadores);
			ArqJogadores = fopen("Jogadores.dat", "a+b");
		}
	}
	else{
		printf("Arquivo vazio, nao ha jogadores para excluir\n\n");
		system("pause");
	}
	return;


}



void Alterar(){
	char nome[20];
	int achou = 0;
  float VelocidadeMax;

	if (TArquivo()!=0){
		fclose(ArqJogadores);
		ArqJogadores = fopen("Jogadores.dat","r+b");
		fseek(ArqJogadores, 0, 0);

		system("cls");
		printf("**** Alteracao de dados ****\n\n");
		printf("Digite o nome do jogador a ser alterado: ");
		scanf("%s", nome);

		do{
			fread(&RgJogador, Tamanho, 1, ArqJogadores);

			if ( (strcmp(nome, RgJogador.Nome) == 0) && (RgJogador.VelocidadeMax != 0) ){
				achou = 1;
				printf("\n\n\nNome: %s\n", RgJogador.Nome);
				printf("Idade: %i anos\n", RgJogador.idade);
				printf("Altura: %.2f m\n", RgJogador.Altura);
				printf("Peso: %.2f kg\n", RgJogador.Peso);
				printf("Posicao: %s\n", RgJogador.Posicao);
				printf("Velocidade Maxima: %.2f m/s\n\n\n", RgJogador.VelocidadeMax);
				system("pause");
			}
		}
		while( !feof(ArqJogadores) && (achou==0) );

		if(achou==0){
			printf("\nRegistro inexistente!\n");
			system("pause");
		}
		else{
			printf("\nQual a nova idade? ");
			scanf("%i", &RgJogador.idade);

			printf("\nQual o novo peso? ");
			scanf("%f", &RgJogador.Peso);

			printf("\nQual a nova posicao? ");
			scanf("%s", &RgJogador.Posicao);

			printf("\nQual a nova velocidade maxima? ");
			scanf("%f", &VelocidadeMax);

      while(VelocidadeMax <= 0){
			 system("cls");
			 printf("Velocidade maxima invalida\n");
			 printf("Digite um valor positivo maior que 0\n");
			 printf("Velocidade maxima do jogador: ");
			 scanf("%f", &VelocidadeMax);
		}

      RgJogador.VelocidadeMax = VelocidadeMax;
      
			fseek(ArqJogadores, -Tamanho, 1);
			fwrite(&RgJogador, Tamanho, 1, ArqJogadores);
			printf("\n\n**** Registro alterado com sucesso! ****\n\n");
			system("pause");

			fclose(ArqJogadores);
			ArqJogadores = fopen("Jogadores.dat", "a+b");
		}
	}
	else{
		printf("Arquivo vazio, nao ha dados para alterar\n\n");
		system("pause");
	}
	return;
}

void Consultar() {
	char nome[20];

	system("cls");
	printf("**** Consultar jogador por nome****\n\n");
	printf("Insira o nome do jogador que deseja consultar: ");
	scanf("%s", nome);

	fseek(ArqJogadores, 0, 0);
	do{
		fread(&RgJogador, Tamanho, 1, ArqJogadores);

		if ( !feof(ArqJogadores) && (RgJogador.VelocidadeMax != 0) && (strcmp(nome, RgJogador.Nome)==0) ){
			printf("Nome: %s\n", RgJogador.Nome);
			printf("Idade: %i anos\n", RgJogador.idade);
			printf("Altura: %.2f m\n", RgJogador.Altura);
			printf("Peso: %.2f kg\n", RgJogador.Peso);
			printf("Posicao: %s\n", RgJogador.Posicao);
			printf("Velocidade Maxima: %.2f m/s\n\n\n", RgJogador.VelocidadeMax);

			system("pause");
			return;
		}
	}
	while (!feof(ArqJogadores));

	printf("\nRegistro inexistente\n");
	system("pause");
	return;
}

void LTodos() {
	system("cls");
	printf("**** Consula Total ****\n\n");
	fseek(ArqJogadores, 0, 0);

	do{
		fread(&RgJogador, Tamanho, 1, ArqJogadores);

		if ( !feof(ArqJogadores) && (RgJogador.VelocidadeMax != 0) ){
			printf("Nome: %s\n", RgJogador.Nome);
			printf("Idade: %i anos\n", RgJogador.idade);
			printf("Altura: %.2f m\n", RgJogador.Altura);
			printf("Peso: %.2f kg\n", RgJogador.Peso);
			printf("Posicao: %s\n", RgJogador.Posicao);
			printf("Velocidade Maxima: %.2f m/s\n\n\n", RgJogador.VelocidadeMax);
		}
	}
	while (!feof(ArqJogadores));

	system("pause");
	return;
}

void CPosicao(){
	char posicao[20];
	
		system("cls");
		printf("**** Listar jogadores por posicao ****\n\n");
		printf("Insira a posicao que deseja consultar: ");
		scanf("%s", posicao);
	
		fseek(ArqJogadores, 0, 0);
		do{
			fread(&RgJogador, Tamanho, 1, ArqJogadores);
	
			if ( !feof(ArqJogadores) && (RgJogador.VelocidadeMax != 0) && (strcmp(posicao, RgJogador.Posicao)==0) ){
				printf("-------------------------------------\n");
				printf("Nome: %s\n", RgJogador.Nome);
				printf("Idade: %i anos\n", RgJogador.idade);
				printf("Altura: %.2f m\n", RgJogador.Altura);
				printf("Peso: %.2f kg\n", RgJogador.Peso);
				printf("Posicao: %s\n", RgJogador.Posicao);
				printf("Velocidade Maxima: %.2f m/s\n", RgJogador.VelocidadeMax);
				printf("-------------------------------------\n");
			}
		}
		while (!feof(ArqJogadores));
		system("pause");
		return;}

int main(){
	
	ArqJogadores = fopen("Jogadores.dat", "a+b");
	char Opcao;

	do {

		system("cls");
		
		printf("\n\n> > > REGISTRO E CONSULTA DE JOGADORES < < < \n\n");
		
		printf("O QUE DESEJA FAZER AGORA? \n\n");
		printf("I - Incluir novo jogador\n");
		printf("A - Alterar dados de jogador\n");  
		printf("E - Remover jogador\n");
		printf("C - Consultar jogador por nome\n");
		printf("P - Listar jogadores por posicao\n");	
		printf("T - Listar todos os jogadores\n");
		printf("S - Sair do programa\n\n");
		
		scanf(" %c", &Opcao);
		Opcao = toupper(Opcao);
		
		switch (Opcao){
			case 'I': Incluir(); break;
			case 'E': Excluir(); break;
			case 'A': Alterar(); break;
			case 'C': Consultar(); break;
			case 'T': LTodos(); break;
			case 'P': CPosicao(); break;
			}	
	}

	while (Opcao != 'S');
	fclose(ArqJogadores);
	return 0;
  }
