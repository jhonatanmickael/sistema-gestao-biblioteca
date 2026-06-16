#include "usuario.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "relatorios.h"
#include "menu.h"

Usuario armazenar[100]; // maximo de contas criadas
Usuario *usuario_logado = NULL; // forçando o ponteiro a iniciar desconectado de uma conta

int totalusuarios = 0;

// definindo o id 1 para uma conta root
void inicializar_sistema () {
    armazenar[0].id = 1;
    strcpy(armazenar[0].username, "root");
    strcpy(armazenar[0].name, "root");
    strcpy(armazenar[0].password, "root123");
    armazenar[0].type = 1; // 1: conta para adm. 2: conta comum
    armazenar[0].active = 1; // conta ativa
    totalusuarios = 1; // sistema ja começa com 1 usuario

    armazenar_usuarios(&armazenar[0]);
}

// tela de cadastro de usuario
int cadastro() {
    char username_auth[50];

    // verifica se o sistema estorou o limite de usuarios criados
    if (limitar_usuarios() == 0) {
        return 0;
    }

    // grande printf da tela de cadastro e usuario
    system("clear"); 
    exibir_cabecalho("-> CADASTRO DE USUÁRIO <-");
    printf("Digite seu nome completo:\n");
    linha();
    printf("-> ");
    
    // coleta o nome completo inserido
    fgets(armazenar[totalusuarios].name, 50, stdin);
    armazenar[totalusuarios].name[strcspn(armazenar[totalusuarios].name, "\n")] = '\0'; // limpa o '\n' no final

    // Se nao inserir nada ele da erro
    if (campo_vazio(armazenar[totalusuarios].name)) {
        exibir_cabecalho("-> CADASTRO DE USUÁRIO <-");
        printf("[!] O nome nao pode ser vazio! [!]\n");
        linha();
        printf("\nPressione [ENTER] para voltar...");
        getchar();
        return 0;
    }
    system("clear");
    exibir_cabecalho("-> CADASTRO DE USUÁRIO");
    printf("Nome completo: %s\n", armazenar[totalusuarios].name);
    linha();
    printf("Digite seu nome de usuário:\n");
    linha();
    printf("-> ");

    // coleta o username inserido
    fgets(username_auth, 50, stdin);
    username_auth[strcspn(username_auth, "\n")] = '\0'; // limpa o '\n' final

    // verifica se o username inserido é valido
    if (campo_vazio(username_auth) || validar_username(username_auth) == 0) {
        exibir_cabecalho("-> CADASTRO DE USUÁRIO");
        printf("[!] Nome de usuário inválido ou já em uso! [!]\n");
        linha();
        printf("Pressione [ENTER] para voltar...");
        getchar();
        return 0;
    }
    strcpy(armazenar[totalusuarios].username, username_auth);

    system("clear");
    exibir_cabecalho("-> CADASTRO DE USUÁRIO <-");
    printf("Nome completo: %s\n", armazenar[totalusuarios].name);
    printf("Nome de usuário: %s\n", armazenar[totalusuarios].username);
    linha();
    printf("Digite a senha para a conta:\n");
    linha();
    printf("-> ");

    // coleta a senha inserida
    fgets(armazenar[totalusuarios].password, 50, stdin);
    armazenar[totalusuarios].password[strcspn(armazenar[totalusuarios].password, "\n")] = '\0';

    // se deixar o campo vazio ele da erro
    if (campo_vazio(armazenar[totalusuarios].password)) {
        exibir_cabecalho("-> CADASTRO DE USUÁRIO <-");
        printf("[!] A senha nao pode ser vazia! [!]\n");
        linha();
        printf("Pressione [ENTER] para voltar...");
        getchar();
        return 0;
    }

    // libera a opção de escolher se vai ser conta comum ou conta de admin
    // essa opção so libera se estiver logado em uma conta de administrador e selecionar pra cadastrar nova conta
    if (usuario_logado != NULL && usuario_logado->type == 1) {
        int tipo_escolhido = 0;
        do {
            system("clear");
            exibir_cabecalho("-> CADASTRO DE USUÁRIO <-");
            printf("Nome completo: %s\n", armazenar[totalusuarios].name);
            printf("Nome de usuário: %s\n", armazenar[totalusuarios].username);
            linha();
            printf("Escolha o nível de acesso da conta:\n");
            printf("1. Administrador\n2. Leitor Comum\n");
            linha();
            printf("-> ");

            // le e ja verifica se oque foi inserido é valido
            if (scanf("%d", &tipo_escolhido) != 1) {
                while (getchar() != '\n'); // limpa o buffer
                tipo_escolhido = -1;
            } else {
                while (getchar() != '\n'); // limpa o buffer
            }

            if (tipo_escolhido < 1 || tipo_escolhido > 2) {
                exibir_cabecalho("-> CADASTRO DE USUÁRIO <-");
                printf("[!] Opção inválida! Escolha 1 ou 2. [!]\n");
            }
        } while (tipo_escolhido < 1 || tipo_escolhido > 2);
        
        armazenar[totalusuarios].type = tipo_escolhido;
    } else {
        // Cadastro comum vindo da tela inicial sem login
        armazenar[totalusuarios].type = 2; 
    }

    // Configura o restante das propriedades do usuário
    armazenar[totalusuarios].id = totalusuarios + 1;
    armazenar[totalusuarios].active = 1; // conta ativa

    // armazena as informações inseridas no arquivo binário
    if (armazenar_usuarios(&armazenar[totalusuarios])) {
        // gera o log do evento
        char log_msg[100];
        snprintf(log_msg, sizeof(log_msg), "Cadastrou o usuário '%s' como %s", 
                 armazenar[totalusuarios].username, (armazenar[totalusuarios].type == 1 ? "ADM" : "Leitor Comum"));
        data_log(log_msg);

        // grande printf pra mostrar os dados da nova conta cadastrada
        system("clear");
        exibir_cabecalho("-> CADASTRO DE USUÁRIO <-");
        printf("  [i] Detalhes da nova credencial no sistema:\n");
        linha();
        printf("  > ID do Usuário:   #%03d\n", totalusuarios + 1);
        printf("  > Nome Completo:   %s\n", armazenar[totalusuarios].name);
        printf("  > Nome de Usuário: %s\n", armazenar[totalusuarios].username);
        printf("  > Tipo de Conta:   %s\n", (armazenar[totalusuarios].type == 1 ? "Administrador" : "Leitor Comum"));
        printf("  > Status do Perfil: Ativo\n");
        printf("====================================================\n");
        printf("Pressione [ENTER] para continuar...");
        getchar();
        
        totalusuarios++;
    } else {
        system("clear");
        exibir_cabecalho("-> CADASTRO DE USUÁRIO <-");
        printf("[!] Erro crítico ao salvar no arquivo de dados. [!]\n");
        linha();
        printf("Pressione [ENTER] para continuar...");
        getchar();
    }

    return 1;
}

