#include "fabrica_de_sumo.h"
#include <stdio.h>

void exibirMenu() {
    printf("\n=== MENU ===\n");
    printf("1. Inserir caixa no tapete\n");
    printf("2. Validar caixas\n");
    printf("3. Inverter tapete\n");
    printf("4. Etiquetar caixas\n");
    printf("5. Encaminhar caixas\n");
    printf("6. Empilhar caixas\n");
    printf("7. Imprimir estado\n");
    printf("8. Terminar simulacao\n");
    printf("0. Sair\n");
    printf("\nEscolha uma opcao: ");
}

int main() {
    //Criar o tapete rolante
    TapeteRolante *tapete = criarTapete();

    //Criar a fila de encaminhamento
    Fila *fila = criarFila();

    //Criar pilhas para diferentes sabores
    Pilha *pilhalaranja = criarPilha("Laranja");
    Pilha *pilhaAnanas = criarPilha("Ananas");
    Pilha *pilhas[2] = {pilhalaranja, pilhaAnanas};

    int opcao, prejuizo = 0, caixaEncaminhada = 0;
    int continuar = 1; // Flag para continuar no menu

    while (continuar) {
        exibirMenu();
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: {
                Caixa novaCaixa;
                printf("\nDigite o sabor da caixa: ");
                scanf("%s", novaCaixa.sabor);
                printf("Digite a quantidade de garrafas: ");
                scanf("%d", &novaCaixa.quantidade);
                novaCaixa.etiquetada = 0; // Sem etiqueta inicialmente
                novaCaixa.validada = 0;  // Não validado ainda
                inserirCaixa(tapete, novaCaixa);
                printf("Caixa inserida no tapete!\n");
                break;
            }
            case 2:
               validarCaixas(tapete, &prejuizo);
               printf("Caixas validadas!\n");
               break;
            case 3:
                inverterTapete(tapete);
                printf("Tapete invertido!\n");
                break;
            case 4:
            etiquetarCaixas(tapete);
            printf("Caixas etiquetadas!\n");
            break;
            case 5:
                encaminharCaixas(tapete, fila, &caixaEncaminhada);
                printf("Caixas encaminhadas para a fila!\n");
                break;
            case 6: 
                empilharCaixa(fila, pilhalaranja);
                empilharCaixa(fila, pilhaAnanas);
                printf("Caixas empilhadas!\n");
                break;
            case 7:
                imprimirEstado(tapete, fila, pilhas, 2);
                break;
            case 8:
                printf("Finalizar simulacao...\n");
                continuar = 0;// Finalizar o programa
                break;
            case 0:
                printf("Encerrando o programa...\n");
                finalizarSimulacao(tapete, fila, pilhas, 2);
                return 0; //Sair do programa
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }
    }
    
    //Simular a inserção de caixas
    Caixa caixa1 = {"Laranja", 6, 0, 0};
    Caixa caixa2 = {"Ananas", 4, 0, 0};
    Caixa caixa3 = {"Laranja", 6, 0, 0};

    //validar caixas no tapete
    inserirCaixa(tapete, caixa1);
    inserirCaixa(tapete, caixa2);
    inserirCaixa(tapete, caixa3);

    //validar caizas no tapete
    validarCaixas(tapete, &prejuizo);

    // Inverter a ordem do tapete rolante
    inverterTapete(tapete);

    // Etiquetar caixas válidas
    etiquetarCaixas(tapete);

    // Encaminhar caixas do tapete para a fila
    encaminharCaixas(tapete, fila, &caixaEncaminhada);

    // Empilhar caixas da fila nas pilhas correspondentes
    empilharCaixa(fila, pilhalaranja);
    empilharCaixa(fila, pilhaAnanas);

    // Imprimir o estado atual da fábrica
    imprimirEstado(tapete, fila, pilhas, 2);

    // Mostrar prejuízo total
    printf("\nPrejuízo acumulado: %d unidades monetárias\n", prejuizo);

    // Salvar estado do tapete em um arquivo
    salvarFicheiro(tapete, "estado_tapete.txt");

    // Finalizar a simulação e liberar memória
    finalizarSimulacao(tapete, fila, pilhas, 2);

    return 0;

}
