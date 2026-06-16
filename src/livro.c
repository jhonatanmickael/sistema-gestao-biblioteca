#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "livro.h"
#include "menu.h"

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

// lista os livros ativos no sistema
void listar_livros() {
    system("clear");
    exibir_cabecalho("-> ACERVO BIBLIOTECA <-");

    int exibidos = 0;
    printf("%-4s | %-28s | %-25s | %-5s\n", "ID", "TÍTULO", "AUTOR", "QTD");
    linha();

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

    linha();
    printf("Pressione [ENTER] para voltar ao menu...");
    getchar(); 
}
// Cadastro de novos livros (Opção exclusiva do Admin/Root)
void cadastrar_livro() {
    system("clear");
    exibir_cabecalho("-> CADASTRAR NOVO LIVRO <-");
    if (totallivros >= 100) {
        printf("[!] Acervo cheio! Não é possível cadastrar mais livros. [!]\n");
        linha();
        printf("Pressione [ENTER] para voltar...");
        getchar();
        return;
    }

    Livro novo;
    novo.id = totallivros + 1; // Id sequencial

    // Coletando o nome do livro
    printf("Título do livro:\n");
    linha(); printf("-> ");
    fgets(novo.titulo, sizeof(novo.titulo), stdin);
    novo.titulo[strcspn(novo.titulo, "\n")] = '\0'; // tirando o '\n' final

    // Coletando o autor do livro
    system("clear");
    exibir_cabecalho("-> CADASTRAR NOVO LIVRO <-");
    printf("Título do Livro: %s\n", novo.titulo);
    linha();
    printf("Autor:\n");
    linha(); printf("-> ");
    fgets(novo.autor, sizeof(novo.autor), stdin);
    novo.autor[strcspn(novo.autor, "\n")] = '\0'; // tirando o '\n' do final

    // Coletando o genero do livro
    system("clear");
    exibir_cabecalho("-> CADASTRAR NOVO LIVRO <-");
    printf("Título do Livro: %s\n", novo.titulo);
    printf("Autor: %s\n", novo.autor);
    linha();
    printf("Gênero:\n");
    linha(); printf("-> ");
    fgets(novo.genero, sizeof(novo.genero), stdin);
    novo.genero[strcspn(novo.genero, "\n")] = '\0'; // tirando o '\n' do final

    // Coletando a quantidade de cópias do livro
    system("clear"); // Adicionado para limpar a tela e manter o padrão visual
    exibir_cabecalho("-> CADASTRAR NOVO LIVRO <-");
    printf("Título do Livro: %s\n", novo.titulo);
    printf("Autor: %s\n", novo.autor);
    printf("Gênero: %s\n", novo.genero);
    linha();
    printf("Quantidade de exemplares:\n");
    linha(); printf("-> ");
    
    if (scanf("%d", &novo.quantidade) != 1 || novo.quantidade < 0) {
        while (getchar() != '\n'); // limpa o buffer
        system("clear");
        exibir_cabecalho("-> CADASTRO DE LIVRO <-");
        printf("[!] Erro: Quantidade inválida! Cadastro cancelado. [!]\n");
        linha();
        printf("Pressione [ENTER] para voltar... ");
        getchar();
        return;
    }
    while (getchar() != '\n'); // limpa o buffer

    novo.active = 1; // O livro cadastrado entra como ativo

    acervo[totallivros] = novo;
    totallivros++;
    armazenar_livros();

    // tela de sucesso
    system("clear");
    exibir_cabecalho("-> CADASTRAR NOVO LIVRO <-");
    printf("[+] LIVRO CADASTRADO COM SUCESSO! [+]\n");
    linha();
    printf("> ID do Livro:   #%03d\n", novo.id);
    printf("> Título:        %s\n", novo.titulo);
    printf("> Autor:         %s\n", novo.autor);
    printf("> Gênero:        %s\n", novo.genero);
    printf("> Exemplares:    %d\n", novo.quantidade);
    linha();
    printf("Pressione [ENTER] para voltar...");
    getchar();
}

