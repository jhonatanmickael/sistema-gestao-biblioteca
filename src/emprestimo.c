#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "emprestimo.h"
#include "usuario.h"
#include "livro.h"
#include "relatorios.h"

// Inicializando as variáveis globais
Emprestimo controle_emprestimos[100];
int totalemprestimos = 0;

// Função para solicitar um livro emprestado (Por ID ou por Nome)
void solicitar_emprestimo() {
    int tipo_busca = 0;

    system("clear");
    printf("=======================================\n");
    printf("        SOLICITAR EMPRÉSTIMO           \n");
    printf("=======================================\n");
    printf("Como deseja selecionar o livro?\n");
    printf("1. Pelo ID\n");
    printf("2. Pelo Título\n");
    printf("-> ");

// Le a opção inserida e ja verifica se oque foi digitado é um numero inteiro
    if (scanf("%d", &tipo_busca) != 1) {
        while (getchar() != '\n');
        system("clear");
        printf("[!] Entrada inválida! Digite apenas números. [!]\n");
        printf("\nPressione [ENTER] para voltar...");
        getchar();
        return;
    }
    while (getchar() != '\n'); // Limpa o buffer

    int livro_index = -1;

    if (tipo_busca == 1) {
        // --- SELEÇÃO POR ID ---
        int id_busca = 0;
        system("clear");
        printf("---- SOLICITAR POR ID ----\n");
        printf("Digite o ID do livro que deseja:\n-> ");
        // Le a opção inserida e ja verifica se foi inserido um numero inteiro
	if (scanf("%d", &id_busca) != 1) {
            while (getchar() != '\n'); // limpa o buffer
            printf("\n[!] ID inválido! [!]\n");
            printf("\nPressione [ENTER] para voltar...");
            getchar();
            return;
        }
        while (getchar() != '\n'); // Limpa o buffer

        // Procura o livro pelo ID no acervo
        for (int i = 0; i < totallivros; i++) {
            if (acervo[i].id == id_busca && acervo[i].active == 1) {
                livro_index = i;
                break;
            }
        }

        if (livro_index == -1) {
            printf("\n[!] Livro não encontrado ou inativo no sistema! [!]\n");
            printf("\nPressione [ENTER] para voltar...");
            getchar();
            return;
        }

    } else if (tipo_busca == 2) {
        // --- SELEÇÃO POR NOME ---
        char termo_busca[100];
        system("clear");
        printf("---- SOLICITAR POR TÍTULO ----\n");
        printf("Digite o nome ou parte do título do livro:\n-> ");
        // Pega o nome do livro e ja limpa o ultimo caracter '\n'
	fgets(termo_busca, sizeof(termo_busca), stdin);
        termo_busca[strcspn(termo_busca, "\n")] = '\0';

        // Vetor dinâmico local para guardar os índices dos livros encontrados
        int indices_encontrados[100];
        int qtd_encontrados = 0;

        for (int i = 0; i < totallivros; i++) {
            if (acervo[i].active == 1 && strstr(acervo[i].titulo, termo_busca) != NULL) {
                indices_encontrados[qtd_encontrados] = i;
                qtd_encontrados++;
            }
        }

        if (qtd_encontrados == 0) {
            printf("\n[!] Nenhum livro ativo encontrado com o termo '%s'. [!]\n", termo_busca);
            printf("\nPressione [ENTER] para voltar...");
            getchar();
            return;
        } 
        
        // Se encontrou exatamente 1 livro, seleciona direto
        if (qtd_encontrados == 1) {
            livro_index = indices_encontrados[0];
            printf("\n[i] Livro encontrado: '%s'\n", acervo[livro_index].titulo);
        } 
        // Se encontrou mais de um, lista os livros para o usuário escolher pelo ID correspondente
        else {
            system("clear");
            printf("===================================================================\n");
            printf("             LIVROS ENCONTRADOS (Escolha um pelo ID)               \n");
            printf("===================================================================\n");
            printf("%-4s | %-28s | %-25s\n", "ID", "TÍTULO", "AUTOR");
            printf("-------------------------------------------------------------------\n");
            for (int i = 0; i < qtd_encontrados; i++) {
                int idx = indices_encontrados[i];
                printf("%-04d | %-28.28s | %-25.25s\n", acervo[idx].id, acervo[idx].titulo, acervo[idx].autor);
            }
            printf("-------------------------------------------------------------------\n");
            printf("Digite o ID do livro que deseja pegar emprestado:\n-> ");
            
	    // Le a opção inserida e ja verifica se é um numero inteiro
            int id_escolhido = 0;
            if (scanf("%d", &id_escolhido) != 1) {
                while (getchar() != '\n'); // limpa o buffer
                printf("\n[!] Entrada inválida! Empréstimo cancelado. [!]\n");
                printf("\nPressione [ENTER] para voltar...");
                getchar();
                return;
            }
            while (getchar() != '\n'); // Limpa o buffer

            // Valida se o ID escolhido está dentro da lista de encontrados
            for (int i = 0; i < qtd_encontrados; i++) {
                int idx = indices_encontrados[i];
                if (acervo[idx].id == id_escolhido) {
                    livro_index = idx;
                    break;
                }
            }

            if (livro_index == -1) {
                printf("\n[!] ID digitado não corresponde aos livros listados! [!]\n");
                printf("\nPressione [ENTER] para voltar...");
                getchar();
                return;
            }
        }

    } else {
        printf("\n[!] Opção de busca inválida! [!]\n");
        printf("\nPressione [ENTER] para voltar...");
        getchar();
        return;
    }

    // --- PROCESSAMENTO DA RETIRADA ---
    if (acervo[livro_index].quantidade <= 0) {
        printf("\n[!] Desculpe, não há exemplares disponíveis desse livro no estoque! [!]\n");
    } else {
        // Registra os dados do empréstimo ativo
        controle_emprestimos[totalemprestimos].id_emprestimo = totalemprestimos + 1;
        controle_emprestimos[totalemprestimos].id_usuario = usuario_logado->id;
        controle_emprestimos[totalemprestimos].id_livro = acervo[livro_index].id;
        controle_emprestimos[totalemprestimos].status = 1; // 1 significa Ativo

        // Decrementa o estoque do livro no acervo
        acervo[livro_index].quantidade--;
        totalemprestimos++;

        printf("\n[+] Empréstimo do livro '%s' realizado com sucesso! [+]\n", acervo[livro_index].titulo);
        char evento[100];
        sprintf(evento, "O usuario %s pegou o livro %s emprestado!", usuario_logado->name, acervo[livro_index].titulo);
        data_log(evento);

    }

    printf("\nPressione [ENTER] para continuar...");
    getchar();
}

