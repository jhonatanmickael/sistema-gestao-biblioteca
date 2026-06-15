#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
#include "usuario.h"
#include "livro.h"
#include "emprestimo.h"

int main() {
    system("clear");
    usuario_logado = NULL;
    carregar_usuarios();
    if (totalusuarios == 0) {
        inicializar_sistema();
    }
    carregar_emprestimos();
    inicializar_livros();
    carregar_emprestimos();
    menu_inicial();

    return 0;
}
