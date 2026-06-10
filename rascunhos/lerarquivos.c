
#include<stdio.h> 
#include<stdlib.h> 

#define TAMANHO 20 
char tabuleiro[TAMANHO][TAMANHO];
int n = TAMANHO; // variável de controle 

void imprimir_tabuleiro() { 
    FILE*arquivo; 
    int i, j; 
    arquivo = fopen("mundo.txt", "r"); // leitura do mundo 

    if (arquivo == NULL) 
        printf("Arquivo nAo encontrado! \n");

    for (i = 0; i < n; i++) { 
        for (j = 0; j < n; j++) 
            fscanf(arquivo, " %c", &tabuleiro[i][j]); // lê os carecteres e salva na matriz
    } 

    for (i = 0; i < n; i++) {  
        for (j = 0; j < n; j++) { 
            printf(" %c", tabuleiro[i][j]);
            }
        printf("\n");
    } 
}

int main () { 
    imprimir_tabuleiro();
}
