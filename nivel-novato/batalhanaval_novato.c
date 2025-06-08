#include <stdio.h>

#define TAM 10
#define NAVIO 3

void imprimirTabuleiro(char tabuleiro[TAM][TAM]) {
    printf("   ");
    for (int i = 0; i < TAM; i++) printf("%d ", i);
    printf("\n");

    for (int i = 0; i < TAM; i++) {
        printf("%2d ", i);
        for (int j = 0; j < TAM; j++) {
            printf("%c ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

int main() {
    char tabuleiro[TAM][TAM];

    // Inicializa o tabuleiro com água ('~')
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            tabuleiro[i][j] = '~';
        }
    }

    // Posição dos 3 navios (cada um com 3 partes)
    // Navio 1 - horizontal na linha 2
    int l1 = 2, c1 = 4;
    for (int i = 0; i < NAVIO; i++) {
        tabuleiro[l1][c1 + i] = '#';
    }

    // Navio 2 - vertical na coluna 7
    int l2 = 5, c2 = 7;
    for (int i = 0; i < NAVIO; i++) {
        tabuleiro[l2 + i][c2] = '#';
    }

    // Navio 3 - horizontal na linha 8
    int l3 = 8, c3 = 1;
    for (int i = 0; i < NAVIO; i++) {
        tabuleiro[l3][c3 + i] = '#';
    }

    // Exibe o tabuleiro final
    printf("\nTABULEIRO FINAL:\n");
    imprimirTabuleiro(tabuleiro);

    return 0;
}
