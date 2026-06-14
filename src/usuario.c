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
    if (limitar_usuarios() == 0) {
        return 0;
    }
    // grande printf da tela de cadastro e usuario
    system("clear"); 
    printf("====================================================\n");
    printf("               CADASTRO DE USUÁRIO                  \n");
    printf("====================================================\n");
    printf("Digite seu nome completo:\n");
    printf("----------------------------------------------------\n");
    printf("-> ");
    
    // coleta o nome completo inserido
    fgets(armazenar[totalusuarios].name, 50, stdin);
    armazenar[totalusuarios].name[strcspn(armazenar[totalusuarios].name, "\n")] = '\0';
    system("clear");

  
    while (1) {
        system("clear");
        printf("====================================================\n");
        printf("               CADASTRO DE USUÁRIO                  \n");
        printf("====================================================\n");
        printf("Nome: %s\n", armazenar[totalusuarios].name);
        printf("-----------------------------------------------------\n");
        printf("Digite o Nome de Usuário desejado:\n");
        printf("----------------------------------------------------\n");
        printf("-> ");
        
        // coleta e salva o nome de usuario
        fgets(username_auth, 50, stdin);
        username_auth[strcspn(username_auth, "\n")] = '\0'; // limpa o '\n' do fgets

        if (campo_vazio(username_auth) == 1) {
            system("clear");
            printf("Username não pode ficar vazio!...\n");
            printf("Pressione [ENTER] para tentar novamente...\n");
            getchar();
            continue;
        }

        // Se retornar 0 o username ja existe
        if (validar_username(username_auth) == 0) {
            system("clear");
            printf("[!] Erro: O username \"%s\" já está em uso! [!]\n", username_auth);
            printf("\nPressione [ENTER] para tentar outro...");
            getchar();
            system("clear");

            continue; // volta para pedir outro username
        }

        // Guarda o username aprovado na struct
        strcpy(armazenar[totalusuarios].username, username_auth);

        break; // se chegou aqui o usarname foi salvo com sucesso
    }

    system("clear");  
    printf("====================================================\n");
    printf("               CADASTRO DE USUÁRIO                  \n");
    printf("====================================================\n");
    printf("Nome: %s\n", armazenar[totalusuarios].name);
    printf("Nome de Usuário: %s\n", armazenar[totalusuarios].username);
    printf("-----------------------------------------------------\n");
    printf("Digite a senha que deseja:\n");
    printf("-----------------------------------------------------\n");
    printf("-> ");

    // le a entrada e salva a senha
    fgets(armazenar[totalusuarios].password, 50, stdin);
    armazenar[totalusuarios].password[strcspn(armazenar[totalusuarios].password, "\n")] = '\0';

    // atualiza informações do usuario
    armazenar[totalusuarios].id = totalusuarios + 1; // id sequencial (1, 2, 3...)
    armazenar[totalusuarios].type = 2;               // 2 = usuario comum
    armazenar[totalusuarios].active = 1;             // 1 = Conta ativa

    // salvando o log
    char evento[100];
    sprintf(evento, "O usuário %s foi cadastrado.", armazenar[totalusuarios].username);
    data_log(evento);
    armazenar_usuarios(&armazenar[totalusuarios]);

    // grande printf dos dados cadastrados
    system("clear");
    printf("====================================================\n");
    printf("          CONTA CRIADA COM SUCESSO!                 \n");
    printf("====================================================\n");
    printf(" Nome:     %s\n", armazenar[totalusuarios].name);
    printf(" Usuário:  %s\n", armazenar[totalusuarios].username);
    printf(" ID:       %d\n", armazenar[totalusuarios].id);
    printf(" Nível:    %s\n", (armazenar[totalusuarios].type == 1) ? "Administrador" : "Leitor Comum");
    printf("----------------------------------------------------\n");
    printf("Pressione [ENTER] para voltar ao menu...");
    getchar();

    // incrementa no total de usuarios apos o uso dos dados atuais
    totalusuarios++;
    system("clear");

    return 0; // Sucesso
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

            return 0; // Ja existe um usuario com esse username
        }
    }
    return 1; // Não existe um usuario com esse username
}

int armazenar_usuarios(Usuario *usuario) {

    FILE *arquivo = fopen("../data/usuarios.dat", "ab");

    if (arquivo == NULL) {
        printf("Arquivo não localizado!");
        return 0;
    }

    fwrite(usuario, sizeof(Usuario), 1, arquivo);

    fclose(arquivo);

    return 1;
}

int carregar_usuarios() {

    FILE *arquivo = fopen("../data/usuarios.dat", "rb");

    if (arquivo == NULL) {
        printf("Arquivo não encontrado");
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