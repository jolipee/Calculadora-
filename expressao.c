#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "expressao.h"

// Estrutura de pilha para números e strings
typedef struct {
    float numeros[512];
    int topoNum;

    char strings[512][512];
    int topoStr;
} Pilha;

void pushNum(Pilha *p, float valor) {
    p->numeros[++(p->topoNum)] = valor;
}

float popNum(Pilha *p) {
    return p->numeros[(p->topoNum)--];
}

void pushStr(Pilha *p, const char *str) {
    strcpy(p->strings[++(p->topoStr)], str);
}

char *popStr(Pilha *p) {
    return p->strings[(p->topoStr)--];
}

float calculaOperacao(float op1, float op2, char operador) {
    switch (operador) {
        case '+': return op1 + op2;
        case '-': return op1 - op2;
        case '*': return op1 * op2;
        case '/': return op1 / op2;
        case '^': return pow(op1, op2);
        default: return 0;
    }
}

float calculaFuncao(float operando, const char *funcao) {
    if (strcmp(funcao, "sen") == 0) return sin(operando * M_PI / 180);
    if (strcmp(funcao, "cos") == 0) return cos(operando * M_PI / 180);
    if (strcmp(funcao, "tg") == 0) return tan(operando * M_PI / 180);
    if (strcmp(funcao, "log") == 0) return log10(operando);
    if (strcmp(funcao, "raiz") == 0) return sqrt(operando);
    return 0;
}

char *getFormaInFixa(char *Str) {
    static char resultado[512];
    Pilha pilha = {{0}, -1, {{0}}, -1};
    char token[64];
    char temp[512];
    strcpy(temp, Str);

    char *tok = strtok(temp, " ");
    while (tok != NULL) {
        if (isdigit(tok[0]) || (tok[0] == '-' && isdigit(tok[1]))) {
            pushStr(&pilha, tok);
        } else if (strlen(tok) == 1) { // Operadores binários
            char op2[512], op1[512], expr[512];
            strcpy(op2, popStr(&pilha));
            strcpy(op1, popStr(&pilha));
            sprintf(expr, "(%s %s %s)", op1, tok, op2);
            pushStr(&pilha, expr);
        } else { // Funções unárias
            char op[512], expr[512];
            strcpy(op, popStr(&pilha));
            sprintf(expr, "%s(%s)", tok, op);
            pushStr(&pilha, expr);
        }
        tok = strtok(NULL, " ");
    }
    strcpy(resultado, popStr(&pilha));
    return resultado;
}

float getValor(char *Str) {
    Pilha pilha = {{0}, -1};
    char temp[512];
    strcpy(temp, Str);

    char *tok = strtok(temp, " ");
    while (tok != NULL) {
        if (isdigit(tok[0]) || (tok[0] == '-' && isdigit(tok[1]))) {
            pushNum(&pilha, atof(tok));
        } else if (strlen(tok) == 1) { // Operadores binários
            float op2 = popNum(&pilha);
            float op1 = popNum(&pilha);
            pushNum(&pilha, calculaOperacao(op1, op2, tok[0]));
        } else { // Funções unárias
            float op = popNum(&pilha);
            pushNum(&pilha, calculaFuncao(op, tok));
        }
        tok = strtok(NULL, " ");
    }
    return popNum(&pilha);
}