// Função pra fazer o login
int login() {
    char user_digitado[50], senha_digitada[50];

    // grande printf de iniciar sessao
    system("clear");
    exibir_cabecalho("-> INICIAR SESSÃO <-");
    printf("Nome de Usuário:\n");
    linha();
    printf("-> ");

    // coleta o nome de usuario
    fgets(user_digitado, 50, stdin);
    user_digitado[strcspn(user_digitado, "\n")] = '\0'; // limpa o '\n'

    // grande printf de iniciar sessao
    system("clear");
    exibir_cabecalho("-> INICIAR SESSÃO <-");
    printf("Nome de Usuário: %s\n", user_digitado);
    linha();
    printf("Digite sua senha:\n");
    linha();
    printf("-> ");

    // coleta a senha
    fgets(senha_digitada, 50, stdin);
    senha_digitada[strcspn(senha_digitada, "\n")] = '\0'; // limpa o '\n'

    //  olha um por um se o usuario existe e a senha corresponde a esse usuario
    for (int i = 0; i < totalusuarios; i++) {
        if (strcmp(armazenar[i].username, user_digitado) == 0 &&
            strcmp(armazenar[i].password, senha_digitada) == 0){

            // caso a conta esteja desativada
            if (validar_atividade(&armazenar[i]) == 0) {
                system("clear");
                exibir_cabecalho("-> INICIAR SESSÃO <-");
                printf("[!] Esta conta está desativada. [!]\n");
                linha();
                printf("Pressione [ENTER] para continuar...");
                getchar();
                return 0;
            }

            // salva a conta na sessao global ativa para usuario logado
            usuario_logado = &armazenar[i];

            // salva o log
            // 150 de tamanho para prevenir o estouro de string
            char evento[150];
            sprintf(evento, "O usuario %s fez login", armazenar[i].username);
            data_log(evento);

            system("clear");
            exibir_cabecalho("-> INICIAR SESSÃO <-");
            printf("\n");
            printf("01110   01110   111  001     01   01  01  01110   01110   011100\n");
            printf("01  01  01     01  01  01    01   01  01  01  01  01  01  01  01\n");
            printf("01110   01110  01  01  01    01   01  01  01  01  01  01  01  01\n");
            printf("01  01  01     01  01  01     01 01   01  01  01  01  01  01  01\n");
            printf("01110   01110  01  01  01      010    01  01  01  01110   011101\n");
            linha();
            printf("Bem-vindo de volta, %s!\n", armazenar[i].name);
            printf("Pressione [ENTER] para continuar...");
            getchar();

            return 1; // Se retornar 1 ent ele fez o login
        }
    }

    // se o usuario e senha não corresponderem ele aponta falha de login
    system("clear");
    exibir_cabecalho("-> INICIAR SESSÃO <-");
    printf("[!] Erro: Nome de Usuário ou senha incorretos.\n");
    linha();
    printf("Presione [ENTER] para continuar...");
    getchar();

    return 0; // N conseguiu fzr o login
}

