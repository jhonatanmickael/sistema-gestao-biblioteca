#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
#include "usuario.h"


int main() {
    int i=1;

    while(i==1){
        system("clear");
        int opt = menu_login();

        switch(opt){
            case 1:

                if(login()==1) {
                    printf("\nPressione ENTER para entrar no sistema...");
                    setbuf(stdin, NULL);
                    getchar();
                    i=0;
                } else {
                    printf("\nPressione ENTER para voltar ao menu...");
                }
                break;

            case 2:

                int i2 = 1;
                while(i2 == 1) {
                    system("clear");

                    if(cadastro() == 0) {
                        printf("----- Usuário cadastrado com sucesso! -----\nPressione ENTER para voltar");
                        setbuf(stdin, NULL);
                        getchar(); 
                        i2 = 0;  
                    }
                    else {
                        printf("[!] Erro: Usuário não cadastrado, tente novamente!\n");
                        setbuf(stdin, NULL);
                        getchar();
                        i2 = 0;
                    }
                }

                break;
            default:
                system("clear");
                printf("[!] Erro: Digite apenas os números das opções.\n");
                printf("Pressione ENTER para continuar...");
                getchar(); 

        }

    }

    return 0;
}
