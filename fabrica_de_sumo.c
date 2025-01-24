#include "fabrica_de_sumo.h"

TapeteRolante *criarTapete() {
    TapeteRolante *tapete = (TapeteRolante *)malloc(sizeof(TapeteRolante));
    tapete->inicio = NULL;
    tapete->fim = NULL;
    tapete->tamanho = 0;
    return tapete;
}

void inserirCaixa(TapeteRolante *tapete, Caixa caixa) {
    no *novo = (no *)malloc(sizeof(no));
    novo->caixa = caixa;
    novo->prox = NULL;

    if (tapete->fim == NULL) {
        tapete->inicio = novo;
    } else {
        tapete->fim->prox = novo;
    }
    tapete->fim = novo;
    tapete->tamanho++;
}

void validarCaixas(TapeteRolante *tapete, int *prejuizo) {
    no *atual = tapete->inicio;
    while (atual != NULL) {
        if (atual->caixa.quantidade < MAX_GARRAFAS) {
            *prejuizo += (MAX_GARRAFAS - atual->caixa.quantidade) * CUSTO_PRODUCAO_LARANJA;
            atual->caixa.validada = 0;
        } else {
            atual->caixa.validada = 1;
        }
        atual = atual->prox;
    }
}

void inverterTapete(TapeteRolante *tapete) {
    no *anterior = NULL;
    no *atual = tapete->inicio;
    no *proximo;

    while (atual != NULL) {
        proximo = atual->prox;
        atual->prox = anterior;
        anterior = atual;
        atual = proximo;
    }
    tapete->fim = tapete->inicio;
    tapete->inicio = anterior;
}

void etiquetarCaixas(TapeteRolante *tapete) {
    no *atual = tapete->inicio;
    while (atual != NULL) {
        if (atual->caixa.validada) {
            atual->caixa.etiquetada = 1;
        }
        atual = atual->prox;
    }
}

Fila *criarFila() {
    Fila *fila = (Fila *)malloc(sizeof(Fila));
    fila->frente = NULL;
    fila->tras = NULL;
    fila->tamanho = 0;
    return fila;
}

void encaminharCaixas(TapeteRolante *tapete, Fila *fila, int *contador) {
    while (tapete->inicio != NULL) {
        no *remover = tapete->inicio;
        tapete->inicio = tapete->inicio->prox;

        if (fila->frente == NULL) {
            fila->frente = remover;
        } else {
            fila->tras->prox = remover;
        }
        fila->tras = remover;
        fila->tamanho++;
        tapete->tamanho--;
        (*contador)++;
    }
    tapete->fim = NULL;
}

Pilha *criarPilha(const char *sabor) {
    Pilha *pilha = (Pilha *)malloc(sizeof(Pilha));
    pilha->topo = NULL;
    strcpy(pilha->sabor, sabor);
    pilha->tamanho = 0;
    pilha->empilhamentos = 0;
    return pilha;
}

void empilharCaixa(Fila *fila, Pilha *pilha) {
    while (fila->tamanho > 0) {
        no *remover = fila->frente;
        fila->frente = fila->frente->prox;

        noPilha *novoNo =(noPilha *)malloc(sizeof(noPilha));
        novoNo->caixa = remover->caixa;
        novoNo->prox = pilha->topo;
        pilha->topo = novoNo;
        pilha->tamanho++;
        pilha->empilhamentos++;

        fila->tamanho--;
        free(remover);
    }
    if (fila->frente == NULL) {
        fila->tras = NULL;
    }
}

//Imprimir o estado atual
void imprimirEstado(TapeteRolante *tapete, Fila *fila, Pilha *pilhas[], int num_pilhas) {
    no *atual = tapete->inicio;
    while (atual != NULL) {
        printf("Caixa: %s | Garrafas: %d | Validada: %d | Etiquetada: %d\n", atual->caixa.sabor, atual->caixa.quantidade, atual->caixa.validada, atual->caixa.etiquetada);
        atual = atual->prox;
    }

    printf("\nEstado das Pilhas:\n");
    for (int i = 0; i < num_pilhas; i++) {
        printf("Pilha %s: %d caixas empilhadas\n", pilhas[i]->sabor, pilhas[i]->empilhamentos);
    }

    printf("\nEstado da Fila:\n");
    atual = fila->frente;
    while (atual != NULL) {
        printf("Caixa: %s | Garrafas: %d\n", atual->caixa.sabor, atual->caixa.quantidade);
        atual = atual->prox;
    }
}

//Finalizar a liberar memória
void finalizarSimulacao(TapeteRolante *tapete, Fila *fila, Pilha *pilhas[], int num_pilhas) {
    no *atual = tapete->inicio;
    while (atual != NULL) {
        no *remover = atual;
        atual = atual->prox;
        free(remover);
    }
    free(tapete);

    atual = fila->frente;
    while (atual != NULL) {
        no *remover = atual;
        atual = atual->prox;
        free(remover);
    }
    free(fila);
    
    for (int i = 0; i < num_pilhas; i++) {
        free(pilhas[i]);
    }
}