// Função para listar todos os livros
void listagem () {
    system("clear");
    exibir_cabecalho("-> LISTA DE USUÁRIO <-");
    printf("%-4s | %-25s | %-20s | %-15s\n", "ID", "NOME", "NOME DE USUÁRIO", "ACESSO");   
    linha();
    // percorre um a um dos usuarios ativos
    for (int i = 0; i < totalusuarios; i++) {
        if (armazenar[i].active == 1) { 
            printf("#%03d | %-25.25s | %-20.20s | %-15s\n",
                armazenar[i].id,
                armazenar[i].name,
                armazenar[i].username,
                (armazenar[i].type == 1 ? "Administrador" : "Leitor Comum"));
        }
    }

    linha();
    printf("\nPressione [ENTER] para voltar ao menu...");
    getchar();
    system("clear");
}

// Verifica se um username ja existe
int validar_username (char *username2) {
    for (int i = 0; i < totalusuarios; i++) {
        if (strcmp(armazenar[i].username, username2) == 0){

            return 0; // ja existe um usuario com esse username
        }
    }
    return 1; // n existe um usuario com esse username
}

int armazenar_usuarios(Usuario *usuario) {

    FILE *arquivo = fopen("../data/usuarios.dat", "ab");

    if (arquivo == NULL) {
        printf("Arquivo não localizado!\n");
        return 0;
    }

    fwrite(usuario, sizeof(Usuario), 1, arquivo);

    fclose(arquivo);

    return 1;
}

int carregar_usuarios() {
    FILE *arquivo = fopen("../data/usuarios.dat", "rb");

    if (arquivo == NULL) {
        totalusuarios = 0;
        return 0; 
    }

    totalusuarios = 0;

    while (fread(&armazenar[totalusuarios], sizeof(Usuario), 1, arquivo) == 1) {
        totalusuarios++;
    }

    fclose(arquivo);

    return totalusuarios > 0;
}

int limitar_usuarios() {
    if (totalusuarios >= 100) {
        system("clear");
        exibir_cabecalho("-> ERRO <-");
        printf("[!] Limite máximo de usuários atingido. [!]\n");
        linha();
        printf("Não é possível cadastrar mais usuários.\n");
        linha();
        printf("Pressione [ENTER] para voltar...");
        getchar();
        return 0;
    }
    return 1;
}

int campo_vazio(char *texto) {
    for (int i = 0; texto[i] != '\0'; i++) {
        if (!isspace(texto[i])) {
            return 0;
        }
    }
    return 1;
}

int validar_atividade(Usuario *usuario) {
    if (usuario->active == 0) {
        return 0;
    }
    return 1;
}

