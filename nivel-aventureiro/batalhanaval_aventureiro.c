#include <stdio.h>
#include <string.h>

#define TAM 10
#define NAVIO 3
#define TOTAL_NAVIOS 3

typedef struct {
    int linha;
    int coluna;
    char orientacao; // 'H' ou 'V'
} Navio;

char tabuleiro[TAM][TAM];
Navio navios[TOTAL_NAVIOS];

void inicializarTabuleiro() {
    for (int i = 0; i < TAM; i++)
        for (int j = 0; j < TAM; j++)
            tabuleiro[i][j] = '~';
}

void posicionarNavios() {
    // Navio 1 - horizontal
    navios[0] = (Navio){2, 4, 'H'};
    // Navio 2 - vertical
    navios[1] = (Navio){5, 7, 'V'};
    // Navio 3 - horizontal
    navios[2] = (Navio){8, 1, 'H'};
}

void desenharNavios() {
    inicializarTabuleiro();

    for (int k = 0; k < TOTAL_NAVIOS; k++) {
        int l = navios[k].linha;
        int c = navios[k].coluna;
        for (int i = 0; i < NAVIO; i++) {
            if (navios[k].orientacao == 'H')
                tabuleiro[l][c + i] = '#';
            else
                tabuleiro[l + i][c] = '#';
        }
    }
}

void imprimirTabuleiro() {
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

int podeMover(Navio n, char direcao) {
    int novaLinha = n.linha;
    int novaColuna = n.coluna;

    if (direcao == 'W') novaLinha--;
    if (direcao == 'S') novaLinha++;
    if (direcao == 'A') novaColuna--;
    if (direcao == 'D') novaColuna++;

    for (int i = 0; i < NAVIO; i++) {
        int l = novaLinha + (n.orientacao == 'V' ? i : 0);
        int c = novaColuna + (n.orientacao == 'H' ? i : 0);

        if (l < 0 || l >= TAM || c < 0 || c >= TAM)
            return 0;

        // Verificar sobreposição
        for (int j = 0; j < TOTAL_NAVIOS; j++) {
            if (&n != &navios[j]) {
                for (int k = 0; k < NAVIO; k++) {
                    int lj = navios[j].linha + (navios[j].orientacao == 'V' ? k : 0);
                    int cj = navios[j].coluna + (navios[j].orientacao == 'H' ? k : 0);
                    if (l == lj && c == cj)
                        return 0;
                }
            }
        }
    }

    return 1;
}

void moverNavio(int indice, char direcao) {
    if (!podeMover(navios[indice], direcao)) {
        printf("Movimento invalido!\n");
        return;
    }

    if (direcao == 'W') navios[indice].linha--;
    if (direcao == 'S') navios[indice].linha++;
    if (direcao == 'A') navios[indice].coluna--;
    if (direcao == 'D') navios[indice].coluna++;
}

int main() {
    inicializarTabuleiro();
    posicionarNavios();
    desenharNavios();

    char comando;
    int navioEscolhido;

    while (1) {
        desenharNavios();
        imprimirTabuleiro();

        printf("\nEscolha o navio (0 a 2) ou -1 para sair: ");
        scanf("%d", &navioEscolhido);
        if (navioEscolhido == -1) break;

        if (navioEscolhido < 0 || navioEscolhido >= TOTAL_NAVIOS) {
            printf("Indice invalido!\n");
            continue;
        }

        printf("Digite o comando de movimento (WASD): ");
        scanf(" %c", &comando);

        moverNavio(navioEscolhido, comando);
    }

    return 0;
}
