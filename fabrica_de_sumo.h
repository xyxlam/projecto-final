#ifndef FABRICA_DE_SUMO_H
#define FABRICA_DE_SUMO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//Constantes
#define MAX_GARRAFAS 6
#define MAX_PILHA 4
#define PRECO_VENDA 400
#define CUSTO_PRODUCAO 110 

//Estrutura para armazenar informações de uma caixa
typedef struct Caixa {
    char sabor[20]; //          // Sabor da caixa            
    int quantidade;             // Quantidade de garrafas na caixa
    int validada;              //  Se a caixa foi validada
    int etiquetada;            // Número da etiqueta (se valida)
}Caixa;

//No para o tapete rolante circular
typedef struct noTapete {
    Caixa caixa;
    struct noTapete *prox;
}noTapete;

typedef struct no {
    Caixa *caixa;
    struct no *prox;
} no;

//Estrutura para o tapete rolante circular
typedef struct {
    noTapete *inicio;
    noTapete *fim;
    int tamanho;        // Número atual de caixas no tapete
}TapeteRolante

//No para a fila de Empilhamento
typedef struct noFila {
    Caixa *caixa;
    struct noFila *prox;
} noFila;

//Estrutura para a fila de Empilhamento
typedef struct {
    noFila *inicio;
    noFila *fim;
    int tamanho;        // Número atual de caixas na fila
} noFila;

// Estrutura para a filha de Empilhamento
typedef struct {
    noFila *frente;
    noFila *tras;
    int tamanho;        // Número atual de caixas na fila
} Fila;

//No para a pilha de caixas
typedef struct noPilha {
    Caixa *caixa;
    struct noPilha *baixo;
}noPilha;

//Estrutura para a pilha
typedef struct {
    noPilha *topo;
    char sabor[20];
    int tamanho;
    int empilhamentos;
} Pilha;

//Funções básicas
TapeteRolante *criarTapete();
Pilha *criarPilha(const char *sabor);

//Operções no tapete rolante
void inserirCaixa(TapeteRolante *tapete, Caixa caixa);
Caixa *validarCaixas(TapeteRolante *tapete, int *prejuizo);
void inverterTapete(TapeteRolante *tapete);
void etiquetarCaixas(TapeteRolante *tapete);

//Funções de validação
void validarCaixa(Caixa *caixa, int *contadorEtiqueta);
void validarTapete(TapeteRolante *tapete, int *contadorEtiqueta);

//Funções de pilha
void empilharCaixa(Pilha *pilha, Caixa *caixa);
void transferirParaPilha(TapeteRolante *tapete, Pilha *pilha, int numSambores);

//Funções de fila
Fila *criarFila();
void encaminharCaixas(TapeteRolante *tapete, Fila *fila, int *contador);

// Funções gerais e de limpeza
void imprimirEstado(TapeteRolante *tapete, Fila *fila, Pilha *pilhas[], int num_pilhas);
void finalizarSimulacao(TapeteRolante *tapete, Fila *fila, Pilha *pilhas[], int num_pilhas);

#endif