// função de buscar usuario, função do painel de adm
void buscar_usuario() {
    int tipo_busca = 0;

    // grande printf da tela de buscar usuario
    system("clear");
    exibir_cabecalho("-> BUSCAR USUÁRIO <-");
    printf("Como deseja buscar o operador?\n");
    printf("1. Pelo ID\n");
    printf("2. Pelo Nome de Usuário\n");
    linha();
    printf("-> ");

    // coleta a opção escolhida e ja verifica se a entrada é valida
    if (scanf("%d", &tipo_busca) != 1) {
        while (getchar() != '\n'); // limpa o buffer
        system("clear");
        exibir_cabecalho("-> BUSCAR USUÁRIO <-");
        printf("[!] Entrada inválida! Digite apenas números. [!]\n");
        linha();
        printf("\nPressione [ENTER] para voltar...");
        getchar();
        return;
    }
    while (getchar() != '\n'); // limpa o buffer

    int indice_encontrado = -1;

    // busca por id
    if (tipo_busca == 1) {
        int id_busca = 0;

        system("clear");
        exibir_cabecalho("-> BUSCAR USUÁRIO <-");
        printf("Digite o ID que deseja buscar:\n");
        linha();
        printf("-> ");

        if (scanf("%d", &id_busca) != 1) {
            while (getchar() != '\n'); // limpa o buffer
            system("clear");
            exibir_cabecalho("-> BUSCAR USUÁRIO <-");
            printf("[!] ID inválido! [!]\n");
            linha();
            printf("Pressione [ENTER] para continuar...\n");
            linha();
            getchar();
            return;
        }

        while (getchar() != '\n'); // limpa o buffer

        // loop que procura um por um
        for (int i = 0; i < totalusuarios; i++) {
            if (armazenar[i].id == id_busca && armazenar[i].active == 1) {
                indice_encontrado = i;
                break;
            }
        }
    } 
    // busca pelo nome de usuario
    else if (tipo_busca == 2) {
        char username_busca[50];

        system("clear");
        exibir_cabecalho("-> BUSCAR USUÁRIO <-");
        printf("Digite o Nome de usuário que deseja buscar:\n");
        linha();

        // coleta o nome de usuario que for inserido
        fgets(username_busca, sizeof(username_busca), stdin);
        username_busca[strcspn(username_busca, "\n")] = '\0'; // remove o \n no final

        // busca um por um
        for (int i = 0; i < totalusuarios; i++) {
            if (strcmp(armazenar[i].username, username_busca) == 0 && armazenar[i].active == 1) {
                indice_encontrado = i;
                break;
            }
        }
    } 
    else {
        system("clear");
        exibir_cabecalho("-> BUSCAR USUÁRIO <-");
        printf("[!] Opção inválida! [!]\n");
        linha();
        printf("Pressione [ENTER] para continuar...\n");
        getchar();
        return;
    }

    // Exibe o resultado da busca
    system("clear");
    if (indice_encontrado != -1) {
        exibir_cabecalho("-> BUSCAR USUÁRIO <-");
        printf("[+] Usuário encontrado! [+]\n");
        linha();
        printf("ID:       %04d\n", armazenar[indice_encontrado].id);
        printf("Nome:     %s\n", armazenar[indice_encontrado].name);
        printf("Username: %s\n", armazenar[indice_encontrado].username);
        printf("Acesso:   %s\n", (armazenar[indice_encontrado].type == 1 ? "Administrador" : "Leitor Comum"));
        linha();
    } else {
        system("clear");
        exibir_cabecalho("-> BUSCAR USUÁRIO <-");
        printf("[!] Operador não localizado ou inativo no sistema. [!]\n");
        linha();
    }

    printf("Pressione [ENTER] para voltar...");
    getchar();
}

