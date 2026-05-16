#include "usuario.h"
#include <stdio.h>
#include <string.h>

Usuario armazenar[100];
int totalusuarios = 0;

int cadastro() {
    printf("\nCadastro de usuarios\n");

    printf("Digite o nome do usuario: ");
    fgets(armazenar[totalusuarios].name, 50, stdin);
    armazenar[totalusuarios].name[
        strcspn(armazenar[totalusuarios].name, "\n")
    ] = '\0';

    printf("\nDigite seu username: \n");
    fgets(armazenar[totalusuarios].username, 50, stdin);
    armazenar[totalusuarios].username[
        strcspn(armazenar[totalusuarios].username, "\n")
    ] = '\0';

    printf("\nDigite seu password: \n");
    fgets(armazenar[totalusuarios].password, 50, stdin);
    armazenar[totalusuarios].password[
        strcspn(armazenar[totalusuarios].password, "\n")
    ] = '\0';

    totalusuarios++;

    return 0;
}

void listagem () {
    if (totalusuarios == 0) {
        printf("Nao ha usuarios cadastrados");
        return;
    }

    for (int i = 0; i < totalusuarios; i++) {
        printf("Usuarios: %d\n", i+1);

        printf("Nome: %s\n", armazenar[i].name);

        printf("Username: %s\n", armazenar[i].username);

    }
<<<<<<< HEAD
}
=======
}

int login() {
    char user_digitado[50];
    char senha_digitada[50];

    printf("\n--- TELA DE LOGIN ---\n");
)
    setbuf(stdin, NULL);

    printf("Username: ");
    fgets(user_digitado, 50, stdin);
    user_digitado[strcspn(user_digitado, "\n")] = '\0';

    printf("Senha: ");
    fgets(senha_digitada, 50, stdin);
    senha_digitada[strcspn(senha_digitada, "\n")] = '\0';

    for (int i = 0; i < totalusuarios; i++) {
        if (strcmp(armazenar[i].username, user_digitado) == 0 &&
            strcmp(armazenar[i].password, senha_digitada) == 0) {

            printf("\nBem-vindo de volta, %s!\n", armazenar[i].name);
            return 1; // Se retornar 1 ent ele fez o login
        }
    }
    printf("\n[!] Erro: Username ou senha incorretos.\n");
    return 0; // N conseguiu fzr o login
}
>>>>>>> origin/main
