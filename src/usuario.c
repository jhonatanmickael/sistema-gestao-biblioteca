#include "usuario.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "relatorios.h"

Usuario armazenar[100];
Usuario *usuario_logado = NULL;

int totalusuarios = 0;

// Função que definir o id 1 para conta root
void inicializar_sistema () {
    armazenar[0].id = 1;
    strcpy(armazenar[0].username, "root");
    strcpy(armazenar[0].name, "root");
    strcpy(armazenar[0].password, "root123");
    armazenar[0].type = 1; // 1: conta para adm. 2: conta comum
    armazenar[0].active = 1; // conta ativa
    totalusuarios = 1; // sistema ja começa com 1 usuario

    armazenar_usuarios(&armazenar[0]);
}

// Função para cadastrar novos usuarios
int cadastro() {
    char username_auth[50];

    // verifica se o sistema estorou o limite de usuarios criados
    if (limitar_usuarios() == 0) {
        return 0;
    }

    // grande printf da tela de cadastro e usuario
    system("clear"); 
    printf("==========================================================\n");
    printf("               SISTEMA DE BIBLIOTECA                      \n");
    printf("               MENU: CADASTRO DE USUÁRIO                  \n");
    printf("==========================================================\n");
    printf("Digite seu nome completo:\n");
    printf("----------------------------------------------------------\n");
    printf("-> ");
    
    // coleta o nome completo inserido
    fgets(armazenar[totalusuarios].name, 50, stdin);
    armazenar[totalusuarios].name[strcspn(armazenar[totalusuarios].name, "\n")] = '\0'; // limpa o '\n' no final

    // Se nao inserir nada ele da erro
    if (campo_vazio(armazenar[totalusuarios].name)) {
        printf("\n[!] O nome nao pode ser vazio! [!]\n");
        printf("\nPressione [ENTER] para voltar...");
        getchar();
        return 0;
    }
    system("clear");
    printf("==========================================================\n");
    printf("               SISTEMA DE BIBLIOTECA                      \n");
    printf("               MENU: CADASTRO DE USUÁRIO                  \n");
    printf("==========================================================\n");
    printf("Nome completo: %s\n", armazenar[totalusuarios].name);
    printf("Digite seu nome de usuário:\n");
    printf("----------------------------------------------------------\n");
    printf("-> ");

    // coleta o username inserido
    fgets(username_auth, 50, stdin);
    username_auth[strcspn(username_auth, "\n")] = '\0'; // limpa o '\n' final

    // verifica se o username inserido é valido
    if (campo_vazio(username_auth) || validar_username(username_auth) == 0) {
        printf("\n[!] Nome de usuário inválido ou já em uso! [!]\n");
        printf("\nPressione [ENTER] para voltar...");
        getchar();
        return 0;
    }
    strcpy(armazenar[totalusuarios].username, username_auth);

    system("clear");
    printf("==========================================================\n");
    printf("               SISTEMA DE BIBLIOTECA                      \n");
    printf("               MENU: CADASTRO DE USUÁRIO                  \n");
    printf("==========================================================\n");
    printf("Nome completo: %s\n", armazenar[totalusuarios].name);
    printf("Nome de usuário: %s\n", armazenar[totalusuarios].username);
    printf("Digite a senha para a conta:\n");
    printf("----------------------------------------------------------\n");
    printf("-> ");

    // coleta a senha inserida
    fgets(armazenar[totalusuarios].password, 50, stdin);
    armazenar[totalusuarios].password[strcspn(armazenar[totalusuarios].password, "\n")] = '\0';

    // se deixar o campo vazio ele da erro
    if (campo_vazio(armazenar[totalusuarios].password)) {
        printf("\n[!] A senha nao pode ser vazia! [!]\n");
        printf("\nPressione [ENTER] para voltar...");
        getchar();
        return 0;
    }

    // libera a opção de escolher se vai ser conta comum ou conta de admin
    // essa opção so libera se estiver logado em uma conta de administrador e selecionar pra cadastrar nova conta
    if (usuario_logado != NULL && usuario_logado->type == 1) {
        int tipo_escolhido = 0;
        do {
            system("clear");
            printf("==========================================================\n");
            printf("               SISTEMA DE BIBLIOTECA                      \n");
            printf("               MENU: CADASTRO DE USUÁRIO                  \n");
            printf("==========================================================\n");
            printf("Nome completo: %s\n", armazenar[totalusuarios].name);
            printf("Nome de usuário: %s\n", armazenar[totalusuarios].username);
            printf("Escolha o nível de acesso da conta:\n");
            printf("1. Administrador\n2. Leitor Comum\n");
            printf("----------------------------------------------------------\n");
            printf("-> ");

            // le e ja verifica se oque foi inserido é valido
            if (scanf("%d", &tipo_escolhido) != 1) {
                while (getchar() != '\n'); // limpa o buffer
                tipo_escolhido = -1;
            } else {
                while (getchar() != '\n'); // limpa o buffer
            }

            if (tipo_escolhido < 1 || tipo_escolhido > 2) {
                printf("[!] Opção inválida! Escolha 1 ou 2. [!]\n");
            }
        } while (tipo_escolhido < 1 || tipo_escolhido > 2);
        
        armazenar[totalusuarios].type = tipo_escolhido;
    } else {
        // Cadastro comum vindo da tela inicial sem login
        armazenar[totalusuarios].type = 2; 
    }

    // Configura o restante das propriedades do usuário
    armazenar[totalusuarios].id = totalusuarios + 1;
    armazenar[totalusuarios].active = 1; // conta ativa

    // armazena as informações inseridas no arquivo binário
    if (armazenar_usuarios(&armazenar[totalusuarios])) {
        // Gera o log do evento
        char log_msg[100];
        snprintf(log_msg, sizeof(log_msg), "Cadastrou o usuário '%s' como %s", 
                 armazenar[totalusuarios].username, (armazenar[totalusuarios].type == 1 ? "ADM" : "Leitor Comum"));
        data_log(log_msg);

        // grande printf pra mostrar os dados da nova conta cadastrada
        system("clear");
        printf("====================================================\n");
        printf("           CONTA CADASTRADA COM SUCESSO!            \n");
        printf("====================================================\n");
        printf("  [i] Detalhes da nova credencial no sistema:\n\n");
        printf("  > ID do Usuário:   #%03d\n", totalusuarios + 1);
        printf("  > Nome Completo:   %s\n", armazenar[totalusuarios].name);
        printf("  > Nome de Usuário: %s\n", armazenar[totalusuarios].username);
        printf("  > Tipo de Conta:   %s\n", (armazenar[totalusuarios].type == 1 ? "Administrador" : "Leitor Comum"));
        printf("  > Status do Perfil: Ativo\n");
        printf("====================================================\n");
        
        totalusuarios++;
    } else {
        printf("\n[!] Erro crítico ao salvar no arquivo de dados. [!]\n");
    }

    printf("\nPressione [ENTER] para continuar...");
    getchar();
    return 1;
}

