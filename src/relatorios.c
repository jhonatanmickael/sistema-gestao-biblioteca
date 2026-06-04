#include <time.h>
#include <stdio.h>
#include "relatorios.h"
#include "usuario.h"

void data_log(char evento[]) {

    FILE *arquivo = fopen("../data/historico.log", "a");

    if (arquivo == NULL) {
        printf("Arquivo não encontrado!\n");
        return;
    }

    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);

    if (usuario_logado == NULL) {

        fprintf(arquivo,
                "[%02d/%02d/%04d %02d:%02d:%02d] Sistema | %s\n",

                tm_info->tm_mday,
                tm_info->tm_mon + 1,
                tm_info->tm_year + 1900,
                tm_info->tm_hour,
                tm_info->tm_min,
                tm_info->tm_sec,

                evento);

    } else {

        fprintf(arquivo,
                "[%02d/%02d/%04d %02d:%02d:%02d] %s | %s\n",

                tm_info->tm_mday,
                tm_info->tm_mon + 1,
                tm_info->tm_year + 1900,
                tm_info->tm_hour,
                tm_info->tm_min,
                tm_info->tm_sec,

                usuario_logado->username,
                evento);
    }

    fclose(arquivo);

}