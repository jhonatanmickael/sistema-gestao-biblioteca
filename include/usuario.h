#ifndef USUARIOS_H
#define USUARIOS_H

typedef struct {
    char name[50];
    char password[50];
    char username[50];
    int id;
    int type;
    int active;
}Usuario;

int cadastro();
void listagem();
int login();

#endif
