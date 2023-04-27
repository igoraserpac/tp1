#include "../include/server.h"
#include "../include/caixa.h"
#include <stdio.h>
#include <stdlib.h>



// ##########################################################################################
//                            Operações sobre server
// ##########################################################################################

// Inicializa servidor.
void CriaServer(Server *sv) {
    sv->primeiro = (Apontador_caixa)malloc(sizeof(Celula_caixa));
    sv->ultimo = sv->primeiro;
    sv->primeiro->Prox = NULL;
}

// Direciona email para caixa certa.
void EntregaMensagem(Server *sv, Mensagem msg, int id){
    Apontador_caixa aux;
    aux = sv->primeiro->Prox;
    while (aux != NULL && aux->Item.Id != id){
        aux = aux->Prox;
    }
    if(aux == NULL) {
        printf("ERRO: CONTA %d NÃO EXISTENTE\n", id);
        return;
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
            printf("OK: CONTA %d CADASTRADA\n", id);
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
