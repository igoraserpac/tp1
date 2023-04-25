#include "../include/tads.h"
#include <stdio.h>
#include <stdlib.h>

// // Lista encadeada simples com descritor para emails

// // Struct para mensagens.
// typedef struct {
//     short int Prioridade; // Nível de prioridade da mensagem.
//     char Msg[1000]; // String que contém a mensagem.
// } Mensagem;

// // Define um "Apontador" como sendo um ponteiro para uma célula.
// typedef struct Celula_email_str *Apontador_email;

// // Struct para célula. Contém uma mensagem e um Apontador_email para a próxima célula.
// typedef struct Celula_email_str {
//     Mensagem Item;
//     Apontador_email Prox;
// } Celula_email;

// // Descritor:
// typedef struct {
//     int Id;
//     Apontador_email primeiro, ultimo;
// } CaixaDeEntrada;

// Operações sobre a Lista:

// Cria caixa de entrada vazia:
void CriaCaixaVazia(CaixaDeEntrada *Caixa, int id) {
    Caixa->primeiro = (Apontador_email)malloc(sizeof(Celula_email));
    Caixa->ultimo = Caixa->primeiro;
    Caixa->primeiro->Prox = NULL;
    Caixa->Id = id;
}

// Verifica se a caixa esta ou não vazia
int CaixaVazia(CaixaDeEntrada *Caixa) {
    return (Caixa->primeiro == Caixa->ultimo);
}

// Função que entrega email a uma caixa de entrada.
void EntregaEmail(CaixaDeEntrada *Caixa, Mensagem msg) {
    Apontador_email aux1, aux2;
    aux1 = Caixa->primeiro;
    printf("%d\n", Caixa->Id);
    while (aux1->Prox != NULL && aux1->Prox->Item.Prioridade >= msg.Prioridade) {
        printf("50\n");
        aux1 = aux1->Prox;
    }
    aux2 = aux1->Prox;
    aux1->Prox = (Apontador_email)malloc(sizeof(Celula_email));
    aux1->Prox->Prox = aux2;
    aux1->Prox->Item = msg;   
    if(aux2 == NULL){
        Caixa->ultimo = aux1->Prox;
    }     
}


/*
Função que consulta caixa de entrada. 
Caso a caixa esteja vazia, retorna a mensagem "CAIXA DE ENTRADA VAZIA", caso
contrário, imprime a primeira mensagem da caixa de entrada seguindo a ordem 
de prioridade e em seguida apaga ela para que a próxima consulta realizada a 
caixa de entrada imprima a próxima mensagem.
*/
void ConsultaEmail(CaixaDeEntrada *Caixa){
    if(CaixaVazia(Caixa)){
        printf("CAIXA DE ENTRADA VAZIA\n");
    }else{
        printf("CONSULTA %d: %s\n",Caixa->Id, Caixa->primeiro->Prox->Item.Msg);
        Apontador_email aux = Caixa->primeiro->Prox;
        Caixa->primeiro->Prox = Caixa->primeiro->Prox->Prox;
        free(aux);
    }
}


// Lista encadeada simples com descritor para caixas de entrada

// typedef struct Celula_caixa_str *Apontador_caixa;

// typedef struct Celula_caixa_str {
//     CaixaDeEntrada Item;
//     Apontador_caixa Prox;
// } Celula_caixa;

// // Descritor:
// typedef struct {
//     Apontador_caixa primeiro, ultimo;
// } Server;

// Operações sobre a lista

// Inicializa servidor
void CriaServer(Server *sv) {
    sv->primeiro = (Apontador_caixa)malloc(sizeof(Celula_caixa));
    sv->ultimo = sv->primeiro;
    sv->primeiro->Prox = NULL;
    printf("SERVER CRIADO\n");
}

// Direciona email para caixa certa
void EntregaMensagem(Server *sv, Mensagem msg, int id){
    Apontador_caixa aux;
    aux = sv->primeiro;
    while (aux->Item.Id != id) {
        if(aux == NULL) {
            printf("CONTA %d NÃO EXISTENTE\n", id);
            return;
        }
        aux = aux->Prox;
    }
    printf("%d\n%s\n", aux->Item.Id, msg.Msg);
    EntregaEmail(&(aux->Item), msg);
}

void NovaCaixa(Server *sv, int id) {
    CaixaDeEntrada cx;
    Apontador_caixa aux;
    aux = sv->primeiro;
    while (aux->Item.Id != id) {
        if(aux->Prox == NULL) {
            CriaCaixaVazia(&cx, id);
            sv->ultimo->Prox = (Apontador_caixa)malloc(sizeof(Celula_caixa));
            sv->ultimo = sv->ultimo->Prox;
            sv->ultimo->Item = cx;
            sv->ultimo->Prox = NULL;
            printf("OK: CONTA %d CADASTRADA!\n", id);
            return;
        }
        aux = aux->Prox;
    }
    printf("ERRO: CONTA %d JÁ EXISTENTE\n", id);
}


void ConsultaID(Server *sv, int id){
    Apontador_caixa aux;
    aux = sv->primeiro;
    while (aux->Item.Id != id) {
        if(aux == NULL) {
            printf("ERRO: CONTA %d NÃO EXISTENTE\n", id);
            return;
        }
        aux = aux->Prox;
    }
    ConsultaEmail(&(aux->Item));
}


