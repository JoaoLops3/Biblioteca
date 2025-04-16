#ifndef BIBLIOTECA_H
#define BIBLIOTECA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LIVROS 100
#define MAX_TITULO 100
#define MAX_AUTOR 100
#define MAX_TEMA 50
#define ARQUIVO_DADOS "biblioteca.dat"

typedef struct {
    int codigo;
    char titulo[MAX_TITULO];
    char autor[MAX_AUTOR];
    char tema[MAX_TEMA];
    int quantidade;
    int emprestados;
    int total_emprestimos;
} Livro;

typedef struct {
    Livro livros[MAX_LIVROS];
    int total;
} Biblioteca;

// Funções da biblioteca
void inicializarBiblioteca(Biblioteca *b);
void inserirLivroBiblioteca(Biblioteca *b, int codigo, const char *titulo, const char *autor, const char *tema, int quantidade);
void removerLivroBiblioteca(Biblioteca *b, int codigo, int quantidade);
Livro* buscarPorCodigo(Biblioteca *b, int codigo);
void buscarPorTema(Biblioteca *b, const char *tema, Livro *resultados, int *quantidade);
void listarLivros(Biblioteca *b);
void ordenarPorTitulo(Biblioteca *b);
void quantidadePorTema(Biblioteca *b);
void livrosMaisEmprestados(Biblioteca *b);
void statusEmprestimo(Biblioteca *b);
void salvarDados(Biblioteca *b);
void carregarDados(Biblioteca *b);
int emprestarLivro(Biblioteca *b, int codigo);
int devolverLivro(Biblioteca *b, int codigo);

#endif // BIBLIOTECA_H 