// Função pra fazer o login
int login() {
    char user_digitado[50], senha_digitada[50];

    // grande printf de iniciar sessao
    system("clear");
    printf("====================================================\n");
    printf("                   INICIAR SESSÃO                   \n");
    printf("====================================================\n");
    printf("Nome de Usuário:\n");
    printf("----------------------------------------------------\n");
    printf("-> ");

    // coleta o nome de usuario
    fgets(user_digitado, 50, stdin);
    user_digitado[strcspn(user_digitado, "\n")] = '\0'; // limpa o '\n'

    // grande printf de iniciar sessao
    system("clear");
    printf("====================================================\n");
    printf("                   INICIAR SESSÃO                   \n");
    printf("====================================================\n");
    printf("Nome de Usuário: %s\n", user_digitado);
    printf("----------------------------------------------------\n");
    printf("Digite sua senha:\n");
    printf("----------------------------------------------------\n");
    printf("-> ");

    // coleta a senha
    fgets(senha_digitada, 50, stdin);
    senha_digitada[strcspn(senha_digitada, "\n")] = '\0'; // limpa o '\n'

    //  olha um por um se o usuario existe e a senha corresponde a esse usuario
    for (int i = 0; i < totalusuarios; i++) {
        if (strcmp(armazenar[i].username, user_digitado) == 0 &&
            strcmp(armazenar[i].password, senha_digitada) == 0){

            // caso a conta esteja desativada
            if (validar_atividade(&armazenar[i]) == 0) {
                system("clear");
                printf("[!] Esta conta está desativada. [!]\n");
                printf("\nPressione [ENTER] para continuar...");
                getchar();
                return 0;
            }

            // salva a conta na sessao global ativa para usuario logado
            usuario_logado = &armazenar[i];

            // salva o log
            // 150 de tamanho para prevenir o estouro de string
            char evento[150];
            sprintf(evento, "O usuario %s fez login", armazenar[i].username);
            data_log(evento);

            system("clear");
            printf("\n");
            printf("-----------------------------------------------------------------------\n");
            printf("    01110   01110   111  001     01   01  01  01110   01110   011100\n");
            printf("    01  01  01     01  01  01    01   01  01  01  01  01  01  01  01\n");
            printf("    01110   01110  01  01  01    01   01  01  01  01  01  01  01  01\n");
            printf("    01  01  01     01  01  01     01 01   01  01  01  01  01  01  01\n");
            printf("    01110   01110  01  01  01      010    01  01  01  01110   011101\n");
            printf("-----------------------------------------------------------------------\n");
            printf("\nBem-vindo de volta, %s!\n", armazenar[i].name);
            printf("Pressione [ENTER] para continuar...");
            getchar();

            return 1; // Se retornar 1 ent ele fez o login
        }
    }

    // se o usuario e senha não corresponderem ele aponta falha de login
    system("clear");
    printf("\n[!] Erro: Username ou senha incorretos.\n");
    printf("Presione [ENTER] para continuar...");
    getchar();

    return 0; // N conseguiu fzr o login
}

