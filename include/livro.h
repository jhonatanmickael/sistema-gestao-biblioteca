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

// variaveis globais
extern Livro acervo[100];
extern int totallivros;

// Declarando as funções
void inicializar_livros();
int armazenar_livros();
int carregar_livros();

void submenu_livros_adm();

void listar_livros();
void cadastrar_livro();
void buscar_livro();
void editar_livro();
void remover_livro();

#endif
