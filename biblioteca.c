#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "biblioteca.h"

static Biblioteca biblioteca;

void inicializarBiblioteca(Biblioteca *b) {
    b->total = 0;
}

void inserirLivroBiblioteca(Biblioteca *b, int codigo, const char *titulo, const char *autor, const char *tema, int quantidade) {
    if (b->total >= MAX_LIVROS) {
        printf("Biblioteca cheia!\n");
        return;
    }

    // Verifica se o livro já existe
    for (int i = 0; i < b->total; i++) {
        if (b->livros[i].codigo == codigo) {
            b->livros[i].quantidade += quantidade;
            return;
        }
    }

    // Insere novo livro
    Livro *novo = &b->livros[b->total];
    novo->codigo = codigo;
    strncpy(novo->titulo, titulo, MAX_TITULO - 1);
    strncpy(novo->autor, autor, MAX_AUTOR - 1);
    strncpy(novo->tema, tema, MAX_TEMA - 1);
    novo->quantidade = quantidade;
    novo->emprestados = 0;
    novo->total_emprestimos = 0;
    b->total++;
}

void removerLivroBiblioteca(Biblioteca *b, int codigo, int quantidade) {
    for (int i = 0; i < b->total; i++) {
        if (b->livros[i].codigo == codigo) {
            if (b->livros[i].quantidade >= quantidade) {
                b->livros[i].quantidade -= quantidade;
                if (b->livros[i].quantidade == 0) {
                    // Remove o livro se não houver mais cópias
                    for (int j = i; j < b->total - 1; j++) {
                        b->livros[j] = b->livros[j + 1];
                    }
                    b->total--;
                }
            } else {
                printf("Quantidade insuficiente de exemplares!\n");
            }
            return;
        }
    }
    printf("Livro nao encontrado!\n");
}

Livro* buscarPorCodigo(Biblioteca *b, int codigo) {
    for (int i = 0; i < b->total; i++) {
        if (b->livros[i].codigo == codigo) {
            return &b->livros[i];
        }
    }
    return NULL;
}

Livro* listarLivrosBiblioteca() {
    return biblioteca.livros;
}

int getTotalLivros() {
    return biblioteca.total;
}

int emprestarLivro(Biblioteca *b, int codigo) {
    Livro* livro = buscarPorCodigo(b, codigo);
    if (livro == NULL) {
        return 0; // Livro nao encontrado
    }

    if (livro->emprestados >= livro->quantidade) {
        return -1; // Todos os exemplares estao emprestados
    }

    livro->emprestados++;
    livro->total_emprestimos++;
    return 1; // Emprestimo realizado com sucesso
}

int devolverLivro(Biblioteca *b, int codigo) {
    Livro* livro = buscarPorCodigo(b, codigo);
    if (livro == NULL) {
        return 0; // Livro nao encontrado
    }

    if (livro->emprestados <= 0) {
        return -1; // Nao ha exemplares emprestados
    }

    livro->emprestados--;
    return 1; // Devolucao realizada com sucesso
}

int salvarDadosBiblioteca() {
    FILE *arquivo = fopen(ARQUIVO_DADOS, "wb");
    if (!arquivo) return 0;
    
    fwrite(&biblioteca.total, sizeof(int), 1, arquivo);
    fwrite(biblioteca.livros, sizeof(Livro), biblioteca.total, arquivo);
    
    fclose(arquivo);
    return 1;
}

int carregarDadosBiblioteca() {
    FILE *arquivo = fopen(ARQUIVO_DADOS, "rb");
    if (!arquivo) return 0;
    
    fread(&biblioteca.total, sizeof(int), 1, arquivo);
    fread(biblioteca.livros, sizeof(Livro), biblioteca.total, arquivo);
    
    fclose(arquivo);
    return 1;
}

int gerarRelatorioBiblioteca() {
    FILE *arquivo = fopen("relatorio.txt", "w");
    if (!arquivo) return 0;
    
    fprintf(arquivo, "=== Relatorio da Biblioteca ===\n\n");
    fprintf(arquivo, "Total de livros: %d\n\n", biblioteca.total);
    
    fprintf(arquivo, "%-6s %-30s %-20s %-15s %-10s %-10s %-10s\n",
        "Codigo", "Titulo", "Autor", "Tema", "Qtd", "Emp", "Total");
    
    for (int i = 0; i < biblioteca.total; i++) {
        fprintf(arquivo, "%-6d %-30s %-20s %-15s %-10d %-10d %-10d\n",
            biblioteca.livros[i].codigo,
            biblioteca.livros[i].titulo,
            biblioteca.livros[i].autor,
            biblioteca.livros[i].tema,
            biblioteca.livros[i].quantidade,
            biblioteca.livros[i].emprestados,
            biblioteca.livros[i].total_emprestimos);
    }
    
    fclose(arquivo);
    return 1;
}

