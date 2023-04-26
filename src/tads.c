#include "../include/tads.h"
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
        printf("CAIXA DE ENTRADA VAZIA\n");
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


// ##########################################################################################
//                            Operações sobre server
// ##########################################################################################

// Inicializa servidor.
void CriaServer(Server *sv) {
    sv->primeiro = (Apontador_caixa)malloc(sizeof(Celula_caixa));
    sv->ultimo = sv->primeiro;
    sv->primeiro->Prox = NULL;
    printf("SERVER CRIADO\n");
}

// Direciona email para caixa certa.
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
    EntregaEmail(&(aux->Item), msg);
}

// Chama a função que cria uma caixa de entrada vazia e adiciona essa caixa ao servidor.
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

// Procura a caixa de entrada no server e chama a função que imprime a mensagem de maior 
// prioridade da caixa e apaga ela.
void ConsultaID(Server *sv, int id){
    Apontador_caixa aux;
    aux = sv->primeiro;
    while (aux->Item.Id != id) {
        if(aux->Prox == NULL) {
            printf("ERRO: CONTA %d NÃO EXISTENTE\n", id);
            return;
        }
        aux = aux->Prox;
    }
    ConsultaEmail(&(aux->Item));
}

// Chama a função que limpa a caixa de entrada e apaga ela em seguida.
void RemoveID(Server *sv, int id){
    Apontador_caixa aux1, aux2;
    aux1 = sv->primeiro;
    while (aux1->Prox != NULL){
        if(aux1->Prox->Item.Id == id){
            LimpaCaixa(&(aux1->Prox->Item));
            aux2 = aux1->Prox->Prox;
            free(aux1->Prox);
            aux1->Prox = aux2;
            if(aux2 == NULL){
                sv->ultimo = aux1;
            }
            printf("OK: CONTA %d REMOVIDA\n", id);
            return;
        }
        aux1 = aux1->Prox;
    }
    printf("ERRO: CONTA %d NÃO EXISTE\n", id);
}