// Função para listar todos os livros
void listagem () {
    system("clear");
    printf("=====================================================\n");
    printf("                LISTA DE UTILIZADORES                \n");
    printf("=====================================================\n");

    if (totalusuarios == 0) {
        printf("\n[!] Não há utilizadores cadastrados no sistema. [!]\n");
    } else {
        printf("%-4s | %-25s | %-15s\n", "ID", "NOME", "USERNAME");
        printf("-----------------------------------------------------\n");
        for (int i = 0; i < totalusuarios; i++) {
            printf("%-04d | %-25.25s | %-15.15s\n",
                   armazenar[i].id,
                   armazenar[i].name,
                   armazenar[i].username);
        }
    }
    printf("=====================================================\n");

    printf("\nPressione [ENTER] para voltar ao menu...");
    getchar();
}

// Verifica se um username ja existe
int validar_username (char *username2) {
    for (int i = 0; i < totalusuarios; i++) {
        if (strcmp(armazenar[i].username, username2) == 0){

            return 0; // ja existe um usuario com esse username
        }
    }
    return 1; // n existe um usuario com esse username
}

int armazenar_usuarios(Usuario *usuario) {

    FILE *arquivo = fopen("../data/usuarios.dat", "ab");

    if (arquivo == NULL) {
        printf("Arquivo não localizado!\n");
        return 0;
    }

    fwrite(usuario, sizeof(Usuario), 1, arquivo);

    fclose(arquivo);

    return 1;
}

int carregar_usuarios() {
    FILE *arquivo = fopen("../data/usuarios.dat", "rb");

    if (arquivo == NULL) {
        totalusuarios = 0;
        return 0; 
    }

    totalusuarios = 0;

    while (fread(&armazenar[totalusuarios], sizeof(Usuario), 1, arquivo) == 1) {
        totalusuarios++;
    }

    fclose(arquivo);

    return totalusuarios > 0;
}

int limitar_usuarios() {
    if (totalusuarios >= 100) {
        system("clear");
        printf("[!] Limite máximo de usuários atingido. [!]\n");
        printf("Não é possível cadastrar mais usuários.\n");
        printf("\nPressione [ENTER] para voltar...");
        getchar();
        return 0;
    }
    return 1;
}

int campo_vazio(char *texto) {
    for (int i = 0; texto[i] != '\0'; i++) {
        if (!isspace(texto[i])) {
            return 0;
        }
    }
    return 1;
}

int validar_atividade(Usuario *usuario) {
    if (usuario->active == 0) {
        return 0;
    }
    return 1;
}