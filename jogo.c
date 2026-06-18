#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <Windows.h>

#define DIMENSION 20 // define o tamanho do mundo 
// variáveis globais
int N=DIMENSION; // dimensão da matriz quadrada que representa o mundo
char matriz[DIMENSION][DIMENSION]; // matriz representando o mundo
int rodada; // rodada (cada tentativa de movimento equivale a uma rodada)
int roboLinha,roboColuna; // posição do robô

bool config();
bool carrega_mundo();
void imprime_mundo();
bool fim_de_jogo();
bool move(int,int);
int getRoboLinha();
int getRoboColuna();

int main() {
	// configuração inicial do jogo
	if (!config() ) {
		return 1; // falha ao carregar configurações
	}
	/************************************************ 
	Declare e inicialize todas as suas variáveis aqui
	*************************************************/
	
	while (true) {    
		imprime_mundo(); // imprime situação atual do mundo
		if (fim_de_jogo()) { // verifica se o jogo acabou
			break;
		}
		/************************************************
			Coloque aqui a sua lógica do jogo 
			para tentar chegar ao prêmio
		************************************************/	
		// Exemplo	
		roboLinha=getRoboLinha();
		roboColuna=getRoboColuna();
		move(roboLinha-1,roboColuna-1);
		
		// espera por 1 segundos para executar próximo movimento
        Sleep(1000); 
	}


    return 0;
}
bool config() {
	// carrega o arquivo com definições do mundo
	if (!carrega_mundo()) {
		return false;
	}
	// posição inicial do robô (canto inferior direito)
 	roboLinha=DIMENSION-1;
	roboColuna=DIMENSION-1;	
	// incializa contador de rodadas
	rodada=1;
	//posiciona o robô no mundo	
	matriz[roboLinha][roboColuna]='R';
	//posiciona o prêmio no mundo	
	matriz[0][0]='$';	
	// tudo pronto, vamos jogar
	return true;
}
bool carrega_mundo() {
    FILE *arquivo;
    int i, j;
 
    // Abre o arquivo para leitura
    arquivo = fopen("entrada.txt", "r");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return false;
    }

    // Lê os caracteres do arquivo
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            fscanf(arquivo, " %c", &matriz[i][j]);
            // Verifica se o caractere é válido
            if (matriz[i][j] != '_' && matriz[i][j] != '*') {
                printf("Caractere invalido encontrado.\n");
                fclose(arquivo);
                return false;
            }
        }
    }

    fclose(arquivo);	
    return true;
}
void imprime_mundo() {
		system("cls");
		printf("Rodada: %d\n",rodada);
		for (int i = 0; i < N; i++) {
        	for (int j = 0; j < N; j++) {
    	        printf("%c ", matriz[i][j]);
        	}
        	printf("\n");
    	}	
}
bool fim_de_jogo() {
	if (rodada==40) {
		printf("GAME OVER:SUA ENERGIA ACABOU\n");
		return true;		
	}
	if (roboLinha==0 && roboColuna==0) {
		printf("GAME OVER:VOCE VENCEU\n");
		return true;
	}
		
	return false;
}
bool move(int newLinha,int newColuna) {
	rodada++;
	 
	if (newLinha<0 || newLinha>DIMENSION-1 || newColuna<0 || newColuna>DIMENSION-1) {
	    	// saiu do mundo
			return false;
	} else if (matriz[newLinha][newColuna]=='*') {
	    	// atingiu um obstáculo
			return false;		
	}
	else if (abs(newLinha-roboLinha)>1 || abs(newColuna-roboColuna)>1) {
		// tentativa de mover para uma casa não adjacente
		return false;
	}
	else {
		matriz[roboLinha][roboColuna]='_';
		roboLinha=newLinha;
		roboColuna=newColuna;
		matriz[roboLinha][roboColuna]='R';
		return true;		
	}
}
int getRoboLinha() {
	return roboLinha;
}
int getRoboColuna(){
	return roboColuna;
}