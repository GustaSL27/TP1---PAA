#include "labirinto.h"
#define RESET    "\033[0m"
#define VERDE    "\033[1;32m"
#define AMARELO  "\033[1;33m"
#define VERMELHO "\033[1;31m"
#define AZUL     "\033[1;34m"
#define CINZA    "\033[0;90m"
long chamadas = 0;
int nivelMax = 0;

//função que verifica se a posição já foi visitada
int jaVisitou(Posicao caminho[], int qtdvisitado, Posicao p) {
    for (int i = 0; i < qtdvisitado; i++) {
        if (caminho[i].linha == p.linha && caminho[i].coluna == p.coluna)
            return 1;
    }
    return 0;
}

// função recursiva que resolve o labirinto
int resolver(int linhas, int colunas, int qtdChaves, char lab[linhas][colunas], int chaves, Posicao caminho[], int qtdvisitado, Posicao p) {

    if (lab[p.linha][p.coluna] == 'C') chaves++; // coleta a chave

    caminho[qtdvisitado] = p; // armazena a posição atual no caminho
    qtdvisitado++;
    chamadas++;
    if (qtdvisitado > nivelMax) nivelMax = qtdvisitado;

    if (lab[p.linha][p.coluna] == 'X' && chaves == qtdChaves) // verifica se chegou na saída com todas as chaves 
        return qtdvisitado;

    Posicao vizinhos[4] = {
        {p.linha - 1, p.coluna}, {p.linha + 1, p.coluna},
        {p.linha, p.coluna - 1}, {p.linha, p.coluna + 1}
    };

    for (int i = 0; i < 4; i++) {
        Posicao v = vizinhos[i];
        if (v.coluna >= 0 && v.coluna < colunas && v.linha >= 0 && v.linha < linhas && lab[v.linha][v.coluna] != '1' && !jaVisitou(caminho, qtdvisitado, v)) {
            int r = resolver(linhas, colunas, qtdChaves, lab, chaves, caminho, qtdvisitado, v);
            if (r > 0) return r; // se encontrou um caminho, retorna o tamanho do caminho
        }
    }
    return 0;
}
// resolve todas solucoes possiveis do labirinto
int resolverTodas(int linhas, int colunas, int qtdChaves, char lab[linhas][colunas], int chaves, Posicao caminho[], int qtdvisitado, Posicao p) {
    if (lab[p.linha][p.coluna] == 'C') chaves++;

    caminho[qtdvisitado] = p;
    qtdvisitado++;
    chamadas++;
    if (qtdvisitado > nivelMax) nivelMax = qtdvisitado;
    // verifica se chegou na saida com todas as chaves e imprime o resultado encontrado
    if(lab[p.linha][p.coluna] == 'X' && chaves == qtdChaves){
        imprimirCoordenadas(caminho, qtdvisitado);
        imprimirLabirintoComCaminho(linhas, colunas, lab, caminho, qtdvisitado);
        return 1;}

    Posicao vizinhos[4] = {
        {p.linha - 1, p.coluna}, {p.linha + 1, p.coluna},
        {p.linha, p.coluna - 1}, {p.linha, p.coluna + 1}
    };

    int total = 0;
     
    //O laco sempre pecorre os 4 vizinhos, o que torna possivel explorar todas as opcoes permritidas
    for (int i = 0; i < 4; i++) {
        Posicao v = vizinhos[i];
        if (v.coluna >= 0 && v.coluna < colunas && v.linha >= 0 && v.linha < linhas && lab[v.linha][v.coluna] != '1' && !jaVisitou(caminho, qtdvisitado, v)) {
            int r = resolverTodas(linhas, colunas, qtdChaves, lab, chaves, caminho, qtdvisitado, v);
            total += r; // soma os caminhos achados por esse vizinho
        }
    }
    return total;

}

void imprimirCoordenadas(Posicao caminho[], int tam) {
    printf("\nCaminho (%d passos):\n", tam - 1);
    for (int i = 0; i < tam; i++) {
        printf("[%d, %d],", caminho[i].linha, caminho[i].coluna);
    }
    printf("\b \n");
}

void imprimirLabirintoComCaminho(int linhas, int colunas, char lab[linhas][colunas], Posicao caminho[], int tam) {
    char copia[linhas][colunas];
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++){
            copia[i][j] = lab[i][j];
        }
    }

    for (int k = 0; k < tam - 1; k++) {
        char *c = &copia[caminho[k].linha][caminho[k].coluna];
        if (*c != 'A' && *c != 'X' && *c != 'C') {
            int dl = caminho[k + 1].linha  - caminho[k].linha;
            int dc = caminho[k + 1].coluna - caminho[k].coluna;

            if      (dl == -1) *c = '^';
            else if (dl ==  1) *c = 'v';
            else if (dc == -1) *c = '<';
            else               *c = '>';
        }
    }

    printf("\nLabirinto com o caminho:\n\n");
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++){
            switch (copia[i][j]) {
                case '1': printf(CINZA    "# " RESET); break;
                case 'A': printf(AZUL     "A " RESET); break;
                case 'C': printf(AMARELO  "C " RESET); break;
                case 'X': printf(VERMELHO "X " RESET); break;
                case '^': printf(VERDE    "^ " RESET); break;
                case 'v': printf(VERDE    "v " RESET); break;
                case '<': printf(VERDE    "< " RESET); break;
                case '>': printf(VERDE    "> " RESET); break;
                default:  printf(". ");
            }
        }
        printf("\n");
    }
}

void imprimirAnalise(){
    printf("\n--- Modo analise ---\n");
    printf("Chamadas recursivas: %ld\n", chamadas);
    printf("Nivel maximo de recursao: %d\n", nivelMax);
}