#include<stdio.h> 
#include<stdlib.h> 
#include<stdbool.h>
#include<math.h>

#define VERDE "\033[32m"
#define RESET "\033[0m"
#define TAMANHO 20 

// VARIÁVEIS
char tabuleiro[TAMANHO][TAMANHO];
int n = TAMANHO; // variável de controle 
int rodada = 1;  // contador de rodadas
int roboLinha, roboColuna; // posição do robo
float distancia = 0;


// FUNÇÕES
void inicializarMundo(); 
bool configInicial();
void imprimirMundo(); 
bool fimdeJogo();
int move(); 

int main () { 
    inicializarMundo();
    configInicial();
    imprimirMundo();
    move();
    imprimirMundo();
}


void inicializarMundo() { // função de leitura 
    FILE*arquivo; 
    int i, j; 
    arquivo = fopen("mundo.txt", "r"); // leitura do mundo 
    
    if (arquivo == NULL) 
        printf("Arquivo nao encontrado! \n");

    for (i = 0; i < n; i++) { 
        for (j = 0; j < n; j++) 
            fscanf(arquivo, " %c", &tabuleiro[i][j]); // lê os carecteres e salva na matriz
    } 
    fclose(arquivo);
}

bool configInicial() { // definiçao e leitura das posições iniciais
    tabuleiro[0][0] = '$'; 
    roboLinha = TAMANHO - 1;
    roboColuna = TAMANHO - 1;
    tabuleiro[roboLinha][roboColuna] = 'R';
    
    // distancia = raizquadrada[(x2 - x1)² + (y2 - y1)²], entretanto não é preciso realizar a subtração pois x1 e y1 sempre serão 0.
    distancia = sqrtf(pow(roboLinha, 2) + pow(roboColuna,2));
    printf("%f \n", distancia);
}

void imprimirMundo() { // impressão da matriz (labirinto)
    int i, j; 
    for (i = 0; i < TAMANHO; i++) {  
        for (j = 0; j < TAMANHO; j++) { 
            if (tabuleiro[i][j] == '#') 
                printf(VERDE " %c" RESET, tabuleiro[i][j]); // na função move(), as casas já visitadas pelo robo são marcadas com #, por isso coloquei para imprimir verde
            else
            printf(" %c", tabuleiro[i][j]);
            }
        printf("\n");
    } 
}

bool fimdeJogo() { // condições para o jogo acabar
    if (tabuleiro[0][0] == 'R' && rodada < 60) { 
        printf(VERDE "Rota encontrada! \n" RESET);
        return true;
    }
    
    if (rodada == 60) {
        printf("O robo ficou sem energia, fim de jogo!");
        return true;
    }
    
return false;
}

int validacaodeMovimento() { // função para validar e escolher a melhor opção de movimento

}




int move() { // função para movimento
    int novaLinha, novaColuna; 
    float novaDistancia;    
    switch(n) {
            case 0: // robo anda para a esquerda 
            novaColuna = roboColuna - 1; 
            tabuleiro[roboLinha][roboColuna] = '#';
            tabuleiro[roboLinha][novaColuna] = 'R';
            roboColuna = novaColuna;
            novaDistancia = sqrtf(pow(roboLinha, 2) + pow(roboColuna,2));
            break; 

            case 1: // robo anda para cima
            novaLinha = roboLinha - 1; 
            tabuleiro[roboLinha][roboColuna] = '#'; 
            tabuleiro[novaLinha][roboColuna] = 'R'; 
            roboLinha = novaLinha;
            novaDistancia = sqrtf(pow(roboLinha, 2) + pow(roboColuna,2));
            break; 

            case 2: // robo anda para a direita
            novaColuna = roboColuna + 1; 
            tabuleiro[roboLinha][roboColuna] = '#';
            tabuleiro[roboLinha][novaColuna] = 'R'; 
            roboColuna = novaColuna; 
            novaDistancia = sqrtf(pow(roboLinha, 2) + pow(roboColuna,2));
            break; 

            case 3: // robo anda para baixo 
            novaLinha = roboLinha + 1; 
            tabuleiro[roboLinha][roboColuna] = '#'; 
            tabuleiro[novaLinha][roboColuna] = 'R'; 
            roboLinha = novaLinha;
            novaDistancia = sqrtf(pow(roboLinha, 2) + pow(roboColuna,2));
            break;
        } 
    }