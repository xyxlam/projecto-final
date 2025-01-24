#ifndef FABRICA_DE_SUMO_H
#define FABRICA_DE_SUMO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Constantes
#define MAX_GARRAFAS 6
#define CUSTO_PRODUCAO_LARANJA 110
#define CUSTO_PRODUCAO_ANANAS 110
#define PRECO_VENDA_LARANJA 400

//Estrutura para armazenar informações de uma caixa
typedef struct Caixa {
    char sabor[20]; //          // Sabor da caixa            
    int quantidade;             // Quantidade de garrafas na caixa
    int validada;              //  Se a caixa foi validada
    int etiquetada;            // Número da etiqueta (se valida)
}Caixa;

typedef struct no {
    Caixa caixa;
    struct no *prox;
} no;

//Estrutura para o tapete rolante circular
typedef struct TapeteRolante {
    no *inicio;
    no *fim;
    int tamanho;        // Número atual de caixas no tapete
}TapeteRolante;

//No para a fila de Empilhamento
typedef struct noPilha {
    Caixa caixa;
    struct noPilha *prox;
} noPilha;

typedef struct pilha{
    noPilha *topo;
    char sabor [20];
    int tamanho;
    int empilhamentos;
}Pilha;

typedef struct Fila {
    no *frente;
    no *tras;
    int *tamanho;
} Fila;

// Prototipagem de funções
TapeteRolante *criarTapete();
void inserirCaixa(TapeteRolante *tapete, Caixa caixa);
void validarCaixas(TapeteRolante *tapete, int *prejuizo);
void inverterTapete(TapeteRolante *tapete);
void etiquetarCaixas(TapeteRolante *tapete);
Fila *criarFila();
void encaminharCaixas(TapeteRolante *tapete, Fila *fila, int *contador);
Pilha *criarPilha(const char *sabor);
void empilharCaixa(Fila *fila, Pilha *pilha);
void imprimirEstado(TapeteRolante *tapete, Fila *fila, Pilha *pilhas[], int num_pilhas);
void finalizarSimulacao(TapeteRolante *tapete, Fila *fila, Pilha *pilhas[], int num_pilhas);
void salvarFicheiro(TapeteRolante *tapete, const char *filename);
void carregarFicheiro(TapeteRolante *tapete, const char *filename);
void validarCaixa(Caixa *caixa, int *contadorEtiqueta);
void validarTapete(TapeteRolante *tapete, int *contadorEtiqueta);
void transferirCaixas(TapeteRolante *tapete, Pilha **pilhas, int numSabores);
void transferirParaPilha(TapeteRolante *tapete, Pilha **pilhas, int numSabores);

#endif