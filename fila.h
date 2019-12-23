#include <stdlib.h>
#include <stdio.h>

//typedef float Itemf;
//typedef char Itemf;
//typedef char* Itemf;
typedef int Itemf;

typedef struct fila {
	int inicio;
	int final;
	int max;
	int total;
	Itemf* itens;
} *Fila;

Fila fila(int max) {
	Fila F = (Fila) malloc(sizeof(struct fila));
	F->inicio = F->final = F->total = 0;
	F->itens = (Itemf*) malloc(sizeof(Itemf) * max);
	F->max = max;
	return F;
}

Itemf iniciof(Fila F) {
	return F->itens[F->inicio];
}

Itemf finalf(Fila F) {
	return F->itens[F->final];
}

int maxf(Fila F) {
	return F->max;
}

int totalf(Fila F) {
	return F->total;
}

int vaziaf(Fila F) {
	return (F->total == 0);
}

int cheiaf(Fila F) {
	return (F->total == F->max);
}

#define avanca(i) (i = (i + 1) % F->max)

void enfileira(Itemf i, Fila F) {
	if (cheiaf(F)) { puts("Fila cheia!"); abort(); }
	F->itens[F->final] = i;
	avanca(F->final);
	F->total++;
}

Itemf desenfileira(Fila F) {
	if (vaziaf(F)) { puts("Fila vazia!"); abort(); }
	Itemf i = F->itens[F->inicio];
	avanca(F->inicio);
	F->total--;
	return i;
}

void destroif(Fila* G) {
	free((*G)->itens);
	free(*G);
	*G = NULL;
}
