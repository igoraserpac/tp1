#include <stdio.h>
#include <stdlib.h>

// Lista encadeada simples com descritor para caixas de entrada

// Struct para mensagens.
typedef struct {
    short int Prioridade; // Nível de prioridade da mensagem.
    char *Msg; // String que contém a mensagem.
} Mensagem;

// Define um "Apontador" como sendo um ponteiro para uma célula.
typedef struct Celula_str *Apontador;

// Struct para célula. Contém uma mensagem e um apontador para a próxima célula.
typedef struct Celula_str {
    Mensagem Item;
    Apontador Prox;
} Celula;

// Descritor:
typedef struct {
    int Id;
    Apontador primeiro, ultimo;
} CaixaDeEntrada;

// Operações sobre a Lista:

// Cria caixa de entrada vazia:
void CriaCaixaVazia(CaixaDeEntrada *Caixa) {
    Caixa->primeiro = (Apontador)malloc(sizeof(Celula));
    Caixa->ultimo = Caixa->primeiro;
    Caixa->primeiro->Prox = NULL;
}

// Verifica se a caixa esta ou não vazia
int CaixaVazia(CaixaDeEntrada *Caixa) {
    return (Caixa->primeiro == Caixa->ultimo);
}

void EntregaEmail(CaixaDeEntrada *Caixa, Mensagem msg) {
    Apontador aux1, aux2;
    aux1 = Caixa->primeiro;
    while (aux1->Prox->Item.Prioridade >= msg.Prioridade &&
            aux1->Prox != NULL) {
        aux1 = aux1->Prox;
    }
    aux2 = aux1->Prox;
    aux1->Prox = (Apontador)malloc(sizeof(Celula));
    aux1->Prox->Prox = aux2;
    aux1->Prox->Item = msg;   
    if(aux2 == NULL){
        Caixa->ultimo = aux1->Prox;
    }     
}

void ConsultaEmail(CaixaDeEntrada *Caixa){
    if(CaixaVazia(Caixa)){
        printf("CAIXA DE ENTRADA VAZIA\n");
    }else{
        printf("%s\n", Caixa->primeiro->Prox->Item.Msg);
        Apontador aux = Caixa->primeiro->Prox;
        Caixa->primeiro->Prox = Caixa->primeiro->Prox->Prox;
        free(aux);
    }
}

