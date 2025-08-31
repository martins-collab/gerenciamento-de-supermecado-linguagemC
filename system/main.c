#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>
#include <math.h>
#include <ctype.h>
#include <stdbool.h>

#include "funcoes.h"

int main(void){
    
    // Acentuação em português
    setlocale(LC_ALL, "Portuguese");
    setlocale(LC_ALL, "Portuguese_Brazil.1252");

    // Cadastro com ponto e não vírgula 
    setlocale(LC_NUMERIC, "C"); 

    // Produtos
    Produto estoque[MAX_PRODUTOS] = {0};
    int quantidade_produto = 0;

    // Vendas
    Venda vendas[1000]; 
    int quantidade_vendas = 0;

    int opcao;

    do{
        
        printf("\nMenu de opções\n\n");

        printf("1 - Cadastrar produto\n");
        printf("2 - Imprimir produtos\n");
        printf("3 - Buscar produto\n");
        printf("4 - Vender produto\n");
        printf("5 - Controle de estoque\n");
        printf("6 - Imprimir Faturamento\n\n");

        printf("7 - Sair\n\n");

        printf("Escolha uma opção: "); 
        scanf("%d", &opcao);
        getchar();

        switch (opcao){
        case 1:
            cadastra_produtos(estoque, &quantidade_produto);
            break;
        case 2:
            imprime_produto(estoque, quantidade_produto);
            break;
        case 3:
            busca_produto(estoque, quantidade_produto);
            break;
        case 4:
            venda(estoque, quantidade_produto, vendas, &quantidade_vendas);
            break;
        case 5:
            controle_estoque(estoque, quantidade_produto);
            break;
        case 6:
            faturamento(vendas, quantidade_vendas);
            break;
        case 7:
            printf("Saindo do programa...\n");
            exit(0);
        default:
            printf("Digite algo válido");
            break;
        }

    } while (opcao >= 1 && opcao <= 7);
    

    return 0;

}
































