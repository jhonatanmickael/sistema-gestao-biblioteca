#ifndef LIVRO_H
#define LIVRO_H

//Struct para salvar livros individualmente
typedef struct {
    int id;
    char titulo[100];
    char autor[100];
    char genero[50];
    int quantidade;
    int active; // 1 para ativo, 0 se for deletado no futuro
} Livro;

// Transformando em variaveis globais
extern Livro acervo[100];
extern int totallivros;

// Declarando as funções
void inicializar_livros();
void listar_livros();
void cadastrar_livro();

#endif