// função de editar usuário
void editar_usuario() {
    int id_busca = 0;

    // grande printf inicial da tela de editar usuário
    system("clear");
    exibir_cabecalho("-> EDITAR USUÁRIO <-");
    printf("Digite o ID do usuário que deseja editar:\n");
    linha(); printf("-> ");

    // coleta o id e ja verifica se a entrada é valida
    if (scanf("%d", &id_busca) != 1) {
        while (getchar() != '\n'); // limpa o buffer
        system("clear");
        exibir_cabecalho("-> EDITAR USUÁRIO <-");
        printf("[!] ID inválido! Digite apenas números. [!]\n");
        linha();
        printf("Pressione [ENTER] para voltar...");
        getchar();
        return;
    }
    while (getchar() != '\n'); // limpa o buffer

    int indice = -1;

    // Busca um por um em usuarios
    for (int i = 0; i < totalusuarios; i++) {
        if (armazenar[i].id == id_busca && armazenar[i].active == 1) {
            indice = i;
            break;
        }
    }

    // tela de usuario nao encontrado
    if (indice == -1) {
        system("clear");
        exibir_cabecalho("-> EDITAR USUÁRIO <-");
        printf("[!] Usuário não localizado ou inativo no sistema. [!]\n");
        linha();
        printf("Pressione [ENTER] para voltar...");
        getchar();
        return;
    }

    // tela de usuario root
    if (armazenar[indice].id == 1) {
        system("clear");
        exibir_cabecalho("-> EDITAR USUÁRIO <-");
        printf("[!] Segurança: O usuário 'root' não pode ser alterado. [!]\n");
        linha();
        printf("Pressione [ENTER] para voltar...");
        getchar();
        return;
    }

    // tela de usuario que esta logado
    if (armazenar[indice].id == usuario_logado->id) {
        system("clear");
        exibir_cabecalho("-> EDITAR USUÁRIO <-");
        printf("[!] Erro: Você não pode alterar ou remover seus próprios\n");
        printf("    dados por este painel administrativo. [!]\n");
        linha();
        printf("Pressione [ENTER] para voltar...");
        getchar();
        return;
    }

    // tela de modificação apos passar por todas verificações anteriores
    int opcao_mod = 0;

    // grande printf do painel de edicao
    system("clear");
    exibir_cabecalho("-> EDITAR USUÁRIO <-");
    printf("Nome:             %s\n", armazenar[indice].name);
    printf("Nome de Usuário:  %s\n", armazenar[indice].username);
    printf("Nivel de Acesso:  %s\n", (armazenar[indice].type == 1 ? "Administrador" : "Leitor Comum"));
    linha();
    printf("Selecione a operação desejada:\n");
    printf("1. Alterar Nome Completo\n");
    printf("2. Alterar Nível de Acesso\n");
    printf("3. Remover Usuário\n");
    printf("0. Cancelar e Voltar\n");
    linha(); printf("-> ");

    // coleta a opção escolhida e ja verifica se é valida
    if (scanf("%d", &opcao_mod) != 1) {
        while (getchar() != '\n'); // limpa o buffer

        system("clear");
        exibir_cabecalho("-> EDITAR USUÁRIO <-");
        printf("[!] Opção inválida! Digite apenas números. [!]\n");
        linha();
        printf("Pressione [ENTER] para voltar...");
        getchar();
        return;
    }
    while (getchar() != '\n'); // limpa o buffer

    char log_msg[150]; // vamos usar pra salvar a edição no relatorio

    // alterar nome, opção 1 do painel de edicao
    if (opcao_mod == 1) {
        char novo_nome[50];

        // grande printf da tela de alterar nome
        system("clear");
        exibir_cabecalho("-> ALTERAR NOME COMPLETO <-");
        printf("Nome atual: %s\n", armazenar[indice].name);
        linha();
        printf("Digite o novo Nome completo:\n");
        linha(); printf("-> ");
        
        // coleta o nome nome complet
        fgets(novo_nome, sizeof(novo_nome), stdin);
        novo_nome[strcspn(novo_nome, "\n")] = '\0'; // tira o '\n' do fim do nome

        // tratamento de erro caso tenha deixado o nome vazio
        if (campo_vazio(novo_nome)) {
            system("clear");    
            exibir_cabecalho("-> ALTERAR NOME COMPLETO <-");
            printf("\n[!] O nome não pode ser vazio! Operação cancelada. [!]\n");
            linha();
            printf("Pressione [ENTER] para voltar...");
            getchar();
            return;
        }

        // aq estamos salvando a alteração feita no nome da conta la no historico.log
        snprintf(log_msg, sizeof(log_msg), "Alterou o nome do usuario '%s' de '%s' para '%s'", 
                 armazenar[indice].username, armazenar[indice].name, novo_nome);
        
        // aq é onde realmente alteramos o antigo nome pelo novo
        strcpy(armazenar[indice].name, novo_nome);

    }  
    // alterar o nivel de acesso da conta
    else if (opcao_mod == 2) {
        int novo_tipo = 0;

        // grande printf da tela de alterar nivel de acesso da conta
        system("clear");
        exibir_cabecalho("-> ALTERAR NIVEL DE ACESSO <-");
        printf("Nome de Usuário: %s\n", armazenar[indice].username);
        printf("Acesso Atual:    %s\n", (armazenar[indice].type == 1 ? "Administrador" : "Leitor Comum"));
        linha();
        printf("Escolha o novo nível de acesso:\n");
        printf("1. Administrator\n");
        printf("2. Leitor Comum\n");
        linha();
        
        // coleta a opção escolhida e ja verific se é valida
        if (scanf("%d", &novo_tipo) != 1 || (novo_tipo < 1 || novo_tipo > 2)) {
            while (getchar() != '\n'); 
            system("clear");
            exibir_cabecalho("-> ALTERAR NIVEL DE ACESSO <-");
            printf("[!] Opção inválida! Nenhuma modificação salva. [!]    \n");
            printf("------------------------------------------------------\n");
            printf("\nPressione [ENTER] para voltar...");
            getchar();
            return;
        }
        while (getchar() != '\n'); // limpa o buffer

        // aq estamos armazenando o novo nivel de acesso
        armazenar[indice].type = novo_tipo;
        
        // aqui estamos salvando a mudança la no historico.log
        snprintf(log_msg, sizeof(log_msg), "Alterou o nível de acesso de '%s' para %s", 
                 armazenar[indice].username, (novo_tipo == 1 ? "ADM" : "Leitor Comum"));

    // apagar uma conta, opção 3 do painel de edição
    } else if (opcao_mod == 3) {
        char confirmacao = 'n';

        // grande printf da tela de remover usuario
        system("clear");
        exibir_cabecalho("-> REMOVER USUÁRIO <-");
        printf("Nome:             %s\n", armazenar[indice].name);
        printf("Nome de Usuário:  %s\n", armazenar[indice].username);
        printf("Nivel de Acesso:  %s\n", (armazenar[indice].type == 1 ? "Administrador" : "Leitor Comum"));
        linha();
        printf("Tem certeza que deseja remover o usuário? (s/n)\n");
        linha(); printf("-> ");

        scanf(" %c", &confirmacao); // coleta a opção escolhida
        while (getchar() != '\n'); // limpa o buffe

        // se digitou s ou S ele apaga
        if (confirmacao == 's' || confirmacao == 'S') {
            armazenar[indice].active = 0; // nosso metodo de apagar é desativando a conta

            // aq estamos salvando uma mensagem de remoção de usuario la no historico.log
            snprintf(log_msg, sizeof(log_msg), "Removeu o usuário '%s' do sistema", armazenar[indice].username);
        } 
        // se digitou n ou N ele cancela
        else if (confirmacao == 'n' || confirmacao == 'N') {
            // grande printf da tela de remover usuario
            system("clear");        
            exibir_cabecalho("-> REMOVER USUÁRIO <-");
            printf("[i] Remoção do usuário '%s' cancelada. [i]\n", armazenar[indice].username);
            linha();
            printf("Pressione [ENTER] para continuar...");
            getchar();
            return;
        }
        // tratamento para caso digite qualquer outra tecla inválida
        else {
            system("clear");            
            exibir_cabecalho("-> REMOVER USUÁRIO <-");
            printf("[!] Opção inválida! Operação cancelada. [!]\n");
            linha();
            printf("Pressione [ENTER] para voltar...");
            getchar();
            return;
        }

    // caso digitou uma opção invalida no submenu de gestao de usuarios
    } else {
        system("clear");
        exibir_cabecalho("-> EDITAR USUÁRIO <-");
        printf("[!] Operação cancelada. [!]\n");
        linha();
        printf("Pressione [ENTER] para voltar...");
        getchar();
        return;
    }

    // abrindo o arquivo usuarios.dat em escrita binaria
    FILE *arquivo = fopen("../data/usuarios.dat", "wb");

    // se der algum erro no arquivo ele volta pra o menu de gestão de usuario
    if (arquivo == NULL) return;

    // salvando tudo do vetor armazenar no arquivo aberto
    fwrite(armazenar, sizeof(Usuario), totalusuarios, arquivo);

    //fecha o arquivo
    fclose(arquivo);

    // Registra o log no histórico do sistema
    data_log(log_msg);

    // tela de sucesso
    system("clear");
    exibir_cabecalho("-> REMOVER USUÁRIO <-");
    if (opcao_mod == 3) {
        printf("[+] Conta deletada com sucesso [+]    \n");
    } else {
        printf("[+] Alterações salvas com sucesso [+] \n");
    }
    linha();
    printf("Pressione [ENTER] para voltar...");
    getchar();
}