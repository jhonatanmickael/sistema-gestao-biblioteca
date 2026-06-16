#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "emprestimo.h"
#include "usuario.h"
#include "livro.h"
#include "relatorios.h"
#include "menu.h"

int armazenar_livros();

// Inicializando as variáveis globais
Emprestimo controle_emprestimos[100];
int totalemprestimos = 0;

// Função para solicitar um livro emprestado (Por ID ou por Nome)
void solicitar_emprestimo() {
    int tipo_busca = 0;

    system("clear");
    exibir_cabecalho("-> PEGAR EMPRESTIMO <-");
    
    if (totalemprestimos >= 100) {
        system("clear");
        exibir_cabecalho("-> PEGAR EMPRESTIMO <-");
        printf("[!] Limite do sistema atingido! Não é possível realizar novos empréstimos. [!]\n");
        linha();
        printf("Pressione [ENTER] para voltar...\n");
        getchar();
        return;
    }

    printf("Como deseja selecionar o livro?\n");
    printf("1. Pelo ID\n");
    printf("2. Pelo Título\n");
    linha(); printf("-> ");

    // Le a opção inserida e ja verifica se oque foi digitado é um numero inteiro
    if (scanf("%d", &tipo_busca) != 1) {
        while (getchar() != '\n');
        system("clear");
        exibir_cabecalho("-> PEGAR EMPRESTIMO <-");
        printf("[!] Entrada inválida! Digite apenas números. [!]\n");
        linha();
        printf("Pressione [ENTER] para voltar...\n");
        getchar();
        return;
    }
    while (getchar() != '\n'); // Limpa o buffer

    int livro_index = -1;

    // emprestimo por id
    if (tipo_busca == 1) {
        int id_busca = 0;

        system("clear");
        exibir_cabecalho("-> PEGAR EMPRESTIMO <-");
        printf("Digite o ID do livro que deseja:\n");
        linha(); printf("-> ");

        // Le a opção inserida e ja verifica se foi inserido um numero inteiro
        if (scanf("%d", &id_busca) != 1) {
            while (getchar() != '\n'); // limpa o buffer
            system("clear");
            exibir_cabecalho("-> PEGAR EMPRESTIMO <-");
            printf("[!] ID inválido! [!]\n");
            linha();
            printf("Pressione [ENTER] para voltar...\n");
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
            system("clear");
            exibir_cabecalho("-> PEGAR EMPRESTIMO <-");
            printf("[!] Livro não encontrado ou inativo no sistema! [!]\n");
            linha();
            printf("Pressione [ENTER] para voltar...\n");
            getchar();
            return;
        }

    // pegar emprestimo pelo titulo
    } else if (tipo_busca == 2) {
        char termo_busca[100];

        system("clear");
        exibir_cabecalho("-> PEGAR EMPRESTIMO <-");
        printf("Digite o nome ou parte do título do livro:\n");
        linha(); printf("-> ");
        fgets(termo_busca, sizeof(termo_busca), stdin);
        termo_busca[strcspn(termo_busca, "\n")] = '\0'; // limpa o '\n' no final

        // vetor dinamico local para guardar os indices dos livros encontrados
        int indices_encontrados[100];
        int qtd_encontrados = 0;

        for (int i = 0; i < totallivros; i++) {
            if (acervo[i].active == 1 && strstr(acervo[i].titulo, termo_busca) != NULL) {
                indices_encontrados[qtd_encontrados] = i;
                qtd_encontrados++;
            }
        }

        if (qtd_encontrados == 0) {
            system("clear");
            exibir_cabecalho("-> PEGAR EMPRESTIMO <-");
            printf("[!] Nenhum livro ativo encontrado com o termo '%s'. [!]\n", termo_busca);
            linha();
            printf("Pressione [ENTER] para voltar...\n");
            getchar();
            return;
        } 
        
        // Se encontrou exatamente 1 livro, seleciona direto
        if (qtd_encontrados == 1) {
            livro_index = indices_encontrados[0];
        } 
        // Se encontrou mais de um, lista os livros para o usuário escolher pelo ID correspondente
        else {
            system("clear");
            exibir_cabecalho("-> PEGAR EMPRESTIMO <-");
            printf("%-5s | %-41s | %-30s\n", "ID", "TÍTULO", "AUTOR");
            linha();
            for (int i = 0; i < qtd_encontrados; i++) {
                int idx = indices_encontrados[i];
                printf("#%04d | %-41.41s | %-30.30s\n", acervo[idx].id, acervo[idx].titulo, acervo[idx].autor);            
            }
            linha();
            printf("Digite o ID do livro que deseja pegar emprestado:\n");
            linha(); printf("-> ");
            
            // Le a opção inserida e ja verifica se é um numero inteiro
            int id_escolhido = 0;
            if (scanf("%d", &id_escolhido) != 1) {
                while (getchar() != '\n'); // limpa o buffer
                system("clear");
                exibir_cabecalho("-> PEGAR EMPRESTIMO <-");
                printf("[!] Entrada inválida! Empréstimo cancelado. [!]\n");
                linha();
                printf("Pressione [ENTER] para voltar...\n");
                getchar();
                return;
            }
            while (getchar() != '\n'); // Limpa o buffer

            // valida se o ID escolhido está dentro da lista de encontrados
            for (int i = 0; i < qtd_encontrados; i++) {
                int idx = indices_encontrados[i];
                if (acervo[idx].id == id_escolhido) {
                    livro_index = idx;
                    break;
                }
            }

            if (livro_index == -1) {
                system("clear");
                exibir_cabecalho("-> PEGAR EMPRESTIMO <-");
                printf("[!] ID digitado não corresponde aos livros listados! [!]\n");
                linha();
                printf("Pressione [ENTER] para voltar...\n");
                getchar();
                return;
            }
        }

    } else {
        system("clear");
        exibir_cabecalho("-> PEGAR EMPRESTIMO <-");
        printf("[!] Opção de busca inválida! [!]\n");
        linha();
        printf("Pressione [ENTER] para voltar...\n");
        getchar();
        return;
    }

    // Processa a retirada
    if (acervo[livro_index].quantidade <= 0) {
        system("clear");
        exibir_cabecalho("-> PEGAR EMPRESTIMO <-");
        printf("[!] Desculpe, não há exemplares disponíveis de:\n");
        printf("    \"%s\" no estoque! [!]\n", acervo[livro_index].titulo);
        linha();
    } else {
        // Registra os dados do empréstimo ativo
        controle_emprestimos[totalemprestimos].id_emprestimo = totalemprestimos + 1;
        controle_emprestimos[totalemprestimos].id_usuario = usuario_logado->id;
        controle_emprestimos[totalemprestimos].id_livro = acervo[livro_index].id;
        controle_emprestimos[totalemprestimos].status = 1; // 1 significa Ativo

        // Decrementa o estoque do livro no acervo
        acervo[livro_index].quantidade--;
        totalemprestimos++;

        // Salva as alterações de estoque no disco
        armazenar_emprestimos();
        armazenar_livros();

        system("clear");
        exibir_cabecalho("-> PEGAR EMPRESTIMO <-");
        printf("[+] Empréstimo realizado com sucesso! [+]\n\n");
        printf("    > Livro: %s\n", acervo[livro_index].titulo);
        printf("    > Retirado por: %s\n", usuario_logado->name);
        linha();

        // criando o log pro evento
        char evento[100];
        snprintf(evento, sizeof(evento), "O usuario %s pegou o livro %s emprestado!", usuario_logado->name, acervo[livro_index].titulo);
        data_log(evento);
    }

    printf("Pressione [ENTER] para continuar...\n");
    getchar(); 
}

