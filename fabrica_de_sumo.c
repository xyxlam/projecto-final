#include "fabrica_de_sumo.h"

//Função para criar um tapete rolante
TapeteRolante *criarTapete() {
    TapeteRolante *tapete = (TapeteRolante *)malloc(sizeof(TapeteRolante));
    tapete->inicio = NULL;
    tapete->fim = NULL;
    tapete->tamanho = 0;
    return tapete;
}

// Função para inserir uma caixa no tapete
void inserirCaixa(TapeteRolante *tapete, Caixa *caixa) {
    no *novo = (no *)malloc(sizeof(no));
    novo->caixa = caixa;
    novo->prox = NULL;

    if(tapete->fim == NULL) {
        tapete->inicio = novo;
    } else {
        tapete->fim->prox = novo;
    }
    tapete->fim = novo;
    tapete->tamanho++;
}

// Função para validar caixas
Caixa *validarCaixa(TapeteRolante *tapete, int *prejuizo) {
    no *atual = tapete->inicio;
    while(atual != NULL) {
        if(atual->caixa->quantidade_garrafas < MAX_GARRAFAS) {
            *prejuizo += (MAX_GARRAFAS - atual->caixa->quantidade_garrafas) * CUSTO_PRODUCAO;
            atual->caixa->validade = 0;
        } else {
            atual->caixa->validade =1;
        }
        atual = atual->caixa->validade;
    }
    return  NULL;
}

//Função para inverter o tapete rolante
void inverterTapete(TapeteRolante *tapete) {
    no *anterior = NULL;
    no *atual = tapete->inicio;
    no *proximo;

    while (atual != NULL) {
        proximo = atual->prox;
        atual->prox = anterior;


    }
}