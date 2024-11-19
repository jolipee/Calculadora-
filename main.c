#include <stdio.h>
#include <string.h>
#include "expressao.h"

int main() {
    Expressao expr;
    char continuar = 's';

    while (continuar == 's' || continuar == 'S') {
        printf("Digite a expressão em notação pós-fixada: ");
        fgets(expr.posFixa, sizeof(expr.posFixa), stdin);
        expr.posFixa[strcspn(expr.posFixa, "\n")] = '\0'; // Remove o '\n'

        // Calcula e exibe os resultados
        strcpy(expr.inFixa, getFormaInFixa(expr.posFixa));
        expr.Valor = getValor(expr.posFixa);

        printf("Forma Infixa: %s\n", expr.inFixa);
        printf("Valor: %.8f\n", expr.Valor);

        // Pergunta ao usuário se deseja continuar
        printf("Deseja calcular outra expressão? (s/n): ");
        scanf(" %c", &continuar);
        getchar(); // Consumir o '\n' deixado pelo scanf
    }

    printf("Programa encerrado. Obrigado!\n");
    return 0;
}