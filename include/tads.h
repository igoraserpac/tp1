
#ifndef TADS
#define TADS

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

void CriaCaixaVazia(CaixaDeEntrada *Caixa, int id);

int CaixaVazia(CaixaDeEntrada *Caixa);

void EntregaEmail(CaixaDeEntrada *Caixa, Mensagem msg);

void ConsultaEmail(CaixaDeEntrada *Caixa);

void LimpaCaixa(CaixaDeEntrada *cx);

// Lista encadeada simples com descritor para caixas de entrada

// Define um "Apontador" como sendo um ponteiro para uma célula.
typedef struct Celula_caixa_t *Apontador_caixa;

// Struct para célula. Contém uma caixa de entrada e um Apontador_caixa para a próxima célula.
typedef struct Celula_caixa_t {
    CaixaDeEntrada Item;
    Apontador_caixa Prox;
} Celula_caixa;

// Descritor:
typedef struct {
    Apontador_caixa primeiro, ultimo;
} Server;

// Operações sobre o server:

void CriaServer(Server *sv);

void EntregaMensagem(Server *sv, Mensagem msg, int id);

void NovaCaixa(Server *sv, int id);

void ConsultaID(Server *sv, int id);

void RemoveID(Server *sv, int id);


#endif