void buscarPorTema(Biblioteca *b, const char *tema, Livro *resultados, int *quantidade) {
    *quantidade = 0;
    for (int i = 0; i < b->total; i++) {
        if (strcmp(b->livros[i].tema, tema) == 0) {
            resultados[*quantidade] = b->livros[i];
            (*quantidade)++;
        }
    }
}

void listarLivros(Biblioteca *b) {
    printf("\n=== Lista de Livros ===\n");
    for (int i = 0; i < b->total; i++) {
        printf("Codigo: %d\n", b->livros[i].codigo);
        printf("Titulo: %s\n", b->livros[i].titulo);
        printf("Autor: %s\n", b->livros[i].autor);
        printf("Tema: %s\n", b->livros[i].tema);
        printf("Quantidade: %d\n", b->livros[i].quantidade);
        printf("Emprestados: %d\n", b->livros[i].emprestados);
        printf("Total de emprestimos: %d\n", b->livros[i].total_emprestimos);
        printf("-------------------\n");
    }
}

void ordenarPorTitulo(Biblioteca *b) {
    for (int i = 0; i < b->total - 1; i++) {
        for (int j = 0; j < b->total - i - 1; j++) {
            if (strcmp(b->livros[j].titulo, b->livros[j + 1].titulo) > 0) {
                Livro temp = b->livros[j];
                b->livros[j] = b->livros[j + 1];
                b->livros[j + 1] = temp;
            }
        }
    }
}

void quantidadePorTema(Biblioteca *b) {
    printf("\n=== Quantidade de Livros por Tema ===\n");
    char temas[MAX_LIVROS][MAX_TEMA];
    int quantidades[MAX_LIVROS] = {0};
    int num_temas = 0;

    for (int i = 0; i < b->total; i++) {
        int encontrado = 0;
        for (int j = 0; j < num_temas; j++) {
            if (strcmp(temas[j], b->livros[i].tema) == 0) {
                quantidades[j] += b->livros[i].quantidade;
                encontrado = 1;
                break;
            }
        }
        if (!encontrado) {
            strcpy(temas[num_temas], b->livros[i].tema);
            quantidades[num_temas] = b->livros[i].quantidade;
            num_temas++;
        }
    }

    for (int i = 0; i < num_temas; i++) {
        printf("Tema: %s - Quantidade: %d\n", temas[i], quantidades[i]);
    }
}

void livrosMaisEmprestados(Biblioteca *b) {
    printf("\n=== Livros Mais Emprestados ===\n");
    ordenarPorTitulo(b); // Ordena para melhor visualizacao
    
    for (int i = 0; i < b->total; i++) {
        if (b->livros[i].total_emprestimos > 0) {
            printf("Titulo: %s\n", b->livros[i].titulo);
            printf("Quantidade: %d\n", b->livros[i].quantidade);
            printf("Total de emprestimos: %d\n", b->livros[i].total_emprestimos);
            printf("-------------------\n");
        }
    }
}

void statusEmprestimo(Biblioteca *b) {
    int disponiveis = 0;
    int emprestados = 0;
    int total_exemplares = 0;

    for (int i = 0; i < b->total; i++) {
        total_exemplares += b->livros[i].quantidade;
        disponiveis += (b->livros[i].quantidade - b->livros[i].emprestados);
        emprestados += b->livros[i].emprestados;
    }

    printf("\n=== Status de Emprestimos ===\n");
    printf("Total de exemplares: %d\n", total_exemplares);
    printf("Exemplares disponiveis: %d\n", disponiveis);
    printf("Exemplares emprestados: %d\n", emprestados);
}

void salvarDados(Biblioteca *b) {
    FILE *arquivo = fopen(ARQUIVO_DADOS, "wb");
    if (arquivo == NULL) {
        printf("Erro ao abrir arquivo para salvamento!\n");
        return;
    }

    fwrite(&b->total, sizeof(int), 1, arquivo);
    fwrite(b->livros, sizeof(Livro), b->total, arquivo);

    fclose(arquivo);
    printf("Dados salvos com sucesso!\n");
}

void carregarDados(Biblioteca *b) {
    FILE *arquivo = fopen(ARQUIVO_DADOS, "rb");
    if (arquivo == NULL) {
        printf("Arquivo de dados nao encontrado. Iniciando biblioteca vazia.\n");
        return;
    }

    fread(&b->total, sizeof(int), 1, arquivo);
    fread(b->livros, sizeof(Livro), b->total, arquivo);

    fclose(arquivo);
    printf("Dados carregados com sucesso!\n");
} 