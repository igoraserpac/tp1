
#ifndef TADS
#define TADS

#include <stdio.h>
#include <stdlib.h>

// Lista encadeada simples com descritor para emails

// Struct para mensagens.
typedef struct {
    short int Prioridade; // Nível de prioridade da mensagem.
    char Msg[1000]; // String que contém a mensagem.
} Mensagem;

// Define um "Apontador" como sendo um ponteiro para uma célula.
typedef struct Celula_email_str *Apontador_email;

// Struct para célula. Contém uma mensagem e um Apontador_email para a próxima célula.
typedef struct Celula_email_str {
    Mensagem Item;
    Apontador_email Prox;
} Celula_email;

// Descritor:
typedef struct {
    int Id;
    Apontador_email primeiro, ultimo;
} CaixaDeEntrada;

// Operações sobre a Lista:

// Cria caixa de entrada vazia:
void CriaCaixaVazia(CaixaDeEntrada *Caixa, int id);
// Verifica se a caixa esta ou não vazia
int CaixaVazia(CaixaDeEntrada *Caixa);

// Função que entrega email a uma caixa de entrada.
void EntregaEmail(CaixaDeEntrada *Caixa, Mensagem msg);

/*
Função que consulta caixa de entrada. 
Caso a caixa esteja vazia, retorna a mensagem "CAIXA DE ENTRADA VAZIA", caso
contrário, imprime a primeira mensagem da caixa de entrada seguindo a ordem 
de prioridade e em seguida apaga ela para que a próxima consulta realizada a 
caixa de entrada imprima a próxima mensagem.
*/
void ConsultaEmail(CaixaDeEntrada *Caixa);


// Lista encadeada simples com descritor para caixas de entrada

typedef struct Celula_caixa_str *Apontador_caixa;

typedef struct Celula_caixa_str {
    CaixaDeEntrada Item;
    Apontador_caixa Prox;
} Celula_caixa;

// Descritor:
typedef struct {
    Apontador_caixa primeiro, ultimo;
} Server;

// Operações sobre a lista

// Inicializa servidor
void CriaServer(Server *sv);

// Direciona email para caixa certa
void EntregaMensagem(Server *sv, Mensagem msg, int id);


void NovaCaixa(Server *sv, int id);


void ConsultaID(Server *sv, int id);




#endif