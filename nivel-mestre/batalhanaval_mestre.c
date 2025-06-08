#include <stdio.h>

#define TAM 10
#define NAVIO 3
#define TOTAL_NAVIOS 3

typedef struct {
    int linha;
    int coluna;
    char orientacao;
} Navio;

char tabuleiro[TAM][TAM];
Navio navios[TOTAL_NAVIOS];

void inicializarTabuleiro() {
    for (int i = 0; i < TAM; i++)
        for (int j = 0; j < TAM; j++)
            tabuleiro[i][j] = '~';
}

void posicionarNavios() {
    navios[0] = (Navio){2, 4, 'H'};
    navios[1] = (Navio){5, 7, 'V'};
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

void ativarHabilidade(int id) {
    int l = navios[id].linha;
    int c = navios[id].coluna;

    if (navios[id].orientacao == 'H')
        c += 1;  // centro do navio horizontal
    else
        l += 1;  // centro do navio vertical

    switch (id) {
        case 0: // Cruz
            for (int i = 0; i < TAM; i++) tabuleiro[l][i] = '*';
            for (int i = 0; i < TAM; i++) tabuleiro[i][c] = '*';
            break;

        case 1: // Cone em L
            for (int i = 0; i < 3; i++) {
                if (l + i < TAM) tabuleiro[l + i][c] = '*';
                if (c + i < TAM) tabuleiro[l][c + i] = '*';
            }
            break;

        case 2: // Octógono (área 3x3)
            for (int i = -1; i <= 1; i++) {
                for (int j = -1; j <= 1; j++) {
                    int li = l + i;
                    int ci = c + j;
                    if (li >= 0 && li < TAM && ci >= 0 && ci < TAM)
                        tabuleiro[li][ci] = '*';
                }
            }
            break;
    }

    // Redesenhar os navios por cima da habilidade
    for (int i = 0; i < TOTAL_NAVIOS; i++) {
        int li = navios[i].linha;
        int ci = navios[i].coluna;
        for (int j = 0; j < NAVIO; j++) {
            if (navios[i].orientacao == 'H')
                tabuleiro[li][ci + j] = '#';
            else
                tabuleiro[li + j][ci] = '#';
        }
    }
}

int main() {
    posicionarNavios();
    desenharNavios();

    int opcao;

    while (1) {
        desenharNavios();
        imprimirTabuleiro();

        printf("\nEscolha uma opção:\n");
        printf("1 - Ativar habilidade de um navio\n");
        printf("2 - Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        if (opcao == 2) break;

        if (opcao == 1) {
            int id;
            printf("Escolha o navio (0 a 2): ");
            scanf("%d", &id);
            if (id >= 0 && id < TOTAL_NAVIOS) {
                ativarHabilidade(id);
            } else {
                printf("ID invalido.\n");
            }
        }
    }

    return 0;
}
