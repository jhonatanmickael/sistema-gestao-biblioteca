#include <stdio.h>
#include <stdlib.h>
#include "menu.h"

int main() {
    int i=1;
    while(i==1){

        int opt = menu_login();
        if(opt == 1) {
            system("clear");
            //FUNÇÂO DE ENTRAR NA CONTA AQUI
            i=0;
        }
        else if(opt == 2){
            system("clear");
            //FUNÇÇÂO DE CADASTRAS USUÁRIO AQUI
            i=0;
        }
        else if(opt == 3) {
            system("clear");
            printf("Erro de digitação, tente novamente.");
        }
        else{
            system("clear");
            printf("[!] Erro: Digite apenas os números das opções.\n");
        }
    }

    return 0;
}
