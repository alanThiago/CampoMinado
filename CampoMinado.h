#ifndef CAMPO_MINADO_H
#define CAMPO_MINADO_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BOMBA -1
#define FLAG_BOMBA -2
#define BOMBA_IMPRESSAO -3
#define SEM_BOMBA -4
#define FLAG_SEM_BOMBA -5

#define RED "\x1b[01;91m"
#define GREEN "\x1b[01;92m"
#define BLUE "\x1b[01;94m"
#define MAGENTA "\x1b[01;95m"
#define RESET "\x1b[0m"

#define N 50

void GerarCampo(int n, int dificuldade);
int NumBombas(int row, int col, int n);
void AbrirCampo(int row, int col, int n, int *numAbertos);
void InserirRemoverFlag(int row, int col);
void InserirBombasImpressao(int n);
void ImprimirCampo(int n);
int GetDificuldade();
char GetFlag();
void GetCoordenadas(int *linha, int *coluna, int n);
int GetTamanhoCampo();
void Jogar();

#endif