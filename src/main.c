#include "../include/server.h"
#include <string.h>

int main(int argc, char *argv[]){
    Server sv;
    CriaServer(&sv);
    if(argc < 2){
        printf("ERRO: ARQUIVO DE ENTRADA NÃO ESPECIFICADO\n");
        return 1;
    }
    FILE *file = fopen(argv[1], "r");
    char comando[20], mensagem[1024];
    int id, pri;
    while (!feof(file)){
        fscanf(file, "%s %d", comando, &id);
        if(!strcmp(comando, "CADASTRA")){
            NovaCaixa(&sv, id);
            fscanf(file,"\n");
        }else if(!strcmp(comando, "CONSULTA")){
            ConsultaID(&sv, id);
            fscanf(file,"\n");
        }else if(!strcmp(comando, "REMOVE")){
            RemoveID(&sv, id);
            fscanf(file,"\n");
        }else if(!strcmp(comando, "ENTREGA")){
            fscanf(file, "%d", &pri);
            fgets(mensagem, 1024, file);
            mensagem[strlen(mensagem)-5] = '\0';
            Mensagem msg;
            strcpy(msg.Msg, mensagem);
            msg.Prioridade = pri;
            EntregaMensagem(&sv, msg, id);
        }
    }
    free(sv.primeiro);
}