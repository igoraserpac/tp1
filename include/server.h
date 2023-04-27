
#ifndef SERVER
#define SERVER

#include <stdio.h>
#include <stdlib.h>
#include "../include/caixa.h"

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