// Função feita para buscar livro pelo id ou nome
void buscar_livro() {
    int tipo_busca = 0;

    system("clear");
    exibir_cabecalho("-> BUSCAR LIVRO <-");
    printf("Como deseja buscar o livro?\n");
    printf("1. Buscar por ID\n");
    printf("2. Buscar pelo Título\n");
    linha(); printf("-> ");

    // Seletor para escolher se vai buscar por id ou nome
    if (scanf("%d", &tipo_busca) != 1) {
        while (getchar() != '\n'); // Limpa o buffer
        system("clear");
        exibir_cabecalho("-> BUSCAR LIVRO <-");
        printf("[!] Entrada inválida! Digite apenas números. [!]\n");
        linha();
        printf("Pressione [ENTER] para voltar...");
        getchar();
        return;
    }
    while (getchar() != '\n'); // Limpa o buffer

    // busca pelo id
    if (tipo_busca == 1) {
        int id_busca = 0;
        system("clear");
        exibir_cabecalho("-> BUSCAR LIVRO <-");
        printf("Digite o ID do livro:\n");
        linha(); printf("-> ");

        // le a entrada e ja olha se é valida
        if (scanf("%d", &id_busca) != 1) {
            while (getchar() != '\n');
            system("clear");
            exibir_cabecalho("-> BUSCAR LIVRO <-");
            printf("[!] ID inválido! Digite apenas números![!]\n");
            linha();
            printf("Pressione [ENTER] para voltar...");
            getchar();
            return;
        }
        while (getchar() != '\n'); // Limpa o buffer

        system("clear");
        exibir_cabecalho("-> RESULTADO DA BUSCA <-");
        printf("%-5s | %-32s | %-25s | %-5s\n", "ID", "TÍTULO", "AUTOR", "QTD");
        linha();

        int encontrado = 0; 
        for (int i = 0; i < totallivros; i++) {
            if (acervo[i].id == id_busca && acervo[i].active == 1) {
                printf("#%04d | %-32.32s | %-25.25s | %-5d\n",
                    acervo[i].id, 
                    acervo[i].titulo, 
                    acervo[i].autor, 
                    acervo[i].quantidade);
                encontrado = 1;
                break;
            }
        }

        if (!encontrado) {
            printf("[!] Nenhum livro ativo encontrado com o ID %d. [!]\n", id_busca);
        }
        linha();

    // buscar pelo titulo
    } else if (tipo_busca == 2) {
        char termo_busca[100];
        system("clear");
        exibir_cabecalho("-> BUSCAR LIVRO <-");
        printf("Digite o termo ou nome do livro:\n");
        linha(); printf("-> ");
        // coletando o titulo inserido
        fgets(termo_busca, sizeof(termo_busca), stdin);
        termo_busca[strcspn(termo_busca, "\n")] = '\0';

        //Resultado da busca
        system("clear");
        exibir_cabecalho("-> RESULTADO DA BUSCA <-");
        printf("%-5s | %-32s | %-25s | %-5s\n", "ID", "TÍTULO", "AUTOR", "QTD");
        linha();

        int encontrados = 0;
        for (int i = 0; i < totallivros; i++) {
            // verifica se termo_busca é o titulo do livro
            if (acervo[i].active == 1 && strstr(acervo[i].titulo, termo_busca) != NULL) {
                printf("#%04d | %-32.32s | %-25.25s | %-5d\n", 
                       acervo[i].id, 
                       acervo[i].titulo, 
                       acervo[i].autor, 
                       acervo[i].quantidade);
                encontrados++;
            }
        }

        if (encontrados == 0) {
            printf("[!] Nenhum livro encontrado com o termo '%s'. [!]\n", termo_busca);
        }
        linha();

    } else {
        system("clear");
        exibir_cabecalho("-> BUSCAR LIVRO <-");
        printf("[!] Opção de busca inválida! [!]\n");
        linha();
        printf("Pressione [ENTER] para continuar...");
        getchar();
        return; 
    }

    printf("Pressione [ENTER] para voltar ao menu...");
    getchar();
}

