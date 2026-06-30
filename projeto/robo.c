#include<stdio.h> 
#include<stdlib.h> 
#include<stdbool.h>
#include<windows.h> 

#define VERDE "\033[32m"
#define RESET "\033[0m"
#define TAMANHO 20 

// Estratégia utilizada: Como o prêmio está na posição [0][0], a estratégia utilizada foi a prioridade para movimentos para a esquerda e para cima, pois ambos se aproximam do prêmio.


// VARIÁVEIS
char tabuleiro[TAMANHO][TAMANHO];
int n = TAMANHO; // variável de controle 
int rodada = 1;  // contador de rodadas
int roboLinha, roboColuna; // posição do robo
int distancia = 0;


// FUNÇÕES
bool inicializarMundo(); 
bool configInicial();
void imprimirMundo(); 
bool fimdeJogo();
int validacaodeMovimento();
int move(); 
int getRoboLinha(); 
int getRoboColuna();

int main () { 
    inicializarMundo();
    if (inicializarMundo() == false) 
        return 0; // sai da função caso o arquivo não for encontrado
    
    configInicial();
    imprimirMundo();
    Sleep(500);
    system("cls");
    while (!fimdeJogo()) {
        validacaodeMovimento();
        move();
        imprimirMundo();
        if (fimdeJogo()) 
            break;
        else {
        Sleep(500);
        system("cls"); 
        }
    }
}

bool inicializarMundo() { // função de leitura 
    FILE*arquivo; 
    int i, j; 
    arquivo = fopen("mundo2.txt", "r"); // leitura do mundo 
    
    if (arquivo == NULL) {
        printf("Arquivo nao encontrado! \n");
        return false;

    } 

    for (i = 0; i < n; i++) { 
        for (j = 0; j < n; j++) 
            fscanf(arquivo, " %c", &tabuleiro[i][j]); // lê os carecteres e salva na matriz
    } 
    fclose(arquivo);
    return true;
}

bool configInicial() { // definiçao e leitura das posições iniciais
    tabuleiro[0][0] = '$'; 
    roboLinha = TAMANHO - 1;
    roboColuna = TAMANHO - 1;
    tabuleiro[roboLinha][roboColuna] = 'R';
    roboLinha = getRoboLinha(); 
    roboColuna = getRoboColuna();

    // distancia Mnahattan: d = |x1 - x2| + |y1 - y2|, entretanto não é preciso realizar a subtração pois x1 e y1 sempre serão 0 (posição do prêmio).
    distancia = roboLinha + roboColuna;
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

    printf("\nRodada numero: %d\n", rodada); 
    printf("O robo esta na linha %d e na coluna %d\n", roboLinha, roboColuna);
    printf("Distancia ate o premio: %d movimentos\n", distancia);
}

bool fimdeJogo() { // condições para o jogo acabar
    if (tabuleiro[0][0] == 'R' && rodada < 60) { 
        printf(VERDE "Premio encontrado! \n" RESET);
        return true;
    }
    
    if (rodada == 60) {
        printf("O robo ficou sem energia, fim de jogo!");
        return true;
    }
    
return false;
}

int validacaodeMovimento() { // função para validar e escolher a melhor opção de movimento
    bool valid;    
    n = 0;

    if (tabuleiro[roboLinha - 1][roboColuna] == '$' || tabuleiro[roboLinha][roboColuna - 1] == '$') { // pegar o prêmio caso esteja em uma casa adjacente
        n = 4;
        return 0;
    }
    
    if (tabuleiro[roboLinha][roboColuna - 1] != '_' || roboColuna - 1 < 0 || roboColuna + 1 < 0) { // invalida movimentos para obstáculos e para fora do tabuleiro
        n = 1;
        
        if (n == 1 && tabuleiro[roboLinha - 1][roboColuna] != '_' || roboLinha - 1 < 0) {
            n = 2;
            
            if (n == 2 && tabuleiro[roboLinha][roboColuna + 1] != '_' || roboColuna + 1 < 20) {
                n = 3;

                if (n == 3 && tabuleiro[roboLinha + 1][roboColuna] != '_' || roboLinha + 1 < 20) {
                    printf("\nNao ha movimentos validos disponiveis!.");
                }
            }
        }
    }
}



int move() { // função para movimento
    int novaLinha, novaColuna;  
    switch(n) {
            case 0: // robo anda para a esquerda 
            novaColuna = roboColuna - 1; 
            tabuleiro[roboLinha][roboColuna] = '#';
            tabuleiro[roboLinha][novaColuna] = 'R';
            roboColuna = novaColuna;
            distancia = roboColuna + roboLinha;
            rodada++;
            break; 

            case 1: // robo anda para cima
            novaLinha = roboLinha - 1; 
            tabuleiro[roboLinha][roboColuna] = '#'; 
            tabuleiro[novaLinha][roboColuna] = 'R'; 
            roboLinha = novaLinha;
            distancia = roboColuna + roboLinha;
            rodada++;
            break; 

            case 2: // robo anda para a direita
            novaColuna = roboColuna + 1; 
            tabuleiro[roboLinha][roboColuna] = '#';
            tabuleiro[roboLinha][novaColuna] = 'R'; 
            roboColuna = novaColuna; 
            distancia = roboColuna + roboLinha;
            rodada++;
            break; 

            case 3: // robo anda para baixo 
            novaLinha = roboLinha + 1; 
            tabuleiro[roboLinha][roboColuna] = '#'; 
            tabuleiro[novaLinha][roboColuna] = 'R'; 
            roboLinha = novaLinha;
            distancia = roboColuna + roboLinha;
            rodada++;
            break;
        
            case 4: // robo pega o prêmio se estiver em uma casa adjacente
            novaColuna = 0; 
            novaLinha = 0; 
            tabuleiro[roboLinha][roboColuna] = '#';  
            tabuleiro[novaLinha][novaColuna] = 'R';  
            roboLinha = novaLinha; 
            roboColuna = novaColuna; 
            distancia = 0;
            rodada++; 
            break;
        } 
    } 

int getRoboLinha() {
	return roboLinha;
}

int getRoboColuna(){
	return roboColuna;
}