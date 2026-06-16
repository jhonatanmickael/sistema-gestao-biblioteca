#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "livro.h"

// Criando o local pra alocação dos livros
Livro acervo[100];
int totallivros = 0;

// Função que ja abre o sistem com os 20 livros iniciais
void inicializar_livros() {
    if (carregar_livros() > 0) {
        return;
    }

    char titulos[20][100] = {
        "O Senhor dos Aneis", "1984", "Dom Casmurro", "O Pequeno Principe", "O Hobbit",
        "Fahrenheit 451", "Admiravel Mundo Novo", "A Revolucao dos Bichos", "O Alquimista", "O Codigo Da Vinci",
        "Moby Dick", "Guerra e Paz", "Ulysses", "O Grande Gatsby", "Cem Anos de Solidao",
        "Crime e Castigo", "O Retrato de Dorian Gray", "Dracula", "Frankenstein", "Grande Sertao: Veredas"
    };

    char autores[20][100] = {
        "J.R.R. Tolkien", "George Orwell", "Machado de Assis", "Antoine de Saint-Exupery", "J.R.R. Tolkien",
        "Ray Bradbury", "Aldous Huxley", "George Orwell", "Paulo Coelho", "Dan Brown",
        "Herman Melville", "Leo Tolstoy", "James Joyce", "F. Scott Fitzgerald", "Gabriel Garcia Marquez",
        "Fyodor Dostoevsky", "Oscar Wilde", "Bram Stoker", "Mary Shelley", "Guimaraes Rosa"
    };

    char generos[20][50] = {
        "Fantasia", "Distopia", "Romance", "Infanto-Juvenil", "Fantasia",
        "Ficcao Cientifica", "Distopia", "Satira Politica", "Filosofia", "Suspense",
        "Aventura", "Romance Historico", "Modernismo", "Classico", "Realismo Magico",
        "Romance Psicologico", "Ficcao Gotica", "Terror", "Terror Ficcao", "Literatura Brasileira"
    };

    // 20 livros no vetor acervo
    for (int i = 0; i < 20; i++) {
        acervo[i].id = i + 1; // IDs de 1 a 20
        strcpy(acervo[i].titulo, titulos[i]);
        strcpy(acervo[i].autor, autores[i]);
        strcpy(acervo[i].genero, generos[i]);
        acervo[i].quantidade = 3; // Cada livro começa com 3 copias
        acervo[i].active = 1;     // Todos começam ativos
    }

    totallivros = 20; // Atualiza o contador do sistema para 20
    armazenar_livros(); // Salva a lista inicial
}

// Lista os livros ativos no sistema
void listar_livros() {
    system("clear");
    printf("=================================================================================\n");
    printf("                              ACERVO DA BIBLIOTECA                               \n");
    printf("=================================================================================\n");

    int exibidos = 0;
    printf("%-4s | %-28s | %-25s | %-5s\n", "ID", "TÍTULO", "AUTOR", "QTD");
    printf("---------------------------------------------------------------------------------\n");

    for (int i = 0; i < totallivros; i++) {
        // Só mostra o livro se ele estiver ativo (active == 1)
        if (acervo[i].active == 1) {
            printf("%-4d | %-28.28s | %-25.25s | %-5d\n", 
                   acervo[i].id, 
                   acervo[i].titulo, 
                   acervo[i].autor, 
                   acervo[i].quantidade);
            exibidos++;
        }
    }

    if (exibidos == 0) {
        printf("\n[!] Nenhum livro disponível no acervo no momento. [!]\n");
    }

    printf("---------------------------------------------------------------------------------\n");
    printf("\nPressione [ENTER] para voltar ao menu...");
    getchar(); 
}

// Cadastro de novos livros (Opção exclusiva do Admin/Root)
void cadastrar_livro() {
    system("clear");
    printf("\n---- CADASTRAR NOVO LIVRO ----\n");

    if (totallivros >= 100) {
        printf("[!] Acervo cheio! Não é possível cadastrar mais livros. [!]\n");
        printf("\nPressione [ENTER] para voltar...");
        getchar();
        return;
    }

    Livro novo;
    novo.id = totallivros + 1; // Id sequencial

    // Coletando o nome do livro
    printf("Título do livro:\n-> ");
    fgets(novo.titulo, sizeof(novo.titulo), stdin);
    novo.titulo[strcspn(novo.titulo, "\n")] = '\0';

    // Coletando o autor do livro
    printf("Autor:\n-> ");
    fgets(novo.autor, sizeof(novo.autor), stdin);
    novo.autor[strcspn(novo.autor, "\n")] = '\0';

    // Coletando o gênero do livro
    printf("Gênero:\n-> ");
    fgets(novo.genero, sizeof(novo.genero), stdin);
    novo.genero[strcspn(novo.genero, "\n")] = '\0';

    // Coletando a quantidade de cópias do livro
    printf("Quantidade de exemplares:\n-> ");
    if (scanf("%d", &novo.quantidade) != 1) {
        while (getchar() != '\n');
        printf("\n[!] Erro: Quantidade inválida! Cadastro cancelado. [!]\n");
        printf("\nPressione [ENTER]... ");
        getchar();
        return;
    }
    while (getchar() != '\n'); // Limpa o buffer do scanf

    novo.active = 1; // O livro cadastrado entra como ativo

    acervo[totallivros] = novo;
    totallivros++;
    armazenar_livros();

    printf("\n[+] Livro '%s' cadastrado com sucesso! (ID: %d) [+]\n", novo.titulo, novo.id);
    printf("\nPressione [ENTER] para continuar...");
    getchar();
}

