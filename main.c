#include "stdio.h"
#include "stdlib.h"

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

    printf("\nLabirinto carregado (%dx%d) - Chaves necessarias: %d\n\n", linhas, colunas, qtdChaves);
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            printf("%c ", labirinto[i][j]);
        }
        printf("\n");
    }
}