#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "usuario.h"

// Menu incial de login/cadastro
void menu_inicial () {
    int select = 0;

    printf("====Gestão de Bibliotecas====\n\n");

    printf("Seja bem-vindo ao Sitema de Gestão de Bibliotecas.\n");

    // Loop para manter o menu ate que uma opção valida seja inserida
    while (1) {
        printf("Selecione a opção desejada:\n\n");
        printf("1. Cadastrar\n2. Login\n-> ");

        // Ler e ja verifica se oque foi inserido é um num inteiro
        if (scanf("%d", &select) != 1) {

            // Limpa o buffer
            while (getchar() != '\n');

            system("clear");
            printf("[!] Digite apenas numeros [!]\nPressione [ENTER] para continuar...");
            getchar();
            system("clear");

            continue; // Volta para o início do menu
        }

        // Verifica se foi inserido uma opção que não seja 1 ou 2
        if (select > 2 || select < 1) {
            // Limpa o buffer   
            while (getchar() != '\n');

            system("clear");
            printf("\n[!] Digite uma opção valida [!]\n\nPressione [ENTER] para continuar...");
            getchar();
            continue; // Volta para o início do menu
        }

        // Limpa o buffer
        while (getchar() != '\n');

        // Direcionamento para a função escolhida pelo usuário
        if (select == 1) {
            system("clear");
            cadastro(); // Chama a tela de cadastro(usuario.c)
        } else if (select == 2) {
            system("clear");
            // login(usuario.c)
            if (login() == 1) {
                menu_sistema(); // Abre o sistema principal da biblioteca
            }
            system("clear");
        }
    }
}