// Função para devolver um livro ativo baseado no ID do Livro
void devolver_livro() {
    int id_livro_dev = 0;
    system("clear");
    printf("=======================================\n");
    printf("          DEVOLVER LIVRO               \n");
    printf("=======================================\n");
    printf("Digite o ID do LIVRO que você vai devolver:\n-> ");

    // Le e ja verifica se o usuario digitou um numero inteiro
    if (scanf("%d", &id_livro_dev) != 1) {
        while (getchar() != '\n'); // Limpa o buffer
        printf("\n[!] Entrada inválida! [!]\n");
        printf("\nPressione [ENTER] para voltar...");
        getchar();
        return;
    }
    while (getchar() != '\n'); // limpa o buffer

    int encontrado = 0;
    for (int i = 0; i < totalemprestimos; i++) {
        // O empréstimo precisa ser do livro digitado, pertencer ao usuário logado e estar ativo (status == 1)
        if (controle_emprestimos[i].id_livro == id_livro_dev && 
            controle_emprestimos[i].id_usuario == usuario_logado->id &&
            controle_emprestimos[i].status == 1) {
            
            // Finaliza o empréstimo (muda status para 0/Devolvido)
            controle_emprestimos[i].status = 0;

            // Devolve 1 unidade ao estoque do livro correspondente
            for (int j = 0; j < totallivros; j++) {
                if (acervo[j].id == id_livro_dev) {
                    acervo[j].quantidade++;
                    printf("\n[+] Livro '%s' devolvido com sucesso! [+]\n", acervo[j].titulo);
                    char evento [100];
                    sprintf(evento, "O livro %s foi devolvido pelo usuario %s!", acervo[j].titulo, usuario_logado->name);
                    data_log(evento);
                    break;
                }
            }
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("\n[!] Você não possui nenhum empréstimo ativo pendente para o livro ID %d! [!]\n", id_livro_dev);
    }

    printf("\nPressione [ENTER] para continuar...");
    getchar();
}
