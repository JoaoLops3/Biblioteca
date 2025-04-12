#ifndef BIBLIOTECA_H
#define BIBLIOTECA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_LIVROS 100
#define MAX_TITULO 100
#define MAX_AUTOR 50
#define MAX_TEMA 30
#define ARQUIVO_DADOS "biblioteca.dat"

// Estrutura para representar um livro
typedef struct {
    int codigo;
    char titulo[MAX_TITULO];
    char autor[MAX_AUTOR];
    char tema[MAX_TEMA];
    int quantidade;
    int emprestados;
    int total_emprestimos;
} Livro;

// Estrutura para representar a biblioteca
typedef struct {
    Livro livros[MAX_LIVROS];
    int total;
} Biblioteca;

// Estrutura para medir tempo de operações
typedef struct {
    double tempo_insercao;
    double tempo_busca;
    double tempo_remocao;
    double tempo_ordenacao;
} MetricasTempo;

// Funções da biblioteca
void inicializarBiblioteca(Biblioteca *b);
int inserirLivro(Biblioteca *b, Livro livro);
int removerLivro(Biblioteca *b, int codigo);
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

// Funções de medição de tempo
void iniciarMedicaoTempo(MetricasTempo *metricas);
void registrarTempoInsercao(MetricasTempo *metricas, double tempo);
void registrarTempoBusca(MetricasTempo *metricas, double tempo);
void registrarTempoRemocao(MetricasTempo *metricas, double tempo);
void registrarTempoOrdenacao(MetricasTempo *metricas, double tempo);
void imprimirMetricasTempo(MetricasTempo *metricas);

#endif // BIBLIOTECA_H 