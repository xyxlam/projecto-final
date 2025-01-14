#ifndef FABRICA_DE_SUMO_H
#define FABRICA_DE_SUMO_H

#include <stdio.h>
#include <stdlib.h>

//Constantes
#define MAX_GARRAFAS 6
#define MAX_PILHA 4
#define PRECO_VENDA 400
#define CUSTO_PRODUCAO 110

//TAD - Tipo Abstratos de Dados
typedef struct {
   char sabor[20];
   int quantidade_garrafas;
   int validade;
   int etiquetada;
} Caixa;

typedef struct no {
    Caixa* caixa; // Caixa caixa
    struct no* prox;
} no;

typedef struct {
    no *inicio;
    no *fim;
    int tamanho;
} TapeteRolante;

typedef struct {
    Caixa *caixa[MAX_PILHA]; // Caixa
    int topo;
    char sabor[20];
    int empilhamentos;
} Pilha;

typedef struct {
    no *frente;
    no* traseira;
    int tamanho;
} Fila;

//Função para o tapete rolante
TapeteRolante *criarTapete();
void inserirCaixa(TapeteRolante *tapete, Caixa *caixa);
Caixa *validarCaixas(TapeteRolante *tapete, int *prejuizo);
void inverterTapete(TapeteRolante *tapete);
void etiquetarCaixas(TapeteRolante *tapete);

//Função para a fila
Fila *criarFila();
void encaminharCaixas(TapeteRolante *tapete, Fila *fila, int *contador);

//Função para a pilha
Pilha *criarPilha(const char *sabor);
void empilharCaixas(Fila *fila, Pilha *pilha);

//Funções gerais
void imprimirEstado(TapeteRolante *tapete, Fila *fila, Pilha *pilha[], int num_pilhas);
void finalizarSimulacao(TapeteRolante *tapete, Fila *fila, Pilha *pilha[], int num_pilhas);


#endif