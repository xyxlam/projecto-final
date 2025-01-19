#include "fabrica_de_sumo.h"

int main() {
    // Variaveis principais
    TapeteRolante *tapete = criarTapete();
    int contadorEtiqueta = 1;

    // Criar pilhas para sabores específicos
    int numSabores = 3;
    Pilha *pilha[3];
    pilha[0] = criarPilha("Laranja");
    pilha[1] = criarPilha("Maçã");
    pilha[2] = criarPilha("Uva");

    int opcao;

    do {
        printf("\nFÁBRICA DE SUMO - MENU\n");
        printf("1. Inserir caixa no tapete\n");
        printf("2. Validar caixas no tapete\n");
        printf("3. Inverter o sentido do tapete\n");
        printf("4. Transferir caixas validadas para as pilhas\n");
        printf("5. Imprimir estado do tapete\n");
        printf("6. Salvar estado do arquivo\n");
        printf("7. Carregar estado do arquivo\n");
        printf("8. Finalizar Simulação\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: {
                Caixa *novaCaixa;
                printf("Digite o sabor da caixa: ");
                scanf("%s", novaCaixa->sabor);
                printf("Digite a quantidade de garrafas: ");
                scanf("%d", &novaCaixa->quantidade);
                novaCaixa->validada = false;
                inserirCaixa(tapete, novaCaixa);
                break;
            }
            case 2:
                validarTapete(tapete, &contadorEtiqueta);
                break;
            case 3:
                inverterTapete(tapete);
                break;
            case 4:
                transferirParaPilha(tapete, pilhas, numSabores);
                break;
            case 5:
                imprimirTapete(tapete);
                break;
            case 6: {
                char filename[50];
                printf("Digite o nome do arquivo para salvar: ");
                scanf("%s", filename);
                break;
            }
            case 7: {
                char filename[50];
                printf("Digite o nome do arquivo para carregar: ");
                scanf("%s", filename);
                carregarFicheiro(tapete, filename);
                break;
            }
            case 0:
                printf("Encerrando o programa...\n");
                break;
            default:
                printf("Opção inválida!\n");
                break;

        }
    } while (opcao != 0);

    return 0;
}