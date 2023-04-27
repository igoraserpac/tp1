#include "../include/caixa.h"
#include <stdio.h>
#include <stdlib.h>


// ##########################################################################################
//                            Operações sobre caixa de entrada
// ##########################################################################################

// Cria caixa de entrada vazia:
void CriaCaixaVazia(CaixaDeEntrada *cx, int id) {
    cx->primeiro = (Apontador_email)malloc(sizeof(Celula_email));
    cx->ultimo = cx->primeiro;
    cx->primeiro->Prox = NULL;
    cx->Id = id;
}

// Verifica se a caixa esta ou não vazia
int CaixaVazia(CaixaDeEntrada *cx) {
    return (cx->primeiro == cx->ultimo);
}

// Função que entrega email a uma caixa de entrada.
void EntregaEmail(CaixaDeEntrada *cx, Mensagem msg) {
    Apontador_email aux1, aux2;
    aux1 = cx->primeiro;
    while (aux1->Prox != NULL && aux1->Prox->Item.Prioridade >= msg.Prioridade) {
        aux1 = aux1->Prox;
    }
    aux2 = aux1->Prox;
    aux1->Prox = (Apontador_email)malloc(sizeof(Celula_email));
    aux1->Prox->Prox = aux2;
    aux1->Prox->Item = msg;   
    if(aux2 == NULL){
        cx->ultimo = aux1->Prox;
    }   
    printf("OK: MENSAGEM PARA %d ENTREGUE\n", cx->Id);
}

// Imprime a mensagem com maior prioridade da caixa e apaga ela.
void ConsultaEmail(CaixaDeEntrada *cx){
    if(CaixaVazia(cx)){
        printf("CONSULTA %d: CAIXA DE ENTRADA VAZIA\n", cx->Id);
    }else{
        printf("CONSULTA %d: %s\n",cx->Id, cx->primeiro->Prox->Item.Msg);
        Apontador_email aux = cx->primeiro->Prox;
        cx->primeiro->Prox = cx->primeiro->Prox->Prox;
        if(cx->primeiro->Prox == NULL){
            cx->ultimo = cx->primeiro;
        }
        free(aux);
    }
}

// Apaga todas as mensagens da caixa de entrada.
void LimpaCaixa(CaixaDeEntrada *cx){
    Apontador_email aux;
    aux = cx->primeiro->Prox;
    while (aux != NULL){
        cx->primeiro->Prox = cx->primeiro->Prox->Prox;
        free(aux);
        aux = cx->primeiro->Prox;
    }
    free(cx->primeiro);
}
