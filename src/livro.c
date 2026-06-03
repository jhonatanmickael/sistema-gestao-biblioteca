#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "livro.h"

// Criando o local pra alocação dos livros
Livro acervo[100];
int totallivros = 0;

// Função que ja abre o sistem com os 20 livros iniciais
void inicializar_livros() {
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

    // Laço para rotular os 20 livros no vetor acervo
    for (int i = 0; i < 20; i++) {
        acervo[i].id = i + 1; // IDs de 1 a 20
        strcpy(acervo[i].titulo, titulos[i]);
        strcpy(acervo[i].autor, autores[i]);
        strcpy(acervo[i].genero, generos[i]);
        acervo[i].quantidade = 3; // Cada livro começa com 3 copias
        acervo[i].active = 1;     // Todos começam ativos (não deletados)
    }

    totallivros = 20; // Atualiza o contador do sistema para 20
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
            printf("%-04d | %-28.28s | %-25.25s | %-5d\n", 
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

    printf("\n[+] Livro '%s' cadastrado com sucesso! (ID: %d) [+]\n", novo.titulo, novo.id);
    printf("\nPressione [ENTER] para continuar...");
    getchar();
}