// Função feita para buscar livro pelo id ou nome
void buscar_livro() {
    int tipo_busca = 0;

    system("clear");
    printf("=======================================\n");
    printf("           BUSCA DE LIVROS             \n");
    printf("=======================================\n");
    printf("Como deseja buscar o livro?\n");
    printf("1. Buscar por ID (Exata)\n");
    printf("2. Buscar por Título (Nome)\n");
    printf("-> ");

    // Seletor para escolher se vai buscar por id ou nome
    if (scanf("%d", &tipo_busca) != 1) {
        while (getchar() != '\n'); // Limpa o buffer
        system("clear");
        printf("[!] Entrada inválida! Digite apenas números. [!]\n");
        printf("\nPressione [ENTER] para voltar...");
        getchar();
        return;
    }
    while (getchar() != '\n'); // Limpa o buffer

    if (tipo_busca == 1) {
        // --- BUSCA POR ID ---
        int id_busca = 0;
        system("clear");
        printf("---- BUSCA POR ID ----\n");
        printf("Digite o ID do livro:\n-> ");
        if (scanf("%d", &id_busca) != 1) {
            while (getchar() != '\n');
            printf("\n[!] ID inválido! [!]\n");
            printf("\nPressione [ENTER] para voltar...");
            getchar();
            return;
        }
        while (getchar() != '\n'); // Limpa o buffer

        system("clear");
        printf("=================================================================================\n");
        printf("                               RESULTADO DA BUSCA                                \n");
        printf("=================================================================================\n");
        printf("%-4s | %-28s | %-25s | %-5s\n", "ID", "TÍTULO", "AUTOR", "QTD");
        printf("---------------------------------------------------------------------------------\n");

        int encontrado = 0;
        for (int i = 0; i < totallivros; i++) {
            if (acervo[i].id == id_busca && acervo[i].active == 1) {
                printf("%-4d | %-28.28s | %-25.25s | %-5d\n",
                       acervo[i].id, acervo[i].titulo, acervo[i].autor, acervo[i].quantidade);
                encontrado = 1;
                break;
            }
        }

        if (!encontrado) {
            printf("\n[!] Nenhum livro ativo encontrado com o ID %d. [!]\n", id_busca);
        }
        printf("---------------------------------------------------------------------------------\n");

    } else if (tipo_busca == 2) {
        // --- BUSCA POR NOME ---
        char termo_busca[100];
        system("clear");
        printf("---- BUSCA POR TÍTULO ----\n");
        printf("Digite o termo ou nome do livro:\n-> ");
        fgets(termo_busca, sizeof(termo_busca), stdin);
        termo_busca[strcspn(termo_busca, "\n")] = '\0';

        //Resultado da busca
        system("clear");
        printf("=================================================================================\n");
        printf("                               RESULTADO DA BUSCA                                \n");
        printf("=================================================================================\n");
        printf("%-4s | %-28s | %-25s | %-5s\n", "ID", "TÍTULO", "AUTOR", "QTD");
        printf("---------------------------------------------------------------------------------\n");

        int encontrados = 0;
        for (int i = 0; i < totallivros; i++) {
            // strstr verifica se termo_busca é o titulo do livro
            if (acervo[i].active == 1 && strstr(acervo[i].titulo, termo_busca) != NULL) {
                printf("%-4d | %-28.28s | %-25.25s | %-5d\n", 
                       acervo[i].id, acervo[i].titulo, acervo[i].autor, acervo[i].quantidade);
                encontrados++;
            }
        }

        if (encontrados == 0) {
            printf("\n[!] Nenhum livro encontrado com o termo '%s'. [!]\n", termo_busca);
        }
        printf("---------------------------------------------------------------------------------\n");

    } else {
        printf("\n[!] Opção de busca inválida! [!]\n");
    }

    printf("\nPressione [ENTER] para voltar ao menu...");
    getchar();
}

