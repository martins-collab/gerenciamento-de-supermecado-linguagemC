#ifndef FUNCOES_H
#define FUNCOES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>
#include <math.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX_PRODUTOS 3000

typedef struct{
    int id_produto;
    char nome[100];
    int quantidade;
    float valor;
    float faturamento;
    int situacao;
} Produto;

typedef struct{
    int id_venda;
    char nome_produto[100];
    int quantidade;
    float valor_unitario;
    float valor_total;
    char data[20];
    char forma_pagamento[20];
} Venda;

// Funções de estoque
void controle_estoque(Produto estoque[], int quantidade_produto);
int buscar_estoque(char nomeDigitado[], Produto estoque[], int quantidade_produto);

// Funções de produto
void busca_produto(Produto estoque[], int quantidade_produto);
void cadastra_produtos(Produto estoque[], int *quantidade_produto);
void imprime_produto(Produto estoque[], int quantidade_produto);
void altera_produto(Produto estoque[], int indice);

// Funções de venda
int venda(Produto estoque[], int quantidade_produto, Venda vendas[], int *quantidade_vendas);
int processar_pagamento(float valor_total);
int pagamento_avista(float valor_total);
int pagamento_parcelado(float valor_total);
void registrar_data(char *buffer, int tamanho); 
void faturamento(Venda vendas[], int quantidade_vendas);

// Validações e utilitários
void titulo(const char *texto);

#endif



