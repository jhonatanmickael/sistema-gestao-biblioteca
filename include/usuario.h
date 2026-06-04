#ifndef USUARIOS_H
#define USUARIOS_H

// Struct para usuarios
typedef struct {
    char name[50];
    char password[50];
    char username[50];
    int id;
    int type;
    int active;
}Usuario;


// Definindo as funções
void inicializar_sistema();
int cadastro();
void listagem();
int login();
int validar_username(char *username2);


// Transformando em variaveis globais
extern Usuario *usuario_logado;
extern Usuario armazenar[100];
extern int totalusuarios;

#endif
