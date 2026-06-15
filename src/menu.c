#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "usuario.h"
#include "menu.h"
#include "livro.h"
#include "emprestimo.h"
    
// tela de cadastro e entrada
void menu_inicial () {
    int select = 0;
    while (1) {
        system("clear");
        // grande printf da tela e cadastro
        printf("====================================================\n");
        printf("              SISTEMA DE BIBLIOTECA                 \n");
        printf("====================================================\n");
        printf("Seja bem-vindo ao Sitema de Gestão de Bibliotecas.\n");
        printf("----------------------------------------------------\n");
        printf("1. Cadastrar\n2. Login\n");
        printf("----------------------------------------------------\n-> ");

        // le e ja verifica se oque foi inserido é um num inteiro
        if (scanf("%d", &select) != 1) {
            while (getchar() != '\n'); // limpa o buffer
            system("clear");
            printf("[!] Digite apenas numeros [!]\nPressione [ENTER] para continuar...");
            getchar();
            system("clear");
            continue; // volta para o inicio do menu
        }

        // verifica se foi inserido uma opção que não seja 1 ou 2
        if (select > 2 || select < 1) {
            while (getchar() != '\n'); // limpa o buffer
            system("clear");
            printf("\n[!] Digite uma opção valida [!]\n\nPressione [ENTER] para continuar...");
            getchar();
            continue; // volta para o inicio do menu
        }

        while (getchar() != '\n'); // limpa o buffer

        // se for 1 chama a tela de cadastro 
        if (select == 1) {
            system("clear");
            cadastro();
        // se for 2 chama a tela de login
        } else if (select == 2) {
            system("clear");
            // se o login der certo ja abre o menu do sistema
            if (login() == 1) {
                menu_sistema();
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
    
        // grande printf pra mostrar todo o menu
        printf("============================================\n");
        printf("          SISTEMA DE BIBLIOTECA             \n");
        printf("============================================\n");
        printf("Usuário conectado: %s\n", usuario_logado->name);
        printf("--------------------------------------------\n");
        printf("1. Livros\n");
        printf("2. Emprestimos\n");
        // somente adms tem acesso a opcao abaixo
        if (usuario_logado->type == 1) {
            printf("3. [ADM] Gerenciar Livros\n");
            printf("4. [ADM] Gerenciar Usuários\n");
            printf("5. [ADM] Gerenciar Logs\n");
        }
        printf("0. Fazer Logout (Sair)\n");
        printf("--------------------------------------------\n");
        printf("-> ");

        // le uma entrada e ja verifica se é um numero inteiro
        if (scanf("%d", &opcao) != 1) {
            while (getchar() != '\n');
            system("clear");
            printf("[!] Entrada inválida! Digite apenas números. [!]\n");
            printf("\nPressione [ENTER] para tentar novamente...");
            getchar();
            continue;
        }
        while (getchar() != '\n'); // limpa o buffer

        // volta pra o menu inicial se a entrada for 0
        if (opcao == 0) {
            system("clear");
            printf("A encerrar a sessão de %s...\n", usuario_logado->name);
            printf("Pressione [ENTER] para voltar ao menu inicial...");
            getchar();
            break; 
        }
        // chama o submenu de livros se a entrada for 1
        else if (opcao == 1) {
            submenu_livros();
        }
        // chama o submenu de emprestimos se a entrada for 2
        else if (opcao == 2) {
            submenu_emprestimos();
        }
        // chama o submenu usuarios para adm se a entrada for 3
        else if (opcao == 3 && usuario_logado->type == 1) {
            menu_livros_adm();
        }
        // chama a submenu de usuarios se a entrada for 4
        else if (opcao == 4 && usuario_logado->type == 1) {
            system("clear");
            submenu_usuarios();
        }
        // chama a listagem de logs se a entrada for 5
        else if (opcao == 5 && usuario_logado->type == 1) {
            menu_logs();
        }
        // tratamento de erro para entradas invalidas
        else {
            system("clear");
            printf("[!] Opção Inválida! [!]\nPressione [ENTER] para tentar novamente...");
            getchar();
        }
    }
}

int menu_logs() {
    FILE *arquivo = fopen("../data/historico.log", "r");

    if (arquivo == NULL) {
        printf("Arquivo não localizado!");
        return 0;
    }

    char linha[200];

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        printf("%s", linha);
    }

    fclose(arquivo);

    printf("Pressione [ENTER] para Voltar...");
    getchar();
    return 1;
}

// menu de livros, opção 1 do menu principal
void submenu_livros() {
    int opcao = 0;

    // grande printf da tela de menu de livros
    while (1) {
        system("clear");
        printf("=======================================\n");
        printf("                LIVROS                 \n");
        printf("=======================================\n");
        printf("1. Listar Livros Disponíveis\n");
        printf("2. Buscar Livro por Título\n");
        printf("0. Voltar ao Menu Principal\n");
        printf("---------------------------------------\n");
        printf("-> ");

        // le uma entrada e ja verifica se é um numero inteiro
        if (scanf("%d", &opcao) != 1) {
            while (getchar() != '\n'); // limpa o buffer
            system("clear");
            printf("[!] Entrada inválida! Digite apenas números. [!]\n");
            printf("\nPressione [ENTER] para tentar novamente...");
            getchar();
            continue;
        }
        while (getchar() != '\n'); // limpa o buffer

        // volta pro menu principal se inserir 0
        if (opcao == 0) {
            break; 
        }
        // lista os livros se inserir 1
        else if (opcao == 1) {
            listar_livros(); 
        }
        // abre a tela de buscar livro se inserir 2
        else if (opcao == 2) {
            buscar_livro(); 
        }
        // tratamento de erro caso insira uma opção invalida
        else {
            system("clear");
            printf("[!] Opção Inválida! [!]\nPressione [ENTER] para tentar novamente...");
            getchar();
        }
    }
}

// menu de emprestimo, opção 2 do menu principal
void submenu_emprestimos() { 
    int opcao = 0;

    // grande printf da tela de emprestimos
    while (1) {
        system("clear");
        printf("=======================================\n");
        printf("          SISTEMA DE BIBLIOTECA        \n");
        printf("          SUBMENU: EMPRÉSTIMOS         \n");
        printf("=======================================\n");
        printf("1. Pegar Livro Emprestado\n");
        printf("2. Devolver um Livro\n");
        printf("3. Meus Empréstimos Pendentes\n");
        printf("0. Voltar ao Menu Principal\n");
        printf("---------------------------------------\n");
        printf("-> ");

        // coleta a opção inserida e ja verifica se foi inserido um num inteiro
        if (scanf("%d", &opcao) != 1) {
            while (getchar() != '\n'); 
            system("clear");
            printf("[!] Entrada inválida! Digite apenas números. [!]\n");
            printf("\nPressione [ENTER] para tentar novamente...");
            getchar();
            continue;
        }
        while (getchar() != '\n'); // limpa o buffer

        // voltar pro menu principal se for digitar 0
        if (opcao == 0) {
            break; 
        }
        // vai pra tela de pegar emprestimo se digitar 1
        else if (opcao == 1) {
            solicitar_emprestimo(); 
        }
        // vai pra tela de devolver emprestimo se digitar 2
        else if (opcao == 2) {
            devolver_livro(); 
        }
        // lista os emprestimos da conta se digitar 3
        else if (opcao == 3) {
            listar_emprestimos();
        }
        // mensagem de tratamento de erro caso inseriu uma opção invalida
        else {
            system("clear");
            printf("[!] Opção Inválida! [!]\nPressione [ENTER] para tentar novamente...");
            getchar();
        }
    }
}

// menu de gestão de usuarios, opção 4 do menu principal
void submenu_usuarios() {
    int opcao;

    do {
        // grande printf so submenu de usuarios
        system("clear");
        printf("======================================\n");
        printf("       SISTEMA DE BIBLIOTECA        \n");
        printf("      SUBMENU: GESTÃO DE USUÁRIOS   \n");
        printf("======================================\n");
        printf("1. Cadastrar Novo Usuário\n");
        printf("2. Listar Todos os Usuários\n");
        printf("3. Buscar Usuário\n");
        printf("4. Alterar Privilegio/Senha\n");
        printf("5. Remover Usuário\n");
        printf("0. Voltar ao Menu Principal\n");
        printf("======================================\n");
        printf("-> ");

        // Le e ja verifica se a entrada é valida
        if (scanf("%d", &opcao) != 1) {
            while (getchar() != '\n'); // limpa o buffer
        } else {
            while (getchar() != '\n'); // limpa o buffer
        }

        // processamento da opção escolhida
        switch (opcao) {
            // opção 1 em desenvolvimento
            case 1:
                system("clear");
                printf("\n[INFO] Opcao 'Cadastrar Novo Operador' em desenvolvimento...\n");
                printf("\nPressione [ENTER] para voltar...");
                getchar();
                break;
            // lista todos os usuarios
            case 2:
                listagem(); 
                break;
            // opção 2 em desenvolvimento
            case 3:
                system("clear");
                printf("\n[INFO] Opcao 'Buscar Operador por Login' em desenvolvimento...\n");
                printf("\nPressione [ENTER] para voltar...");
                getchar();
                break;
            // opção 4 em desenvolvimento
            case 4:
                system("clear");
                printf("\n[INFO] Opcao 'Alterar Privilegio/Senha' em desenvolvimento...\n");
                printf("\nPressione [ENTER] para voltar...");
                getchar();
                break;
            // opção 5 em desenvolvimento
            case 5:
                system("clear");
                printf("\n[INFO] Opcao 'Remover Operador' em desenvolvimento...\n");
                printf("\nPressione [ENTER] para voltar...");
                getchar();
                break;
            // opção 0 volta pra o menu principal
            case 0:
                printf("\nVoltando ao menu principal...\n");
                break;
            // caso a entrada nao seja valida
            default:
                system("clear");
                printf("\n[ERRO] Opcao invalida! Tente novamente.\n");
                printf("\nPressione [ENTER] para continuar...");
                getchar();
                break;
        }
    } while (opcao != 0);
}