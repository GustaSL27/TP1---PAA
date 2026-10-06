#ifndef LABIRINTO_H
#define LABIRINTO_H

#include "stdio.h"
#include "stdlib.h"

typedef struct {
    int linha;
    int coluna;
} Posicao;

int jaVisitou(Posicao caminho[], int qtdvisitado, Posicao p);
int resolver(int linhas, int colunas, int qtdChaves, char lab[linhas][colunas], int chaves, Posicao caminho[], int qtdvisitado, Posicao p);
int resolverTodas(int linhas, int colunas, int qtdChaves, char lab[linhas][colunas], int chaves, Posicao caminho[], int qtdvisitado, Posicao p);
void imprimirCoordenadas(Posicao caminho[], int tam);
void imprimirLabirintoComCaminho(int linhas, int colunas, char lab[linhas][colunas], Posicao caminho[], int tam);

#endif