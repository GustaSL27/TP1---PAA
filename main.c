#include "LABIRINTO/labirinto.h"

int main(){
    int qtdChaves;
    int linhas, colunas;
    char analise;

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
    printf("====================\n");
    
    
    // opcoes de escolha
    printf("\nEscolha o modo:\n");
    printf("1 - Encontrar um caminho\n");
    printf("2 - Encontrar um caminho em globo\n");
    printf("3 - Opcao Extra: Encontrar todos os caminhos possiveis\n");
    
    

    char escolha;
    scanf(" %c", &escolha);
    
    printf("Ativar modo analise? (s/n): ");
    scanf(" %c", &analise);

    Posicao atual = {-1, -1};
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            if (labirinto[i][j] == 'A') {
                atual.linha = i;
                atual.coluna = j;
            }
        }
    }

    Posicao caminho[linhas * colunas];



    if (escolha == '1') {
        int tam = resolver(linhas, colunas, qtdChaves, labirinto, 0, caminho, 0, atual);
        if (tam > 0) {
            imprimirCoordenadas(caminho, tam);
            imprimirLabirintoComCaminho(linhas, colunas, labirinto, caminho, tam);
        }
        else {
            printf("Nao ha um caminho possivel para a entrada de dados fornecida\n");
        }
    }

    else if (escolha == '2') {
        int tam = resolverGlobo(linhas, colunas, qtdChaves, labirinto, 0, caminho, 0, atual);
        if (tam > 0) {
            imprimirCoordenadas(caminho, tam);
            imprimirLabirintoComCaminho(linhas, colunas, labirinto, caminho, tam);
        } else {
            printf("Nao ha um caminho possivel para a entrada de dados fornecida\n");
        }
    }

    else if (escolha == '3') {
        int total = resolverTodas(linhas, colunas, qtdChaves, labirinto, 0, caminho, 0, atual);
            
        if (total > 0) {
            printf("\nTotal de caminhos encontrados: %d\n", total);
        } else {
            printf("Nao ha um caminho possivel para a entrada de dados fornecida\n");
        }
    }

    else printf("Opcao invalida");
    if (analise == 's' || analise == 'S') imprimirAnalise();
}
