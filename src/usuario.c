#include "usuario.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "livro.h"
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
    armazenar[0].type = 1; // 1: Conta para root. 2: Conta comum
    armazenar[0].active = 1; // Conta ativa
    totalusuarios = 1; //Sistema ja começa com 1 usuario

    armazenar_usuarios(&armazenar[0]);
}

// Função para cadastrar novos usuarios
int cadastro() {
    char username_auth[80];

    // Coleta e limpa o Nome Completo
    system("clear");
    printf("\n---- CADASTRO DE USUÁRIO ----\n");
    printf("Digite seu nome completo:\n-> ");
    fgets(armazenar[totalusuarios].name, 50, stdin);
    armazenar[totalusuarios].name[strcspn(armazenar[totalusuarios].name, "\n")] = '\0';
    system("clear");

    // Loop principal para validação do Username
    while (1) {
        printf("\n---- CADASTRO DE USUÁRIO ----\n");
        printf("Nome: %s\n", armazenar[totalusuarios].name);
        printf("--------------------------------\n");
        printf("Digite o username desejado:\n-> ");
        // Coleta e limpa o nome de usuário
        fgets(username_auth, 50, stdin);
        username_auth[strcspn(username_auth, "\n")] = '\0';

        // Se retornar 0 o username ja existe
        if (validar_username(username_auth) == 0) {
            system("clear");
            printf("[!] Erro: O username \"%s\" já está em uso! [!]\n", username_auth);
            printf("\nPressione [ENTER] para tentar outro...");
            getchar();
            system("clear");

            continue; // Volta para pedir outro username
        }

        // Guarda o username aprovado na struct
        strcpy(armazenar[totalusuarios].username, username_auth);

        break; // Se chegou aqui o usarname foi salvo com sucesso
    }

    // Coleta e limpa a Senha para o username criado
    system("clear");
    printf("\n---- CADASTRO DE UTILIZADOR ----\n");
    printf("Nome: %s\n", armazenar[totalusuarios].name);
    printf("Username: %s\n", armazenar[totalusuarios].username);
    printf("--------------------------------\n");
    printf("Digite a password:\n-> ");
    fgets(armazenar[totalusuarios].password, 50, stdin);
    armazenar[totalusuarios].password[strcspn(armazenar[totalusuarios].password, "\n")] = '\0';

    // status do usuario
    armazenar[totalusuarios].id = totalusuarios + 1; // ID automático (1, 2, 3...)
    armazenar[totalusuarios].type = 2;               // 2 = usuario comum
    armazenar[totalusuarios].active = 1;             // 1 = Conta ativa

    char evento[100];
    sprintf(evento, "O usuarios %s foi cadastrado.", armazenar[totalusuarios].username);
    data_log(evento);

    armazenar_usuarios(&armazenar[totalusuarios]);

    // usuario criado com sucesso, incrementa no total de usuarios
    totalusuarios++;
    system("clear");
    printf("[+] Utilizador cadastrado com sucesso! [+]\n");
    printf("\nPressione [ENTER] para voltar ao menu...");
    getchar();
    system("clear");



    return 0; // Sucesso
}

// Função pra fazer o login
int login() {
    char user_digitado[50], senha_digitada[50];

    // Coleta oque foi digitado e limpa o \n final
    system("clear");
    printf("\n---- TELA DE LOGIN ----\n");
    printf("Username:\n-> ");
    fgets(user_digitado, 50, stdin);
    user_digitado[strcspn(user_digitado, "\n")] = '\0';

    // Coleta oque foi digitado e limpa o \n final
    system("clear");
    printf("\n---- TELA DE LOGIN ----\n");
    printf("Senha:\n-> ");
    fgets(senha_digitada, 50, stdin);
    senha_digitada[strcspn(senha_digitada, "\n")] = '\0';

    //  Verifica um por um se as informações correspondem a um usuario e senha ja existentes
    for (int i = 0; i < totalusuarios; i++) {
        if (strcmp(armazenar[i].username, user_digitado) == 0 &&
            strcmp(armazenar[i].password, senha_digitada) == 0) {

            usuario_logado = &armazenar[i];

            // Salva a conta encontrada na sessão global ativa (Corrige o lixo de memória)


            char evento[100];
            sprintf(evento, "O usuario %s fez login", armazenar[i].username);
            data_log(evento);

            system("clear");
            printf("\n");
            printf("  01110   01110   111  001     01   01  01  01110   01110   011100\n");
            printf("  01  01  01     01  01  01    01   01  01  01  01  01  01  01  01\n");
            printf("  01110   01110  01  01  01    01   01  01  01  01  01  01  01  01\n");
            printf("  01  01  01     01  01  01     01 01   01  01  01  01  01  01  01\n");
            printf("  01110   01110  01  01  01      010    01  01  01  01110   011101\n");
            printf("-------------------------------------------------------");
            printf("\nBem-vindo de volta, %s!\n", armazenar[i].name);
            printf("Pressione [ENTER] para continuar...");
            getchar();

            return 1; // Se retornar 1 ent ele fez o login
        }
    }

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
