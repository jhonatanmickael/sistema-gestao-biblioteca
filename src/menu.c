#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "usuario.h"
#include "menu.h"
#include "livro.h"
#include "emprestimo.h"

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

// Menu principal do sistema
void menu_sistema() {
    int opcao = 0;

    while (1) {
        system("clear");
        printf("====================================\n");
        printf("        SISTEMA DA BIBLIOTECA       \n");
        printf("====================================\n");
        // Exibe o nome de quem logou e o nível de acesso baseado no type
        printf("Usuário: %s | Acesso: %s\n",  
                usuario_logado.name,  
                (usuario_logado.type == 1) ? "Administrador" : "Comum");
        printf("------------------------------------\n");

        // Opções de menu
        printf("1. Listar Livros Disponíveis\n2. Buscar Lívro\n3. Pegar Lívro Emprestado\n4. Devolver Livro\n");

        // Bloqueio de Segurança: Só mostra se for o ROOT/ADMIN
        if (usuario_logado.type == 1) {
            printf("5. [ADM] Cadastrar Novo Livro\n6. [ADM] Listar Todos os Utilizadores\n");
        }

        printf("0. Fazer Logout (Sair)\n");
        printf("------------------------------------\n-> ");

        // Ler e verifica se foi um numero inteiro
        if (scanf("%d", &opcao) != 1) {
            while (getchar() != '\n'); // Limpa buffer
            system("clear");
            printf("[!] Digite apenas números! [!]\nPressione [ENTER]...");
            getchar();
            continue;
        }
        while (getchar() != '\n'); // Limpa o buffer

        // Processamento das opções do menu
        if (opcao == 0) {
            system("clear");
            printf("A encerrar a sessão de %s...\n", usuario_logado.name);
            printf("Pressione [ENTER] para voltar ao menu inicial...");
            getchar();
            break; // Sai do loop e volta pra a tela de login/cadastro
        }
        else if (opcao == 1) {
            listar_livros();
        }
        else if (opcao == 2) {
            buscar_livro();
        }
        else if (opcao == 3) {
            solicitar_emprestimo();
        }
        else if (opcao == 4) {
            devolver_livro();
        }
        else if (opcao == 5 && usuario_logado.type == 1) {
            cadastrar_livro();
        }
        else if (opcao == 6 && usuario_logado.type == 1) {
            system("clear");
            listagem();
        }

        else {
            system("clear");
            printf("[!] Opção Inválida! [!]\nPressione [ENTER] para tentar novamente...");
            getchar();
        }
    }
}
