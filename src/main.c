#include "../include/tads.h"
#include <string.h>

int main(){
    Server sv;
    CriaServer(&sv);
    NovaCaixa(&sv, 5);
    NovaCaixa(&sv, 6);
    NovaCaixa(&sv, 7);
    NovaCaixa(&sv, 8);
    NovaCaixa(&sv, 6);

    Mensagem msg;
    strcpy(msg.Msg, "Olá Bom dia!");
    msg.Prioridade = 8;
    EntregaMensagem(&sv, msg, 5);
    EntregaMensagem(&sv, msg, 6);
    EntregaMensagem(&sv, msg, 7);
    EntregaMensagem(&sv, msg, 8);
    EntregaMensagem(&sv, msg, 5);
    EntregaMensagem(&sv, msg, 5);
    ConsultaID(&sv, 5);
    ConsultaID(&sv, 5);
    ConsultaID(&sv, 5);
    ConsultaID(&sv, 5);
    RemoveID(&sv, 5);
    RemoveID(&sv, 6);
    RemoveID(&sv, 7);
    RemoveID(&sv, 8);
    ConsultaID(&sv, 5);
}