//salvar o estado do tapete em um arquivo
void salvarFicheiro(TapeteRolante *tapete, const char *filename) {
    FILE *ficheiro = fopen(filename, "w");
    if (!ficheiro) {
        fprintf(stderr, "Erro ao abrir o arquivo para salvar\n");
        exit(EXIT_FAILURE);
        return;
    }

    no *atual = tapete->inicio;
    if (atual) {
        do {
            fprintf(ficheiro, "`%s` %d %d %d\n", atual->caixa.sabor, atual->caixa.quantidade, atual->caixa.validada, atual->caixa.etiquetada);
            atual = atual->prox;
        } while (atual != tapete->inicio);
    }

    fclose(ficheiro);
    printf("Estado do tapete salvo em '%s'.\n", filename);
}

//carregar o estado do tapete de um arquivo
void carregarFicheiro(TapeteRolante *tapete, const char *filename) {
    FILE *ficheiro = fopen(filename, "r");
    if (!ficheiro) {
        fprintf(stderr, "Erro ao abrir o arquivo para carregar\n");
        exit(EXIT_FAILURE);
        return;
    }

    char sabor[20];
    int quantidade, validada, etiquetada;

    while (fscanf(ficheiro, "%s %d %d %d\n", sabor, &quantidade, &validada, &etiquetada) == 4) {
        Caixa caixa;
        strcpy(caixa.sabor, sabor);
        caixa.quantidade = quantidade;
        caixa.validada = validada;
        caixa.etiquetada = etiquetada;
        inserirCaixa(tapete, caixa);
    }

    fclose(ficheiro);
    printf("Estado do tapete carregado de '%s'.\n", filename);
}

//Fun;áo para validar e etiquetar uma caixa
void validarCaixa(Caixa *caixa, int *contadorEtiqueta) {
    if (!caixa->validada) {
        caixa->validada = 1;
        caixa->etiquetada = (*contadorEtiqueta)++;
    } else {
        printf("A caixa já está validada: Sabor %s, Etiqueta %d/n", caixa->sabor, caixa->etiquetada);
    }
}

// Validar todas as caixas no tapete rolante
void validarTapete(TapeteRolante *tapete, int *contadorEtiqueta) {
    if (tapete->inicio == NULL) {
        printf("O tapete está vazio. Nada a validar.\n");
        return;
    }

    no *atual = tapete->inicio;
    do {
        validarCaixa(&atual->caixa, contadorEtiqueta);
        atual = atual->prox;
    } while (atual != tapete->inicio);
}

// Criar uma nova pilha
Pilha *criarPilha(char *sabor) {
    Pilha *pilha = (Pilha *)malloc(sizeof(Pilha));
    if(!pilha) {
        fprintf(stderr, "Erro ao alocar memória para a pilha\n");
        exit(EXIT_FAILURE);
    }
    pilha->topo = NULL;
    pilha->tamanho = 0;
    strcpy(pilha->sabor, sabor);
    return pilha;
}

// Empilhar uma caixa na pilha correspondente ao sabor
void empilharCaixa(Pilha *pilha, Caixa *caixa) {
    if (strcmp(pilha->sabor, caixa->sabor) != 0) {
        printf("Erro: O sabor da caixa não corresponde ao da pilha.\n");
        return;
}

noPilha *novo = (noPilha *)malloc(sizeof(noPilha));
if(!novo) {
    fprintf(stderr, "Erro ao alocar memória para o nó da pilha\n");
    exit(EXIT_FAILURE);
}

novo->caixa = *caixa;
novo->prox = pilha->topo;
pilha->topo = novo;
pilha->tamanho++;
}

//Transferir caixas validadas do tapete para a pilha correspondente
void transferirParaPilha(TapeteRolante *tapete, Pilha **pilhas, int numSabores) {
    if (tapete->inicio == NULL) {
        printf("O tapete está vazio. Nada para ser transferido.\n");
        return;
    }

    no *atual = tapete->inicio;
    no *anterior = NULL;

    do {
        if(atual->caixa.validada) {
            // Procurar a pilha correspondente ao sabor
            for (int i = 0; i < numSabores; i++) {
                if (strcmp(pilhas[i]->sabor, atual->caixa.sabor) == 0) {
                    empilharCaixa(pilhas[i], &atual->caixa);
                    break;
                }
            }

            // Remover a caixa do tapete
            if (anterior) {
                anterior->prox = atual->prox;
            } else {
                tapete->inicio = atual->prox;
            }

            no *remover = atual;
            atual = atual->prox;

            free(remover);
            tapete->tamanho--;
        } else {
            anterior = atual;
            atual = atual->prox;
        }
    } while (atual != tapete->inicio);
}