// Permite ao administrador editar os dados de um livro ativo
void editar_livro() {
    int id_busca = 0;
    int indice = -1;
    char entrada[20];
    int opcao_campo = -1;

    system("clear");
    exibir_cabecalho("-> EDITAR LIVRO <-");
    printf("Digite o ID do livro que deseja editar:\n");
    linha(); printf("-> ");

    if (scanf("%d", &id_busca) != 1) {
        while (getchar() != '\n'); // limpa o buffer
        system("clear");
        exibir_cabecalho("-> EDITAR LIVRO <-");
        printf("[!] ID inválido! Digite apenas números. [!]\n");
        linha();
        printf("Pressione [ENTER] para voltar...");
        getchar();
        return;
    }
    while (getchar() != '\n'); // limpar o buffer

    for (int i = 0; i < totallivros; i++) {
        if (acervo[i].id == id_busca && acervo[i].active == 1) {
            indice = i;
            break;
        }
    }

    if (indice == -1) {
        system("clear");
        exibir_cabecalho("-> EDITAR LIVRO <-");
        printf("[!] Livro não encontrado ou removido! [!]\n");
        linha();
        printf("Pressione [ENTER] para voltar...");
        getchar();
        return;
    }

    // loop pra escolher oq quer editar
    while (1) {
        system("clear");
        exibir_cabecalho("-> EDITAR LIVRO <-");
        printf("[+] Livro Selecionado [+]\n");
        linha();
        printf("> ID: %d\n", acervo[indice].id);
        printf("> 1. Título:     %s\n", acervo[indice].titulo);
        printf("> 2. Autor:      %s\n", acervo[indice].autor);
        printf("> 3. Gênero:     %s\n", acervo[indice].genero);
        printf("> 4. Quantidade: %d\n", acervo[indice].quantidade);
        printf("> 0. Voltar\n");
        linha();    
        printf("O que deseja alterar? (0-4):\n");
        linha(); printf("-> ");

        if (scanf("%d", &opcao_campo) != 1) {
            while (getchar() != '\n');
            system("clear");
            exibir_cabecalho("-> EDITAR LIVRO <-");
            printf("[!] Entrada inválida! Digite um número de 0 a 4. [!]\n");
            linha();
            printf("Pressione [ENTER] para continuar...");
            getchar();
            continue;
        }
        while (getchar() != '\n'); // Limpa o buffer

        if (opcao_campo == 0) {
            break; // sai do loop e vai para a parte de salvar
        }

        // executa a alteração com base na escolha
        // muda o titulo
        if (opcao_campo == 1) {
            system("clear");
            exibir_cabecalho("-> ALTERAR TÍTULO <-");
            printf("Título Atual: %s\n", acervo[indice].titulo);
            linha();
            printf("Digite o Novo Título:\n");
            linha(); printf("-> ");
            fgets(acervo[indice].titulo, sizeof(acervo[indice].titulo), stdin);
            acervo[indice].titulo[strcspn(acervo[indice].titulo, "\n")] = '\0';
            
        } 
        // muda o autor
        else if (opcao_campo == 2) {
            system("clear");
            exibir_cabecalho("-> ALTERAR AUTOR <-");
            printf("Autor Atual: %s\n", acervo[indice].autor);
            linha();
            printf("Digite o Novo Autor:\n");
            linha(); printf("-> ");
            fgets(acervo[indice].autor, sizeof(acervo[indice].autor), stdin);
            acervo[indice].autor[strcspn(acervo[indice].autor, "\n")] = '\0';
            
        } 
        // muda o genero
        else if (opcao_campo == 3) {
            system("clear");
            exibir_cabecalho("-> ALTERAR GÊNERO <-");
            printf("Gênero Atual: %s\n", acervo[indice].genero);
            linha();
            printf("Digite o Novo Gênero:\n");
            linha(); printf("-> ");
            fgets(acervo[indice].genero, sizeof(acervo[indice].genero), stdin);
            acervo[indice].genero[strcspn(acervo[indice].genero, "\n")] = '\0';
            
        } 
        // muda a quantidade
        else if (opcao_campo == 4) {
            int nova_quantidade = 0;
            system("clear");
            exibir_cabecalho("-> ALTERAR QUANTIDADE <-");
            printf("Quantidade Atual: %d\n", acervo[indice].quantidade);
            linha();
            printf("Digite a Nova Quantidade:\n");
            linha(); printf("-> ");
            fgets(entrada, sizeof(entrada), stdin);

            if (sscanf(entrada, "%d", &nova_quantidade) != 1 || nova_quantidade < 0) {
                system("clear");
                exibir_cabecalho("-> EDITAR USUÁRIO <-");
                printf("[!] Quantidade inválida! Alteração rejeitada. [!]\n");
                linha();
                printf("Pressione [ENTER] para continuar...");
                getchar();
            } else {
                acervo[indice].quantidade = nova_quantidade;
            }
        } 
        // tratamento de erro
        else {
            system("clear");
            exibir_cabecalho("-> EDITAR USUÁRIO <-");
            printf("[!] Opção inválida! Escolha de 0 a 4. [!]\n");
            linha();
            printf("Pressione [ENTER] para continuar...");
            getchar();
        }
    }

    // Fora do loop: Salva as alterações feitas no arquivo
    system("clear");
    exibir_cabecalho("-> SALVANDO ALTERAÇÕES <-");
    if (armazenar_livros()) {
        printf("[+] Alterações salvas com sucesso no banco de dados! [+]\n");
    } else {
        printf("[!] Erro crítico ao salvar as alterações no arquivo! [!]\n");
    }

    linha();
    printf("Pressione [ENTER] para voltar ao menu...");
    getchar();
}

