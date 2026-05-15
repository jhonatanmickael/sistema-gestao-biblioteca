#include <stdio.h>

int menu_login() {
    int opt;
    printf("\n--- SISTEMA BIBLIOTECA ---\n");
    printf("1. Entrar\n2. Cadastrar\nEscolha: ");

    // CASO O USUARIO DIGITE LETRA:
    if (scanf("%d", &opt) != 1) {
        while (getchar() != '\n'); 
        return -1; 
    }

    // APAGANDO LETRAS QUE SOBRAREM NO BUFFER CASO ELE TENHA DIGITADO LETRAS ANTERIORMENTE
    while (getchar() != '\n'); 
    return opt;
}
