#ifndef CAIXA
#define CAIXA

#include <stdio.h>
#include <stdlib.h>

// Lista encadeada simples com descritor para caixas de entrada

// Struct para mensagens.
typedef struct {
    short int Prioridade; // Nível de prioridade da mensagem.
    char Msg[1024]; // String que contém a mensagem.
} Mensagem;

// Define um "Apontador" como sendo um ponteiro para uma célula.
typedef struct Celula_email_t *Apontador_email;

// Struct para célula. Contém uma mensagem e um Apontador_email para a próxima célula.
typedef struct Celula_email_t {
    Mensagem Item;
    Apontador_email Prox;
} Celula_email;

// Descritor:
typedef struct {
    int Id;
    Apontador_email primeiro, ultimo;
} CaixaDeEntrada;

// Operações sobre a caixa de entrada:

void CriaCaixaVazia(CaixaDeEntrada *cx, int id);

int CaixaVazia(CaixaDeEntrada *cx);

void EntregaEmail(CaixaDeEntrada *cx, Mensagem msg);

void ConsultaEmail(CaixaDeEntrada *cx);

void LimpaCaixa(CaixaDeEntrada *cx);

#endif