// remove o livro, active = 0
void remover_livro() {
    int id_busca = 0;
    int indice = -1;
    char confirmacao = 'n';

    system("clear");
    exibir_cabecalho("-> REMOVER LIVRO <-");
    printf("Digite o ID do livro que deseja remover:\n");
    linha(); printf("-> ");

    if (scanf("%d", &id_busca) != 1) {
        while (getchar() != '\n');
        system("clear");
        exibir_cabecalho("-> REMOVER LIVRO <-");
        printf("[!] ID inválido! [!]\n");
        linha();
        printf("Pressione [ENTER] para voltar...");
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
        system("clear");
        exibir_cabecalho("-> REMOVER LIVRO <-");
        printf("[!] Livro não encontrado ou já removido! [!]\n");
        linha();
        printf("Pressione [ENTER] para voltar...");
        getchar();
        return;
    }

    system("clear");
    exibir_cabecalho("-> REMOVER LIVRO <-");
    printf("[+] Livro encontrado! [+]\n");
    linha();
    printf("> ID: %d\n", acervo[indice].id);
    printf("> Título: %s\n", acervo[indice].titulo);
    printf("> Autor: %s\n", acervo[indice].autor);
    printf("> Quantidade: %d\n", acervo[indice].quantidade);
    linha();
    printf("Tem certeza que deseja remover este livro? (s/n)\n");
    linha(); printf("-> ");
    scanf(" %c", &confirmacao);
    while (getchar() != '\n'); // limpa o buffer

    if (confirmacao == 's' || confirmacao == 'S') {
        acervo[indice].active = 0;
        if (armazenar_livros()) {
            system("clear");
            exibir_cabecalho("-> REMOVER LIVRO <-");
            printf("[+] Livro removido com sucesso! [+]\n");
            linha();
        } else {
            system("clear");
            exibir_cabecalho("-> REMOVER LIVRO <-");
            printf("[!] Erro ao salvar remoção do livro! [!]\n");
            linha();    
        }
    } else {
        system("clear");
        exibir_cabecalho("-> REMOVER LIVRO <-");
        printf("[i] Remoção cancelada. [i]\n");
        linha();
    }

    printf("Pressione [ENTER] para continuar...");
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