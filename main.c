#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "biblioteca.h"

void limparBuffer() {
    while (getchar() != '\n');
}

int main() {
    Biblioteca biblioteca;
    inicializarBiblioteca(&biblioteca);
    carregarDados(&biblioteca);

    int opcao;
    do {
        printf("\n=== Sistema de Biblioteca ===\n");
        printf("1. Inserir livro\n");
        printf("2. Remover livro\n");
        printf("3. Buscar livro por codigo\n");
        printf("4. Buscar livros por tema\n");
        printf("5. Listar todos os livros\n");
        printf("6. Ordenar livros por titulo\n");
        printf("7. Quantidade de livros por tema\n");
        printf("8. Livros mais emprestados\n");
        printf("9. Status de emprestimos\n");
        printf("10. Emprestar livro\n");
        printf("11. Devolver livro\n");
        printf("12. Salvar dados\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        limparBuffer();

        switch (opcao) {
            case 1: {
                int codigo, quantidade;
                char titulo[MAX_TITULO], autor[MAX_AUTOR], tema[MAX_TEMA];
                printf("Codigo: ");
                scanf("%d", &codigo);
                printf("Titulo: ");
                scanf(" %[^\n]", titulo);
                printf("Autor: ");
                scanf(" %[^\n]", autor);
                printf("Tema: ");
                scanf(" %[^\n]", tema);
                printf("Quantidade: ");
                scanf("%d", &quantidade);
                inserirLivroBiblioteca(&biblioteca, codigo, titulo, autor, tema, quantidade);
                break;
            }
            case 2: {
                int codigo, quantidade;
                printf("Codigo do livro: ");
                scanf("%d", &codigo);
                printf("Quantidade a remover: ");
                scanf("%d", &quantidade);
                removerLivroBiblioteca(&biblioteca, codigo, quantidade);
                break;
            }
            case 3: {
                int codigo;
                printf("Codigo do livro: ");
                scanf("%d", &codigo);
                Livro *livro = buscarPorCodigo(&biblioteca, codigo);
                if (livro) {
                    printf("Livro encontrado:\n");
                    printf("Titulo: %s\n", livro->titulo);
                    printf("Autor: %s\n", livro->autor);
                    printf("Tema: %s\n", livro->tema);
                    printf("Quantidade: %d\n", livro->quantidade);
                    printf("Emprestados: %d\n", livro->emprestados);
                } else {
                    printf("Livro nao encontrado!\n");
                }
                break;
            }
            case 4: {
                char tema[MAX_TEMA];
                printf("Tema: ");
                scanf(" %[^\n]", tema);
                Livro resultados[MAX_LIVROS];
                int quantidade;
                buscarPorTema(&biblioteca, tema, resultados, &quantidade);
                if (quantidade > 0) {
                    printf("Livros encontrados:\n");
                    for (int i = 0; i < quantidade; i++) {
                        printf("%d. %s - %s\n", i + 1, resultados[i].titulo, resultados[i].autor);
                    }
                } else {
                    printf("Nenhum livro encontrado com este tema!\n");
                }
                break;
            }
            case 5:
                listarLivros(&biblioteca);
                break;
            case 6:
                ordenarPorTitulo(&biblioteca);
                printf("Livros ordenados por titulo!\n");
                break;
            case 7:
                quantidadePorTema(&biblioteca);
                break;
            case 8:
                livrosMaisEmprestados(&biblioteca);
                break;
            case 9:
                statusEmprestimo(&biblioteca);
                break;
            case 10: {
                int codigo;
                printf("Codigo do livro: ");
                scanf("%d", &codigo);
                if (emprestarLivro(&biblioteca, codigo)) {
                    printf("Livro emprestado com sucesso!\n");
                } else {
                    printf("Nao foi possivel emprestar o livro!\n");
                }
                break;
            }
            case 11: {
                int codigo;
                printf("Codigo do livro: ");
                scanf("%d", &codigo);
                if (devolverLivro(&biblioteca, codigo)) {
                    printf("Livro devolvido com sucesso!\n");
                } else {
                    printf("Nao foi possivel devolver o livro!\n");
                }
                break;
            }
            case 12:
                salvarDados(&biblioteca);
                printf("Dados salvos com sucesso!\n");
                break;
            case 0:
                salvarDados(&biblioteca);
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 0);

    return 0;
} 