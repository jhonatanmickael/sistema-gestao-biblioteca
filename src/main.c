#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
#include "usuario.h"
#include "livro.h"

int main() {
    system("clear");

    inicializar_sistema();
    inicializar_livros();
    menu_inicial();

    return 0;
}
