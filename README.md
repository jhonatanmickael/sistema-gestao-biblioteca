# Sistema de Gestão de Biblioteca

Projeto Final de Laboratório e Prática de Programação 1 desenvolvido como requisito avaliativo do Curso de Bacharelado em Sistemas de Informação da Universidade Federal de Alagoas (UFAL).

## Contexto Acadêmico

* Instituição: Universidade Federal de Alagoas (UFAL)
* Campus: Campus Arapiraca (Sede Penedo)
* Curso: Bacharelado em Sistemas de Informação
* Disciplina: Programação 1
* Orientação: Professor Thyago Tenório e Professor Jario Jose

## Sobre o Projeto

O Sistema de Gestão de Biblioteca é uma aplicação de linha de comando desenvolvida inteiramente na linguagem C. O software foi projetado utilizando o conceito de modularização para simular de forma fiel as regras de negócio e operações cotidianas de uma biblioteca universitária.

O projeto aplica em sua construção os seguintes conceitos técnicos fundamentais:
* Estrutura de Dados: Armazenamento e manipulação de registros em memória por meio de arranjos (arrays) baseados em estruturas (structs).
* Persistência de Dados Binária: Gravação e leitura automatizada de dados estruturados utilizando arquivos com extensão .dat.
* Subsistema de Logs: Rastreamento cronológico de eventos e operações da aplicação gravados em modo de acréscimo em arquivo de texto (.log).
* Resiliência de Inicialização: Mecanismos de tratamento de ponteiros para garantir a auto-recriação automática dos arquivos de persistência caso sejam removidos do ambiente local.

## Estrutura de Diretórios

A árvore do diretório do projeto está organizada seguindo os padrões recomendados para a linguagem C, separando definições de cabeçalhos, códigos de implementação e os arquivos físicos de dados:

```text 
    sistema-gestao-biblioteca/
    │
    ├── .gitignore             # Ignora binários e logs locais no Git
    ├── CMakeLists.txt         # Configuração de automação de build do CMake
    ├── README.md              # Documentação oficial do projeto
    │
    ├── include/               # Arquivos de cabeçalho (.h) - Protótipos e Structs
    │   ├── emprestimo.h       # Estrutura de empréstimos e protótipos de locação
    │   ├── livro.h            # Estrutura de livros e protótipos de acervo
    │   ├── menu.h             # Protótipos de navegação e interfaces do terminal
    │   ├── relatorios.h       # Protótipo de auditoria e histórico do sistema
    │   └── usuario.h          # Estrutura de usuários e protótipos de autenticação
    │
    ├── src/                   # Código-fonte funcional (.c) - Lógica de Negócio
    │   ├── emprestimo.c       # Regras de empréstimos, devoluções e listagens
    │   ├── livro.c            # Controle de estoque, cadastro, edição e remoção de livros
    │   ├── main.c             # Entrada do programa, carga de dados e inicialização
    │   ├── menu.c             # Implementação visual dos menus e fluxos de navegação
    │   ├── relatorios.c       # Manipulação de registros e logs no arquivo de texto
    │   └── usuario.c          # Autenticação, controle de sessão e cadastro de usuários
    │
    └── data/                  # Diretório reservado para persistência de dados
        ├── .gitkeep           # Preserva a pasta vazia no controle de versão do Git
        ├── usuarios.dat       # Base de dados binária dos usuários do sistema
        ├── livros.dat         # Base de dados binária do acervo de livros
        ├── emprestimos.dat    # Registro binário das operações de empréstimos
        └── historico.log      # Arquivo de texto com o histórico de logs do sistema
```

## Como Compilar e Executar (Via CMake)

O projeto utiliza o CMake para a automação de compilação, permitindo o gerenciamento isolado de arquivos binários intermediários (out-of-source build). Certifique-se de ter as ferramentas básicas instaladas antes de iniciar.

## 1. Ambiente Linux (Arch Linux, Ubuntu, etc.)

**Pré-requisitos:** O pacote `cmake` e o compilador `gcc` (contido no grupo `base-devel`). No Arch Linux, instale via terminal:
```bash
sudo pacman -S cmake base-devel
```

### Criar o diretório para os arquivos binários
```bash
mkdir build
```

### Entrar no diretório e configurar o ambiente com o CMake
```bash
cd build && cmake ..
```

### Compilar o código-fonte gerando o executável
```bash
make
```
### Executar a aplicação
```bash
./sistema_gest_o_biblioteca
```

## 2. Ambiente Windows (Prompt de Comando ou PowerShell)

**Pré-requisitos:** O `CMake` para Windows instalado e configurado nas variáveis de ambiente (PATH), além de um compilador como o `GCC` (via MinGW/MSYS2) ou as ferramentas de build do `Visual Studio`.

