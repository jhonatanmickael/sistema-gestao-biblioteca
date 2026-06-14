#ifndef EMPRESTIMO_H
#define EMPRESTIMO_H

// struct para salvar os emprestimos
typedef struct {
    int id_emprestimo;
    int id_usuario;   // id de quem pegou
    int id_livro;     // id de qual livro pegou
    int status;       // 1 = Emprestado, 0 = Devolvido
} Emprestimo;


// Definindo as variaveis globais
extern Emprestimo controle_emprestimos[100];
extern int totalemprestimos;

// Definindo as funções criadas
void solicitar_emprestimo();
void devolver_livro();
int armazenar_emprestimos();
int carregar_emprestimos();
void listar_emprestimos();

#endif
