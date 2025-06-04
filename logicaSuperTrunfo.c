#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Desafio Super Trunfo - Países - Nível Aventureiro
// Aluno: Alex Batista Rodrigues
// Matrícula: 201907217894

// Definição da estrutura da carta
typedef struct {
    char estado;
    int codigo;
    char nome[50];
    unsigned long int populacao;
    float area;
    float pib;
    int pontosTuristicos;
    float densidadePopulacional;
    float pibPerCapita;
} Carta;

// Cálculos auxiliares
float calcularDensidadePopulacional(unsigned long int populacao, float area) {
    return populacao / area;
}

float calcularPibPerCapita(float pib, unsigned long int populacao) {
    return pib / populacao;
}

void registrarCarta(Carta *carta) {

    // Estado (A-H)
    do {
        printf("Estado (A-H): ");
        scanf("%c", &carta->estado);
        carta->estado = toupper(carta->estado);
    } while (carta->estado < 'A' || carta->estado > 'H');

    // Código (1-4)
    do {
        printf("Código da cidade (1-4): ");
        scanf("%d", &carta->codigo);
    } while (carta->codigo < 1 || carta->codigo > 4);

    // Nome da cidade
    printf("Nome da cidade: ");
    scanf(" %[^\n]", &carta->nome);

    printf("Digite a população: ");
    scanf("%lu", &carta->populacao);

    printf("Digite a área (km²): ");
    scanf("%f", &carta->area);

    printf("Digite o PIB (milhões): ");
    scanf("%f", &carta->pib);

    printf("Digite o número de pontos turísticos: ");
    scanf("%d", &carta->pontosTuristicos);

    carta->densidadePopulacional = calcularDensidadePopulacional(carta->populacao, carta->area);
    carta->pibPerCapita = calcularPibPerCapita(carta->pib, carta->populacao);
}

// Exibição da carta
void exibirCarta(Carta carta) {
    printf("\n--- CARTA %c%02d: %s ---\n", carta.estado, carta.codigo, carta.nome);
    printf("População: %lu\n", carta.populacao);
    printf("Área: %.2f km²\n", carta.area);
    printf("PIB: R$ %.2f milhões\n", carta.pib);
    printf("Pontos turísticos: %d\n", carta.pontosTuristicos);
    printf("Densidade Populacional: %.2f hab/km²\n", carta.densidadePopulacional);
    printf("PIB per capita: R$ %.2f\n", carta.pibPerCapita);
}

int compararAtributo(Carta c1, Carta c2, int atributo, int *empate) {
    *empate = 0;
    float valor1, valor2;

    switch (atributo) {
        case 1: // População
            valor1 = c1.populacao;
            valor2 = c2.populacao;
            break;
        case 2: // Área
            valor1 = c1.area;
            valor2 = c2.area;
            break;
        case 3: // PIB
            valor1 = c1.pib;
            valor2 = c2.pib;
            break;
        case 4: // Pontos Turísticos
            valor1 = c1.pontosTuristicos;
            valor2 = c2.pontosTuristicos;
            break;
        case 5: // Densidade Populacional (menor vence)
            if (c1.densidadePopulacional == c2.densidadePopulacional) {
                *empate = 1;
                return 0;
            }
            return c1.densidadePopulacional < c2.densidadePopulacional ? 1 : 0;
        case 6: // PIB per Capita
            valor1 = c1.pibPerCapita;
            valor2 = c2.pibPerCapita;
            break;
        default:
            return 0;
    }

    if (valor1 == valor2) {
        *empate = 1;
        return 0;
    }

    return valor1 > valor2 ? 1 : 0;
}

void menuComparacao(Carta c1, Carta c2) {
    int opcao1, opcao2;
    int empate1, empate2;
    int resultado1, resultado2;
    int repetir;

    printf("\n===      MENU DE COMPARAÇÃO       ===\n");
    printf("1. População\n");
    printf("2. Área\n");
    printf("3. PIB\n");
    printf("4. Pontos Turísticos\n");
    printf("5. Densidade Populacional\n");
    printf("6. PIB per Capita\n");
    printf("0. Sair\n");

    printf("\nEscolha o primeiro atributo para comparação: ");
    scanf("%d", &opcao1);

    if (opcao1 < 1 || opcao1 > 6) {
        printf("Opção inválida!\n");
        return;
    }

    printf("\nEscolha o segundo atributo para comparação: ");
    scanf("%d", &opcao2);

    if (opcao2 < 1 || opcao2 > 6) {
        printf("Opção inválida!\n");
        return;
    }

    // Comparação dos atributos
    resultado1 = compararAtributo(c1, c2, opcao1, &empate1);
    resultado2 = compararAtributo(c1, c2, opcao2, &empate2);

    // Exibir resultados
    printf("\n===          RESULTADOS           ===\n");

    // Primeiro atributo
    printf("\nAtributo %d:\n", opcao1);
    if (empate1) {
        printf("Empate neste atributo!\n");
    }
    else {
        printf("Vencedor: Carta %d\n", resultado1 + 1);
    }

    // Segundo atributo
    printf("\nAtributo %d:\n", opcao2);
    if (empate2) {
        printf("Empate neste atributo!\n");
    }
    else {
        printf("Vencedor: Carta %d\n", resultado2 + 1);
    }

    // Resultado combinado
    if (!empate1 && !empate2) {
        if (resultado1 == resultado2) {
            printf("\nCarta %d vence em ambos atributos!\n", resultado1 + 1);
        }
        else {
            printf("\nCada carta vence em um atributo diferente!\n");
        }
    }
    else if (empate1 && empate2) {
        printf("\nEmpate em ambos atributos!\n");
    }
    else if (empate1) {
        printf("\nCarta %d vence no segundo atributo (primeiro empatou)\n", resultado2 + 1);
    }
    else {
        printf("\nCarta %d vence no primeiro atributo (segundo empatou)\n", resultado1 + 1);
    }
}

int main() {
    Carta carta1, carta2;

    printf("\n=== Desafio Super Trunfo - Países ===\n");

    printf("\n===      Cadastro da Carta 1      ===\n");
    registrarCarta(&carta1);

    printf("\n===      Cadastro da Carta 2      ===\n");
    registrarCarta(&carta2);

    exibirCarta(carta1);
    exibirCarta(carta2);

    // Menu de comparação
    menuComparacao(carta1, carta2);

    printf("\n===        Jogo encerrado         ===\n");
    printf("\n===      Obrigado por jogar       ===\n");
    printf("\n\n");

    return 0;
}