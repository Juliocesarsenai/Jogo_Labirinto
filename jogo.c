#include <stdio.h>

#include <stdlib.h>

#include <stdbool.h>



#ifdef _WIN32

#include <windows.h>

#else

#include <unistd.h>

#endif



#define DIMENSION 20 // define o tamanho do mundo

// variáveis globais

int N=DIMENSION; // dimensão da matriz quadrada que representa o mundo

char matriz[DIMENSION][DIMENSION]; // matriz representando o mundo

char matriz_2[DIMENSION][DIMENSION]; // matriz representando o caminho pelo qual já passou, evitando voltas

int rodada; // rodada (cada tentativa de movimento equivale a uma rodada)

int roboLinha,roboColuna; // posição do robô

int premioLinha, premioColuna; // posição do prêmio



bool config();

bool carrega_mundo();

bool encontra_caractere(char, int *, int *);

void imprime_mundo();

bool fim_de_jogo();

bool move(int,int);

int getRoboLinha();

int getRoboColuna();

void espera_um_segundo();



int main() {

    // configuração inicial do jogo

    if (!config() ) {

        return 1; // falha ao carregar configurações

    }

    /************************************************ Declare e inicialize todas as suas variáveis aqui

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

        roboLinha=getRoboLinha();

        roboColuna=getRoboColuna();

        if (roboLinha > 0 && matriz[roboLinha - 1][roboColuna] != '*' && matriz_2[roboLinha - 1][roboColuna] != '.') {

            move(roboLinha - 1, roboColuna);

            matriz_2[roboLinha+1][roboColuna] = '.'; //assim o robô não volta por onde já passou e o caminho da tela não é alterado por um "."

        } else if (roboColuna > 0 && matriz[roboLinha][roboColuna - 1] != '*' && matriz_2[roboLinha][roboColuna - 1] != '.') {

            move(roboLinha, roboColuna - 1);

            matriz_2[roboLinha][roboColuna+1] = '.';

        } else if (roboLinha < DIMENSION - 1 && matriz[roboLinha + 1][roboColuna] != '*' && matriz_2[roboLinha + 1][roboColuna] != '.') {

            move(roboLinha + 1, roboColuna);

            matriz_2[roboLinha-1][roboColuna] = '.';

        } else if (roboColuna < DIMENSION - 1 && matriz[roboLinha][roboColuna + 1] != '*' && matriz_2[roboLinha][roboColuna + 1] != '.') {

            move(roboLinha, roboColuna + 1);

            matriz_2[roboLinha][roboColuna-1] = '.';



        }

       

        // espera por 1 segundo para executar próximo movimento

        espera_um_segundo();

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

    // encontra a posição do prêmio no mapa carregado

    premioLinha = -1;

    premioColuna = -1;

    if (!encontra_caractere('$', &premioLinha, &premioColuna)) {

        premioLinha = 0;

        premioColuna = 0;

    }

   

    // incializa contador de rodadas

    rodada=1;

    //posiciona o robô no mundo

    matriz[roboLinha][roboColuna]='R';

    // tudo pronto, vamos jogar

    return true;

}



bool carrega_mundo() {

    FILE *arquivo;

    int i, j;

 

    // Abre o arquivo para leitura

    arquivo = fopen("entrada4.txt", "r");



    if (arquivo == NULL) {

        printf("Erro ao abrir o arquivo.\n");

        return false;

    }



    // Lê os caracteres do arquivo

    for (int i = 0; i < N; i++) {

        for (int j = 0; j < N; j++) {

            fscanf(arquivo, " %c", &matriz[i][j]);

            // Verifica se o caractere é válido

            if (matriz[i][j] != '_' && matriz[i][j] != '*' && matriz[i][j] != '$') {

                printf("Caractere invalido encontrado.\n");

                fclose(arquivo);

                return false;

            }

            matriz_2[i][j] = matriz[i][j]; //iguala as 2 matrizes para depois alterar a matriz 2 sem afetar o que aparece em tela;

        }

    }



    fclose(arquivo);    

    return true;

}



bool encontra_caractere(char alvo, int *linha, int *coluna) {

    for (int i = 0; i < N; i++) {

        for (int j = 0; j < N; j++) {

            if (matriz[i][j] == alvo) {

                *linha = i;

                *coluna = j;

                return true;

            }

        }

    }

    return false;

}



void espera_um_segundo() {

#ifdef _WIN32

    Sleep(1000);

#else

    sleep(1);

#endif

}



void imprime_mundo() {

#ifdef _WIN32

        system("cls");

#else

        system("clear");

#endif

        printf("Rodada: %d\n",rodada);

        for (int i = 0; i < N; i++) {

            for (int j = 0; j < N; j++) {

                printf("%c ", matriz[i][j]);

            }

            printf("\n");

        }  

}



bool fim_de_jogo() {

    if (rodada==1000) {

        printf("GAME OVER:SUA ENERGIA ACABOU\n");

        return true;        

    }

    if (roboLinha==premioLinha && roboColuna==premioColuna) {

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