// Função para devolver um livro ativo baseado no ID do Livro
void devolver_livro() {
    int id_livro_dev = 0;
    system("clear");
    exibir_cabecalho("-> DEVOLVER LIVRO <-");
    printf("Digite o ID do LIVRO que você vai devolver:\n");
    linha(); printf("-> ");

    // Le e ja verifica se o usuario digitou um numero inteiro
    if (scanf("%d", &id_livro_dev) != 1) {
        while (getchar() != '\n'); // Limpa o buffer
        system("clear");
        exibir_cabecalho("-> DEVOLVER LIVRO <-");
        printf("[!] Entrada inválida! [!]\n");
        linha();
        printf("Pressione [ENTER] para voltar...\n");
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
                    
                    // Salva as alterações de estoque no disco
                    armazenar_emprestimos();
                    armazenar_livros();

                    system("clear");
                    exibir_cabecalho("-> DEVOLVER LIVRO <-");
                    printf("\n[+] Livro '%s' devolvido com sucesso! [+]\n", acervo[j].titulo);
                    linha();

                    // criando o log do evento
                    char evento [100];
                    snprintf(evento, sizeof(evento), "O livro %s foi devolvido pelo usuario %s!", acervo[j].titulo, usuario_logado->name);
                    data_log(evento);
                    break;
                }
            }
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        system("clear");
        exibir_cabecalho("-> PEGAR EMPRESTIMO <-");
        printf("[!] Você não possui nenhum empréstimo ativo pendente para o livro ID %d! [!]\n", id_livro_dev);
        linha();
    }

    printf("Pressione [ENTER] para continuar...\n");
    getchar();
}

// Função pra armazenas os emprestimos no arquivo emprestimos.dat
int armazenar_emprestimos() {
    FILE *arquivo = fopen("../data/emprestimos.dat", "wb");
    if (arquivo == NULL) {
        printf("Erro ao abrir arquivo de empréstimos para escrita!\n");
        return 0;
    }
    fwrite(controle_emprestimos, sizeof(Emprestimo), totalemprestimos, arquivo);
    fclose(arquivo);
    return 1;
}

// Função para ler o arquivo emrpestimos.dat
int carregar_emprestimos() {
    FILE *arquivo = fopen("../data/emprestimos.dat", "rb");
    if (arquivo == NULL) {
        return 0; // o arquivo ainda n existe na primeira execução
    }
    int lidos = 0;
    while (fread(&controle_emprestimos[lidos], sizeof(Emprestimo), 1, arquivo) == 1) {
        lidos++;
    }
    totalemprestimos = lidos;
    fclose(arquivo);
    return lidos;
}

// Função para listar os emprestimos
void listar_emprestimos() {
    system("clear");
    exibir_cabecalho("-> MEUS EMPRESTIMOS <-");

    int encontrados = 0;

    // percorre a lista de emprestimos e separa as que pertence ao id de usuario logado
    for (int i = 0; i < totalemprestimos; i++) {
        if (controle_emprestimos[i].id_usuario == usuario_logado->id
            && controle_emprestimos[i].status == 1) {
                
            char titulo_livro[100] = "Livro não encontrado ou removido";
            for (int j = 0; j < totallivros; j++) {
                if (acervo[j].id == controle_emprestimos[i].id_livro) {
                    snprintf(titulo_livro, sizeof(titulo_livro), "%s", acervo[j].titulo);
                    break;
                }
            }

            printf("ID Livro: %d\n", controle_emprestimos[i].id_livro);
            printf("Livro: %s\n", titulo_livro);
            linha();
            encontrados++;
        }
    }

    if (encontrados == 0) {
        printf("[!] Você não possui empréstimos pendentes. [!]\n");
    } else {
        printf("Total de livros pendentes: %d\n", encontrados);
    }
    linha();
    printf("Pressione [ENTER] para voltar...");
    getchar(); 
}