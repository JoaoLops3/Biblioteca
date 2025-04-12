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
    
    MetricasTempo metricas;
    iniciarMedicaoTempo(&metricas);

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
        printf("13. Ver metricas de tempo\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        limparBuffer();

        switch (opcao) {
            case 1: {
                Livro livro;
                printf("Codigo: ");
                scanf("%d", &livro.codigo);
                limparBuffer();
                printf("Titulo: ");
                fgets(livro.titulo, MAX_TITULO, stdin);
                livro.titulo[strcspn(livro.titulo, "\n")] = 0;
                printf("Autor: ");
                fgets(livro.autor, MAX_AUTOR, stdin);
                livro.autor[strcspn(livro.autor, "\n")] = 0;
                printf("Tema: ");
                fgets(livro.tema, MAX_TEMA, stdin);
                livro.tema[strcspn(livro.tema, "\n")] = 0;
                printf("Quantidade: ");
                scanf("%d", &livro.quantidade);
                limparBuffer();

                if (inserirLivro(&biblioteca, livro)) {
                    printf("Livro inserido com sucesso!\n");
                } else {
                    printf("Erro ao inserir livro. Biblioteca cheia.\n");
                }
                break;
            }
            case 2: {
                int codigo;
                printf("Codigo do livro a remover: ");
                scanf("%d", &codigo);
                limparBuffer();

                if (removerLivro(&biblioteca, codigo)) {
                    printf("Livro removido com sucesso!\n");
                } else {
                    printf("Erro ao remover livro. Livro nao encontrado ou possui exemplares emprestados.\n");
                }
                break;
            }
            case 3: {
                int codigo;
                printf("Codigo do livro a buscar: ");
                scanf("%d", &codigo);
                limparBuffer();

                Livro* livro = buscarPorCodigo(&biblioteca, codigo);
                if (livro) {
                    printf("\nLivro encontrado:\n");
                    printf("Codigo: %d\n", livro->codigo);
                    printf("Titulo: %s\n", livro->titulo);
                    printf("Autor: %s\n", livro->autor);
                    printf("Tema: %s\n", livro->tema);
                    printf("Quantidade: %d\n", livro->quantidade);
                    printf("Emprestados: %d\n", livro->emprestados);
                    printf("Total de emprestimos: %d\n", livro->total_emprestimos);
                } else {
                    printf("Livro nao encontrado.\n");
                }
                break;
            }
            case 4: {
                char tema[MAX_TEMA];
                printf("Tema a buscar: ");
                fgets(tema, MAX_TEMA, stdin);
                tema[strcspn(tema, "\n")] = 0;

                Livro resultados[MAX_LIVROS];
                int quantidade;
                buscarPorTema(&biblioteca, tema, resultados, &quantidade);

                if (quantidade > 0) {
                    printf("\nLivros encontrados:\n");
                    for (int i = 0; i < quantidade; i++) {
                        printf("Codigo: %d\n", resultados[i].codigo);
                        printf("Titulo: %s\n", resultados[i].titulo);
                        printf("Autor: %s\n", resultados[i].autor);
                        printf("Tema: %s\n", resultados[i].tema);
                        printf("Quantidade: %d\n", resultados[i].quantidade);
                        printf("Emprestados: %d\n", resultados[i].emprestados);
                        printf("Total de emprestimos: %d\n", resultados[i].total_emprestimos);
                        printf("-------------------\n");
                    }
                } else {
                    printf("Nenhum livro encontrado com este tema.\n");
                }
                break;
            }
            case 5:
                listarLivros(&biblioteca);
                break;
            case 6:
                ordenarPorTitulo(&biblioteca);
                printf("Livros ordenados por titulo.\n");
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
                printf("Codigo do livro a emprestar: ");
                scanf("%d", &codigo);
                limparBuffer();

                int resultado = emprestarLivro(&biblioteca, codigo);
                if (resultado == 1) {
                    printf("Livro emprestado com sucesso!\n");
                } else if (resultado == -1) {
                    printf("Todos os exemplares deste livro ja estao emprestados.\n");
                } else {
                    printf("Livro nao encontrado.\n");
                }
                break;
            }
            case 11: {
                int codigo;
                printf("Codigo do livro a devolver: ");
                scanf("%d", &codigo);
                limparBuffer();

                int resultado = devolverLivro(&biblioteca, codigo);
                if (resultado == 1) {
                    printf("Livro devolvido com sucesso!\n");
                } else if (resultado == -1) {
                    printf("Nao ha exemplares deste livro emprestados.\n");
                } else {
                    printf("Livro nao encontrado.\n");
                }
                break;
            }
            case 12:
                salvarDados(&biblioteca);
                break;
            case 13:
                imprimirMetricasTempo(&metricas);
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