**Passo a passo para compilação:**
### Criar o diretório para os arquivos binários
```powershell
mkdir build
```

### Entrar no diretório e configurar o ambiente com o CMake
```pwoershell
cd build
cmake ..
```
### Compilar o projeto de forma multiplataforma utilizando o próprio CMake
```powershell
cmake --build .
```
### Executar a aplicação (o executável será gerado dentro da pasta Debug ou Release)
```powershell
.\Debug\sistema_gest_o_biblioteca.exe
```

## Credenciais de Inicialização Padrão

Para o primeiro acesso ao sistema, a aplicação conta com uma conta de administrador (root) pré-configurada diretamente na lógica de inicialização para permitir o gerenciamento inicial de usuários, livros e empréstimos:

* **Login:** `root`
* **Senha:** `root123`

> ⚠️ **Nota de Segurança:** Recomenda-se a alteração das credenciais padrão ou o cadastro de um novo operador com privilégios administrativos assim que o sistema for inicializado pela primeira vez no ambiente local.

## Funcionalidades do Sistema

A aplicação é dividida em módulos independentes e complementares, acessíveis de acordo com o nível de privilégio do usuário autenticado:

### 1. Módulo de Usuários
* **Cadastro de Operadores:** Inclusão de novos usuários com definição de papéis (Administrador ou Atendente).
* **Controle de Acesso:** Tela de login com mascaramento de senha e validação de credenciais contra a persistência binária.
* **Listagem e Busca:** Visualização de todos os operadores cadastrados no sistema para auditoria interna.

### 2. Módulo de Livros
* **Catálogo Técnico:** Cadastro de títulos contendo informações cruciais como Título, Autor, Ano de Publicação e Quantidade de Exemplares Disponíveis.
* **Atualização de Estoque:** Permite alterar os dados de um livro ou ajustar a quantidade de cópias na biblioteca.
* **Consulta Rápida:** Busca direcionada por código ou título para verificar a disponibilidade imediata de um exemplar.

### 3. Módulo de Empréstimos
* **Fluxo de Saída:** Registro de novos empréstimos vinculando o código do livro ao operador/usuário solicitante, com atualização imediata do status do livro.
* **Fluxo de Retorno (Devolução):** Baixa manual no sistema para registrar a entrega do exemplar, devolvendo a cópia ao estoque disponível na biblioteca.

### 4. Módulo de Relatórios e Auditoria
* **Logs do Sistema (`.log`):** Registro cronológico em tempo real de todas as ações importantes (logins, cadastros, alterações e exclusões).
* **Estatísticas Gerenciais:** Telas de visualização consolidadas com o total de livros, usuários ativos e empréstimos pendentes.

## Persistência de Dados e Segurança

Para garantir a integridade das informações e a rastreabilidade das operações realizadas no sistema, a aplicação utiliza mecanismos de persistência em arquivos físicos e auditoria automatizada:

### 1. Armazenamento Binário (`data/*.dat`)
Diferente de arquivos de texto comuns, os dados de usuários, livros e empréstimos são gravados diretamente em formato binário. Isso oferece:
* **Performance:** Leituras e escritas diretas de estruturas (`structs`) na memória para o disco.
* **Segurança Local:** Impede que os arquivos de dados sejam lidos ou alterados facilmente por editores de texto convencionais sem passar pelas validações do programa.

### 2. Arquivos de Log (`data/historico.log`)
Todas as atividades críticas do sistema disparam uma rotina de auditoria que grava informações cronológicas no arquivo de log:
* **Rastreabilidade:** Registro de quem realizou a ação (ex: login de administrador, cadastro de livro, devolução de empréstimo) acompanhado do carimbo de data e hora.
* **Persistência Segura:** Os logs utilizam o modo de abertura *append* (`a`), garantindo que os registros antigos nunca sejam sobrescritos, apenas incrementados.

## Contribuição e Autores

Este projeto foi desenvolvido como parte das atividades acadêmicas do curso de Sistemas de Informação na **Universidade Federal de Alagoas (UFAL)**. 

Desenvolvido com dedicação por:
* **Jhonatan Mickael** — [*jhonatanmickael*](https://github.com/jhonatanmickael)
* **Maximus Eduardo** — [*sumixaM-Eduardo*](https://github.com/sumixaM-Eduardo)
* **Cauet Remigio** — [*cauergss*](https://github.com/cauergss)
* **Luis Felipe** — [*Felipemachado292*](https://github.com/Felipemachado292)
---
Sinta-se à vontade para clonar, testar o código e sugerir melhorias abrindo uma *Issue* ou um *Pull Request* no repositório! 🚀