// Permite ao administrador editar os dados de um livro ativo
void editar_livro() {
    int id_busca = 0;
    int indice = -1;
    char entrada[20];
    int nova_quantidade = 0;

    system("clear");
    printf("====================================\n");
    printf("            EDITAR LIVRO            \n");
    printf("====================================\n");
    printf("Digite o ID do livro que deseja editar:\n-> ");

    if (scanf("%d", &id_busca) != 1) {
        while (getchar() != '\n');
        printf("\n[!] ID inválido! [!]\n");
        printf("\nPressione [ENTER] para voltar...");
        getchar();
        return;
    }
    while (getchar() != '\n');

    for (int i = 0; i < totallivros; i++) {
        if (acervo[i].id == id_busca && acervo[i].active == 1) {
            indice = i;
            break;
        }
    }

    if (indice == -1) {
        printf("\n[!] Livro não encontrado ou removido! [!]\n");
        printf("\nPressione [ENTER] para voltar...");
        getchar();
        return;
    }

    printf("\nLivro encontrado:\n");
    printf("ID: %d\n", acervo[indice].id);
    printf("Título atual: %s\n", acervo[indice].titulo);
    printf("Autor atual: %s\n", acervo[indice].autor);
    printf("Gênero atual: %s\n", acervo[indice].genero);
    printf("Quantidade atual: %d\n", acervo[indice].quantidade);

    printf("\nNovo título:\n-> ");
    fgets(acervo[indice].titulo, sizeof(acervo[indice].titulo), stdin);
    acervo[indice].titulo[strcspn(acervo[indice].titulo, "\n")] = '\0';

    printf("Novo autor:\n-> ");
    fgets(acervo[indice].autor, sizeof(acervo[indice].autor), stdin);
    acervo[indice].autor[strcspn(acervo[indice].autor, "\n")] = '\0';

    printf("Novo gênero:\n-> ");
    fgets(acervo[indice].genero, sizeof(acervo[indice].genero), stdin);
    acervo[indice].genero[strcspn(acervo[indice].genero, "\n")] = '\0';

    printf("Nova quantidade:\n-> ");
    fgets(entrada, sizeof(entrada), stdin);

    if (sscanf(entrada, "%d", &nova_quantidade) != 1 || nova_quantidade < 0) {
        printf("\n[!] Quantidade inválida! Edição cancelada. [!]\n");
        printf("\nPressione [ENTER] para voltar...");
        getchar();
        return;
    }

    acervo[indice].quantidade = nova_quantidade;

    if (armazenar_livros()) {
        printf("\n[+] Livro editado com sucesso! [+]\n");
    } else {
        printf("\n[!] Erro ao salvar alterações do livro! [!]\n");
    }

    printf("\nPressione [ENTER] para continuar...");
    getchar();
}

// Remove o livro do acervo usando exclusão lógica: active = 0
void remover_livro() {
    int id_busca = 0;
    int indice = -1;
    char confirmacao = 'n';

    system("clear");
    printf("====================================\n");
    printf("            REMOVER LIVRO           \n");
    printf("====================================\n");
    printf("Digite o ID do livro que deseja remover:\n-> ");

    if (scanf("%d", &id_busca) != 1) {
        while (getchar() != '\n');
        printf("\n[!] ID inválido! [!]\n");
        printf("\nPressione [ENTER] para voltar...");
        getchar();
        return;
    }
    while (getchar() != '\n');

    for (int i = 0; i < totallivros; i++) {
        if (acervo[i].id == id_busca && acervo[i].active == 1) {
            indice = i;
            break;
        }
    }

    if (indice == -1) {
        printf("\n[!] Livro não encontrado ou já removido! [!]\n");
        printf("\nPressione [ENTER] para voltar...");
        getchar();
        return;
    }

    printf("\nLivro encontrado:\n");
    printf("ID: %d\n", acervo[indice].id);
    printf("Título: %s\n", acervo[indice].titulo);
    printf("Autor: %s\n", acervo[indice].autor);
    printf("Quantidade: %d\n", acervo[indice].quantidade);

    printf("\nTem certeza que deseja remover este livro? (s/n)\n-> ");
    scanf(" %c", &confirmacao);
    while (getchar() != '\n');

    if (confirmacao == 's' || confirmacao == 'S') {
        acervo[indice].active = 0;

        if (armazenar_livros()) {
            printf("\n[+] Livro removido com sucesso! [+]\n");
        } else {
            printf("\n[!] Erro ao salvar remoção do livro! [!]\n");
        }
    } else {
        printf("\n[i] Remoção cancelada. [i]\n");
    }

    printf("\nPressione [ENTER] para continuar...");
    getchar();
}

int armazenar_livros() {
    FILE *arquivo = fopen("../data/livros.dat", "wb");
    if (arquivo == NULL) {
        printf("Erro ao abrir arquivo de livros para escrita!\n");
        return 0;
    }
    // Grava o vetor inteiro de livros ativos de uma vez só
    fwrite(acervo, sizeof(Livro), totallivros, arquivo);
    fclose(arquivo);
    return 1;
}

int carregar_livros() {
    FILE *arquivo = fopen("../data/livros.dat", "rb");
    if (arquivo == NULL) {
        return 0; // Arquivo não existe (primeira execução)
    }
    int lidos = 0;
    while (fread(&acervo[lidos], sizeof(Livro), 1, arquivo) == 1) {
        lidos++;
    }
    totallivros = lidos; // Restaura o total de livros cadastrados
    fclose(arquivo);
    return lidos;
}