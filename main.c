#include "stdio.h"
#include "stdlib.h"

typedef struct {
    int linha;
    int coluna;
} Posicao;

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

    for (int k = 0; k < tam; k++) {
        char *c = &copia[caminho[k].linha][caminho[k].coluna];
        if (*c != 'S' && *c != 'X' && *c != 'C')
            *c = '*';
    }

    printf("\nLabirinto com o caminho:\n\n");
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++){
            printf("%c ", copia[i][j]);
        }
        printf("\n");
    }
}

int main(){
    int qtdChaves;
    int linhas, colunas;

    char caminho_ent[255];
    FILE* arquivo;

    printf("Digite o caminho do arquivo de ENTRADA: ");
    scanf(" %255[^\n]", caminho_ent);

    //le o arquivo de texto //
    arquivo = fopen(caminho_ent,"r"); // Colocar o endereço do arquivo a ser lido //
    if (arquivo==NULL){
        printf("Erro na abertura do arquivo de entrada\n");
        system("pause");
        exit(1);
    }
    
    fscanf(arquivo, "%d %d", &linhas, &colunas); // LE O NUMERO DE LINHAS E COLUNAS //
    fscanf(arquivo, "%d", &qtdChaves); // LE A QUANTIDADE DE CHAVES //
    char labirinto[linhas][colunas];
    
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            fscanf(arquivo, " %c", &labirinto[i][j]);
        }
    }

    fclose(arquivo);

    // Verificação da leitura //
    printf("\nLabirinto carregado (%dx%d) - Chaves necessarias: %d\n\n", linhas, colunas, qtdChaves);
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            printf("%c ", labirinto[i][j]);
        }
        printf("\n");
    }

    Posicao atual = {-1, -1};
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            if (labirinto[i][j] == 'A') {
                atual.linha = i;
                atual.coluna = j;
            }
        }
    }

    Posicao caminho[linhas * colunas]; // array para armazenar o caminho encontrado
    int tam = resolver(linhas, colunas, qtdChaves, labirinto, 0, caminho, 0, atual);

    if (tam > 0) {
        imprimirCoordenadas(caminho, tam);
        imprimirLabirintoComCaminho(linhas, colunas, labirinto, caminho, tam);
    } else {
        printf("“Não há um caminho possível para a entrada de dados fornecida“\n");
    }

}
