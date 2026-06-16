#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "usuario.h"
#include "menu.h"
#include "livro.h"
#include "emprestimo.h"
#include <string.h>

// cabeçalho padrao pra diminuir um pouco o codigo
void exibir_cabecalho(char *subtitulo) {
    int largura_total = 82; // largura de tudo
    int tam_texto = strlen(subtitulo);
    // calcula a quantidade de espaços a esquerda pra centralizar
    int espacos_esquerda = (largura_total - tam_texto) / 2;
    system("clear");
    printf("==================================================================================\n");
    printf("                          SISTEMA DE GESTÃO DE BIBLIOTECA                         \n");
    // imprime os espaços a esquerdas pra centralizar
    for (int i = 0; i < espacos_esquerda; i++) {
        printf(" ");
    }
    // imprime o texto escolhido
    printf("%s\n", subtitulo);
    printf("==================================================================================\n");
}

// linhas padroes usadas
void linha() {
    int tam_linha = 82; // altere aqui o tamanho das linhas padroes
    for (int i = 0; i < tam_linha; i++) {
        printf("-");
    }
    printf("\n");
}

// tela de cadastro e entrada
void menu_inicial () {
    int select = 0;

    while (1) {
        // grande printf da tela e cadastro
        system("clear");
        exibir_cabecalho("-> TELA INICIAL <-");
        printf("Seja bem-vindo ao Sitema de Gestão de Bibliotecas.  \n");
        linha();
        printf("1. Cadastrar\n2. Login\n");
        linha();

        // le e ja verifica se oque foi inserido é um num inteiro
        if (scanf("%d", &select) != 1) {
            while (getchar() != '\n'); // limpa o buffer
            select = -1;
            system("clear");
            exibir_cabecalho("-> TELA INICIAL <-");
            printf("[!] Digite apenas numeros [!]");
            linha();
            printf("Pressione [ENTER] para continuar...");
            getchar();
            system("clear");
            continue; // volta para o inicio do menu
        }

        // verifica se foi inserido uma opção que não seja 1 ou 2
        if (select > 2 || select < 1) {
            while (getchar() != '\n'); // limpa o buffer
            system("clear");
            exibir_cabecalho("-> TELA INICIAL <-");
            printf("\n[!] Digite uma opção valida [!]\n");
            linha();
            printf("Pressione [ENTER] para continuar...");
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
        // grande printf pra mostrar todo o menu
        system("clear");
        exibir_cabecalho("-> MENU PRINCIPAL <-");
        printf("Usuário conectado: %s\n", usuario_logado->name);
        linha();
        printf("1. Livros\n");
        printf("2. Emprestimos\n");

        // printf que somente adms tem acesso a opcao abaixo
        if (usuario_logado->type == 1) {
            printf("3. [ADM] Gerenciar Livros\n");
            printf("4. [ADM] Gerenciar Usuários\n");
            printf("5. [ADM] Gerenciar Logs\n");
        }
        printf("0. Fazer Logout (Sair)\n");
        linha();
        printf("-> ");

        // le uma entrada e ja verifica se é uma entrada valida
        if (scanf("%d", &opcao) != 1) {
            while (getchar() != '\n'); // limpa o buffer
            opcao = -1;
            system("clear");
            exibir_cabecalho("-> MENU PRINCIPAL <-");
            printf("[!] Entrada inválida! Digite apenas números. [!]\n");
            linha();
            printf("Pressione [ENTER] para tentar novamente...");
            getchar();
            continue;
        }
        while (getchar() != '\n'); // limpa o buffer

        // volta pra o menu inicial se a entrada for 0
        if (opcao == 0) {
            system("clear");
            exibir_cabecalho("-> MENU PRINCIPAL <-");
            printf("A encerrar a sessão de %s...\n", usuario_logado->name);
            linha();
            printf("Pressione [ENTER] para voltar ao menu inicial...");
            getchar();
            usuario_logado = NULL; // forçando o ponteiro a desconectar de uma conta
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
            submenu_livros_adm();
        }
        // chama a submenu de usuarios se a entrada for 4
        else if (opcao == 4 && usuario_logado->type == 1) {
            submenu_usuarios();
        }
        // chama a listagem de logs se a entrada for 5
        else if (opcao == 5 && usuario_logado->type == 1) {
            menu_logs();
        }
        // tratamento de erro para entradas invalidas
        else {
            system("clear");
            exibir_cabecalho("-> MENU PRINCIPAL <-");
            printf("[!] Opção Inválida! [!]\n");
            linha();
            printf("Pressione [ENTER] para tentar novamente...");
            getchar();
        }
    }
}

// submenu de livros, opção 1 do menu principal
void submenu_livros() {
    int opcao = 0;
    
    // grande printf da tela de menu de livros
    while (1) {
        system("clear");
        exibir_cabecalho("-> LIVROS <-");
        printf("1. Listar Livros Disponíveis\n");
        printf("2. Buscar Livro por Título\n");
        printf("0. Voltar ao Menu Principal\n");
        linha();
        printf("-> ");
        
        // le uma entrada e ja verifica se é um numero inteiro
        if (scanf("%d", &opcao) != 1) {
            while (getchar() != '\n'); // limpa o buffer
            system("clear");
            exibir_cabecalho("-> LIVROS <-");
            printf("[!] Entrada inválida! Digite apenas números. [!]\n");
            linha();
            printf("Pressione [ENTER] para tentar novamente...");
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
            exibir_cabecalho("-> LIVROS <-");
            printf("[!] Opção Inválida! [!]\n");
            linha();
            printf("Pressione [ENTER] para tentar novamente...");
            getchar();
        }
    }
}

// submenu de emprestimo, opção 2 do menu principal
void submenu_emprestimos() { 
    int opcao = 0;
    
    // grande printf da tela de emprestimos
    while (1) {
        system("clear");
        exibir_cabecalho("-> EMPRESTIMOS <-");
        printf("1. Pegar Livro Emprestado\n");
        printf("2. Devolver um Livro\n");
        printf("3. Meus Empréstimos Pendentes\n");
        printf("0. Voltar ao Menu Principal\n");
        linha();
        printf("-> ");
        
        // coleta a opção inserida e ja verifica se foi inserido um num inteiro
        if (scanf("%d", &opcao) != 1) {
            while (getchar() != '\n'); 
            system("clear");
            exibir_cabecalho("-> EMPRESTIMOS <-");
            printf("[!] Entrada inválida! Digite apenas números. [!]\n");
            linha();
            printf("Pressione [ENTER] para tentar novamente...");
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
            exibir_cabecalho("-> EMPRESTIMOS <-");
            printf("[!] Opção Inválida! [!]");
            linha();
            printf("Pressione [ENTER] para tentar novamente...");
            getchar();
        }
    }
}

// submenu de gerenciar livros, opção 3 do menu principal
void submenu_livros_adm() {
    int opcao = 0;

    while (1) {
        system("clear");
        exibir_cabecalho("-> GERENCIAR LIVROS <-");
        printf("1. Cadastrar livro\n");
        printf("2. Editar livro\n");
        printf("3. Remover livro\n");
        printf("0. Voltar\n");
        linha();

        if (scanf("%d", &opcao) != 1) {
            while (getchar() != '\n');
            opcao = -1;
            system("clear");
            exibir_cabecalho("-> GERENCIAR LIVROS <-");
            printf("[!] Digite apenas números! [!]\n");
            linha();
            printf("Pressione [ENTER] para continuar...");
            getchar();
            continue;
        }
        while (getchar() != '\n');

        if (opcao == 0) {
            break;
        } else if (opcao == 1) {
            cadastrar_livro();
        } else if (opcao == 2) {
            editar_livro();
        } else if (opcao == 3) {
            remover_livro();
        } else {
            system("clear");
            exibir_cabecalho("-> GERENCIAR LIVROS <-");
            printf("[!] Opção inválida! [!]\n");
            linha();
            printf("Pressione [ENTER] para continuar...");
            getchar();
        }
    }
}

// submenu de gestão de usuarios, opção 4 do menu principal
void submenu_usuarios() {
    int opcao;
    
    do {
        // grande printf so submenu de usuarios
        system("clear");
        exibir_cabecalho("-> GERENCIAR USUÁRIOS <-");
        printf("1. Cadastrar Novo Usuário\n");
        printf("2. Listar Todos os Usuários\n");
        printf("3. Buscar Usuário\n");
        printf("4. Editar Usuário\n");
        printf("0. Voltar ao Menu Principal\n");
        linha();
        printf("-> ");
        
        // Le e ja verifica se a entrada é valida
        if (scanf("%d", &opcao) != 1) {
            while (getchar() != '\n'); // limpa o buffer
            opcao = -1; 
        } else {
            while (getchar() != '\n'); // limpa o buffer
        }
        
        // se escolher 1 abre a tela de cadastro
        if (opcao == 1) {
            cadastro();
        }
        // se escolher 2 lista todos os usuarios
        else if (opcao == 2) {
            listagem(); 
        }
        // se escolher 3 abre a busca de usuario
        else if (opcao == 3) {
            buscar_usuario();
        }
        // se escolher 4 abre o editor de usuario
        else if (opcao == 4) {
            editar_usuario();
        }
        // opção 0 volta pra o menu principal
        else if (opcao == 0) {
            // mantem o 0, quando chegar na verificaçção ele vai parar o loop
        }
        // caso a entrada nao seja valida
        else {
            system("clear");
            exibir_cabecalho("-> GERENCIAR USUÁRIOS");
            printf("[!] Opcao invalida! Tente novamente. [!]\n");
            linha();
            printf("Pressione [ENTER] para continuar...");
            getchar();
        }
    } while (opcao != 0);
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