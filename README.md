# Sistema de Biblioteca em C

Este projeto implementa um sistema de gerenciamento de biblioteca em C, utilizando uma estrutura de dados estática para armazenar informações sobre livros. O sistema permite realizar operações básicas de gerenciamento de livros, como inserção, remoção, busca e listagem, além de funcionalidades avançadas como empréstimo e devolução de livros.

## Estrutura do Projeto

O projeto é composto pelos seguintes arquivos:

- `biblioteca.h`: Contém as definições das estruturas de dados e protótipos das funções
- `biblioteca.c`: Implementa as funções de gerenciamento da biblioteca
- `main.c`: Contém o programa principal com a interface de usuário
- `biblioteca.dat`: Arquivo de dados para persistência das informações

<<<<<<< HEAD
## Implementação com Lista Estática

O sistema foi implementado utilizando uma lista estática, que é uma estrutura de dados linear onde os elementos são armazenados em um array de tamanho fixo. Esta escolha oferece:

- Acesso direto aos elementos através de índices
- Alocação contígua de memória
- Simplicidade na implementação
- Facilidade na persistência de dados

A lista estática é implementada através da estrutura `Biblioteca`, que contém um array de `Livro` com tamanho máximo definido por `MAX_LIVROS`. As operações de inserção, remoção e busca são realizadas mantendo a ordem dos elementos no array.

=======
>>>>>>> 50af47fa6e84f59a63771c65e5cc01dd11c77d63
## Funcionalidades

O sistema oferece as seguintes funcionalidades:

1. **Inserir Livro**: Adiciona um novo livro à biblioteca
2. **Remover Livro**: Remove um livro existente da biblioteca
3. **Buscar Livro por Código**: Localiza um livro específico usando seu código
4. **Buscar Livro por Título**: Encontra livros pelo título
5. **Listar Livros**: Exibe todos os livros cadastrados
6. **Gerar Relatório**: Cria um relatório detalhado dos livros
7. **Emprestar Livro**: Registra o empréstimo de um livro
8. **Devolver Livro**: Registra a devolução de um livro
9. **Salvar Dados**: Salva manualmente os dados da biblioteca
10. **Carregar Dados**: Carrega os dados salvos anteriormente
11. **Ver Métricas de Tempo**: Exibe o tempo de execução das operações

## Estrutura de Dados

O sistema utiliza as seguintes estruturas de dados:

```c
typedef struct {
    int codigo;
    char titulo[100];
    char autor[100];
    char tema[50];
    int quantidade;
    int emprestados;
    int vezes_emprestado;
} Livro;

typedef struct {
    Livro livros[MAX_LIVROS];
    int total;
} Biblioteca;
```

## Requisitos e Instalação

### Requisitos

- Compilador C (gcc recomendado)
- Sistema operacional compatível

### Compilação e Execução

1. Compile o projeto:

```
gcc -o biblioteca main.c biblioteca.c
```

2. Execute o programa:

```
biblioteca
```

## Persistência de Dados

O sistema salva automaticamente os dados no arquivo `biblioteca.dat` quando o programa é encerrado e carrega esses dados quando é iniciado. Os dados incluem:

- Código do livro
- Título
- Autor
- Tema
- Quantidade de cópias
- Quantidade de cópias emprestadas
- Número de vezes que o livro foi emprestado

## Métricas e Desempenho

O sistema inclui funcionalidades para medir o tempo de execução das principais operações:

- Inserção de livros
- Busca por código
- Remoção de livros
- Ordenação por título

Estas métricas podem ser visualizadas através da opção 13 no menu principal.

## Próximas Etapas

- Implementação alternativa com outra estrutura de dados
- Execução de testes com diferentes volumes de dados
- Medição do tempo das operações
- Comparação de desempenho por meio de gráficos
- Produção de relatório técnico

## Observações

- O sistema utiliza um array estático com capacidade máxima de 100 livros
- Cada livro possui um código único
- Os livros podem ser ordenados por título
- O sistema mantém controle de empréstimos e quantidade de vezes que cada livro foi emprestado