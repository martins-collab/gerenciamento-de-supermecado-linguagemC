#include "funcoes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>
#include <math.h>
#include <ctype.h>
#include <stdbool.h>

/* 
    A função cadastra_produtos cadastra produtos dentro de um vetor de 
    struct chamado Produto. Ela também verifica se o produto já existe
    e caso exista chama uma função para alterar o produto existente.    
*/

void cadastra_produtos(Produto estoque[], int *quantidade_produto){

    //Conferindo a quantidade de produtos cadastrados (não pode passar e 3000)
    if(*quantidade_produto >= MAX_PRODUTOS){
        printf("Estoque cheio. Não é possível cadastrar mais produtos\n");
        return;
    } 

    int i;

    titulo("Cadastrar Produto");

    // Inicializando um novo produto
    Produto produto;
    produto.situacao = 1;

    produto.id_produto = *quantidade_produto + 1;

    //Solicitando o nome do produto
    printf("Nome do produto: ");
    fgets(produto.nome, sizeof(produto.nome), stdin); 
    produto.nome[strcspn(produto.nome, "\n")] = '\0'; 

    //Solicitando a quantidade do produto
    printf("Digite a quantidade: ");
    scanf("%d", &produto.quantidade);
    getchar();

    //Solicitando o valor do produto
    printf("Digite o valor: ");
    scanf("%f", &produto.valor);
    getchar();

    // Verifica se já existe produto com esse nome
    int indice_existente = -1;

    for(i=0; i < *quantidade_produto; i++){
        if (strcasecmp(estoque[i].nome, produto.nome) == 0) {
            indice_existente = i;
            break;
        }
    }
    
    // Verifica se já existe produto com esse nome
    // Se houver vai chamar a função de altera_produto
    if(indice_existente != -1){
        printf("\nProduto '%s' já existe no estoque\n", estoque[indice_existente].nome);
        altera_produto(estoque, indice_existente);
        return; // Evita cadastro duplicado
    } else{
        // Adiciona o novo produto ao estoque (cadastra)
        estoque[*quantidade_produto] = produto;
        (*quantidade_produto)++;
        printf("\nProduto cadastrado\n\n");
    }
    
}

/*
    A função controle_estoque verifica se algum produto está com a 
    quantidade menor ou igual a 5 e avisa que o produto precisa de reposição.
    Caso o produto esteja com estoque normal, ele apenas atualiza a situação
    para ativo.
*/

void controle_estoque(Produto estoque[], int quantidade_produto){

    int encontrou = 0, i;

    titulo("Controle de Estoque");

    // Percorre todo estoque de produtos
    for(i=0; i < quantidade_produto; i++){

        // Produto com baixa quantidade ou sem estoque
        if(estoque[i].quantidade <= 5){

            estoque[i].situacao = 0; 

            printf("\nProduto em baixa quantidade ou sem estoque\n");

            printf("id: %d\n", estoque[i].id_produto);
            printf("Nome: %s\n", estoque[i].nome);
            printf("Quantidade: %d\n", estoque[i].quantidade);
            printf("Valor: R$%.2f\n", estoque[i].valor);

            if(estoque[i].situacao){
                printf("Situação: Ativo\n");
            } else{
                printf("Situação: Reposição necessária\n");
            }
            encontrou = 1;

        } else {
            // Estoque normal
            estoque[i].situacao = 1; 
        }
    }

    if(!encontrou){
        printf("Todos os produtos estão com estoque suficiente\n");
    }
}

/* 
    A função imprime_produto imprime todos os produtos cadastrados
    no estoque, mostrando seus dados como id, nome, quantidade, valor
    e situação.
*/

void imprime_produto(Produto estoque[], int quantidade_produto){

    // Verificando se o estoque não está vazio
    if(quantidade_produto == 0){
        printf("Nenhum produto cadastrado\n");
        return;
    } 

    titulo("Lista de Produtos");

    int i;

    // Percorre todo estoque de produtos
    for(i=0; i < quantidade_produto; i++){

        // Imprime todos os produtos e seus dados 
        printf("id: %d\n", estoque[i].id_produto);
        printf("Nome: %s\n", estoque[i].nome);
        printf("Quantidade: %d\n", estoque[i].quantidade);
        printf("Valor: R$%.2f\n", estoque[i].valor);

        if(estoque[i].situacao){
            printf("Situação: Ativo\n");
        } else{
            printf("Situação: Reposiçao necessária\n");
        }

    }

    printf("\nTotal de produtos cadastrados: %d\n", quantidade_produto);

}

/* 
    A função busca_produto busca um produto pelo nome digitado
    pelo usuário. Se encontrar, imprime os dados do produto.
    Se não encontrar, informa que o produto não foi encontrado.
*/

void busca_produto(Produto estoque[], int quantidade_produto){

    char produtoProcurado[100];
    int encontrado = 0, i, j;

    titulo("Buscar Produto");

    printf("Digite o nome do produto que deseja buscar: ");
    fgets(produtoProcurado, sizeof(produtoProcurado), stdin);
    produtoProcurado[strcspn(produtoProcurado, "\n")] = '\0'; 

    // Converter produtoProcurado para minúsculo
    for(j=0; produtoProcurado[j]; j++){
        produtoProcurado[j] = tolower((unsigned char)produtoProcurado[j]);
    }

    // Percorre todo estoque de produtos
    for(i=0; i < quantidade_produto; i++){
        char nome_lower[100];
        // Transformar o nome do produto em minúsculo para comparação
        strcpy(nome_lower, estoque[i].nome);
        // Converte para minúsculo
        for(j=0; nome_lower[j]; j++){
            nome_lower[j] = tolower((unsigned char)nome_lower[j]);
        }

        // Comparação ignorando maiúsculas e minúsculas
        if(strcmp(nome_lower, produtoProcurado) == 0){
            printf("\nProduto '%s' encontrado:\n", estoque[i].nome);
            imprime_produto(&estoque[i], 1);
            encontrado = 1;
            break;
        }
    }

    if(!encontrado) {
        printf("Produto não encontrado\n");
    }
}

/*
    A função venda permite ao usuário comprar um produto do estoque.
    Ela verifica se o produto existe, se há estoque disponível,
    solicita a quantidade desejada, calcula o valor total e processa
    o pagamento. Se o pagamento for aprovado, atualiza o estoque.
*/

int venda(Produto estoque[], int quantidade_produto, Venda vendas[], int *quantidade_vendas){

    // Verificando se o estoque não está vazio
    if(quantidade_produto == 0){
        printf("Nenhum produto cadastrado\n");
        return -1;
    }

    int i;

    titulo("Venda de Produtos");

    printf("Produtos disponíveis para venda: \n\n");

    // Mostra apenas produtos com estoque disponível
    int produtos_disponiveis = 0;

    for(i=0; i < quantidade_produto; i++){
        if(estoque[i].quantidade > 0){
            printf("Nome: %s\n", estoque[i].nome);
            printf("Quantidade: %d\n", estoque[i].quantidade);
            printf("Valor: R$ %.2f\n", estoque[i].valor);
            printf("Situação: %s\n\n", estoque[i].situacao ? "Ativo" : "Reposicao necessária");
            produtos_disponiveis++;
        }
    }

    // Confere no estoque se existe algum produto precisando de reposição
    if(produtos_disponiveis == 0){
        printf("Nenhum produto disponível para venda\n");
        return -1;
    }

    char produto_digitado[100];

    printf("Digite o nome do produto que você deseja comprar: ");
    fgets(produto_digitado, sizeof(produto_digitado), stdin);
    produto_digitado[strcspn(produto_digitado, "\n")] = '\0';

    // Chama a função que confere se o produto existe
    int indice = buscar_estoque(produto_digitado, estoque, quantidade_produto);

    // Se retornar -1 -< produto não encontrado
    if(indice == -1){
        printf("Produto não encontrado.\n");
        return -1;
    }

    // Produto encontrado, agora verificar a quantidade
    // Verifica se o produto está com estoque disponível
    if(estoque[indice].quantidade <= 0){
        printf("Produto sem estoque disponível\n");
        return -1;
    }

    int quantidade_comprar;

    // Mostra detalhes do produto encontrado
    printf("\nVenda do produto: %s\n", estoque[indice].nome);
    printf("Estoque disponível: %d\n", estoque[indice].quantidade);
    printf("Preço unitário: R$ %.2f\n", estoque[indice].valor);

    printf("Quantidade que deseja comprar: ");
    scanf("%d", &quantidade_comprar);
    getchar();

    // Verificando a quantidade digitada
    if(quantidade_comprar <= 0){
        printf("Quantidade deve ser maior que zero\n");
        return -1;
    }

    // Verificando se quantidade a ser comprada não é maior que a quantidade do produto
    if(quantidade_comprar > estoque[indice].quantidade){
        printf("Quantidade indisponível. Estoque: %d\n", estoque[indice].quantidade);
        return -1;
    }

    float valor_total = estoque[indice].valor * quantidade_comprar;

    // Resumo da compra
    printf("\nResumo da compra:\n");

    printf("%-15s | %-15s | %-15s | %-15s\n", "Produto", "Valor Unitário", "Quantidade", "Valor Total");
    printf("%-15s | R$ %-12.2f | %-15d | R$ %-12.2f\n", estoque[indice].nome, estoque[indice].valor, quantidade_comprar, valor_total);
    
    // Escolha da forma de pagamento
    int tipo_pagamento = 0;
    int pagamento_aprovado = 0;
    char forma_pagamento[20] = "";

    titulo("Forma de Pagamento");
    printf("Selecione a forma de pagamento:\n\n");
    printf("1 - À vista (dinheiro, PIX, débito)\n");
    printf("2 - Parcelado no cartão de crédito\n");
    printf("3 - Cancelar compra\n\n");
    printf("Opção: ");
    scanf("%d", &tipo_pagamento);
    getchar();

    switch (tipo_pagamento) {
        case 1:
            pagamento_aprovado = pagamento_avista(valor_total);
            strcpy(forma_pagamento, "À vista");
            break;
        case 2:
            pagamento_aprovado = pagamento_parcelado(valor_total);
            strcpy(forma_pagamento, "Parcelado");
            break;
        case 3:
            printf("Compra cancelada.\n");
            return -1;
        default:
            printf("Opção inválida. Venda não realizada.\n");
            return -1;
    }

    if (pagamento_aprovado) {
        estoque[indice].quantidade -= quantidade_comprar;

        char data_venda[20];
        registrar_data(data_venda, sizeof(data_venda));

        Venda nova_venda;
        nova_venda.id_venda = *quantidade_vendas + 1;

        strcpy(nova_venda.nome_produto, estoque[indice].nome);

        nova_venda.quantidade = quantidade_comprar;
        nova_venda.valor_unitario = estoque[indice].valor;
        nova_venda.valor_total = valor_total;

        strncpy(nova_venda.data, data_venda, sizeof(nova_venda.data));
        strncpy(nova_venda.forma_pagamento, forma_pagamento, sizeof(nova_venda.forma_pagamento));

        nova_venda.data[sizeof(nova_venda.data) - 1] = '\0';
        nova_venda.forma_pagamento[sizeof(nova_venda.forma_pagamento) - 1] = '\0';

        // Adiciona a nova venda ao array de vendas
        vendas[*quantidade_vendas] = nova_venda;
        (*quantidade_vendas)++;

        printf("\nVenda realizada com sucesso em %s\n", data_venda);
        printf("Novo estoque de %s: %d unidades\n", estoque[indice].nome, estoque[indice].quantidade);

        return 0;
    } else {
        printf("Pagamento cancelado. Venda não realizada\n");
        return -1;
    }
}

/*
    A função processar_pagamento gerencia o processo de pagamento,
    oferecendo opções de pagamento à vista ou parcelado.
    Retorna 1 se o pagamento for aprovado, 0 se cancelado.
*/

int processar_pagamento(float valor_total){

    int opcao;
    
    titulo("Forma de Pagamento");
    
    do{

        printf("Selecione a forma de pagamento:\n\n");

        printf("1 - À vista (dinheiro, PIX, débito)\n");
        printf("2 - Parcelado no cartão de crédito\n");
        printf("3 - Cancelar compra\n\n");

        printf("Opção: ");
        scanf("%d", &opcao);
        getchar();

        switch(opcao){
            case 1:
                return pagamento_avista(valor_total);
            case 2:
                return pagamento_parcelado(valor_total);
            case 3:
                printf("Compra cancelada\n");
                return 0;
            default:
                printf("Opção inválida. Tente novamente\n");
        }

    } while(opcao >= 1 && opcao <= 3);

    return 0;
}

/*
    A função pagamento_avista processa pagamentos à vista
    em dinheiro, PIX ou cartão de débito.
    Retorna 1 se o pagamento for aprovado, 0 se cancelado.
*/

int pagamento_avista(float valor_total){

    (void)valor_total;
    int opcao;
    
    titulo("Pagamento à Vista");
    
    do{

        printf("Selecione o metodo:\n\n");

        printf("1 - Dinheiro\n");
        printf("2 - PIX\n");
        printf("3 - Cartão de débito\n");

        printf("4 - Voltar\n\n");

        printf("Opção: ");
        scanf("%d", &opcao);
        getchar();

        switch(opcao){
            case 1:
                printf("Pagamento em dinheiro aprovado\n");
                return 1;
            case 2:
                printf("Pagamento via pix aprovado\n");
                return 1;
            case 3:
                printf("Pagamento no débito aprovado\n");
                return 1;
            case 4:
                return 0; 
            default:
                printf("Opção inválida.\n");
        }
    } while(opcao >= 1 && opcao >= 4);

    return 0;
}

/*
    A função pagamento_parcelado processa pagamentos parcelados
    no cartão de crédito. Solicita o número de parcelas e confirma
    o parcelamento.
    Retorna 1 se o pagamento for aprovado, 0 se cancelado.
*/

int pagamento_parcelado(float valor_total){

    int parcelas, confirmar;

    titulo("Pagamento Parcelado");
    
    do{

        printf("Em quantas vezes deseja parcelar? (12x): ");
        scanf("%d", &parcelas);
        getchar();

        float valor_parcelas = valor_total / parcelas;

        printf("Resumo do parcelamento:\n\n");

        printf("Parcelas: %dx\n", parcelas);
        printf("Valor da parcela: R$ %.2f\n", valor_parcelas);
        printf("Valor total: R$ %.2f\n", valor_total);

        printf("Confirmar parcelamento? (1-Sim | 2-Não): ");
        scanf("%d", &confirmar);
        getchar();

        if(confirmar == 1){
            printf("Pagamento parcelado aprovado em %dx de R$ %.2f", parcelas, valor_parcelas);
            return 1;
        }else{
            printf("\nParcelamento cancelado\n");
            return 0;
        }

    } while(1);
}

/*
    A função faturamento imprime todas as vendas realizadas
    e o faturamento total do mês.
*/

void faturamento(Venda vendas[], int quantidade_vendas){

    if(quantidade_vendas == 0){
        printf("Nenhuma venda realizada até o momento\n");
        return;
    }

    titulo("Faturamento mensal");

    float total_faturamento = 0.0f;
    int i;   

    printf("%-5s | %-15s | %-10s | %-15s | %-15s | %-20s | %-15s\n", "ID", "Produto", "Quantidade", "Valor Unitário", "Valor Total", "Data da Venda", "Forma de Pagamento");
    printf("---------------------------------------------------------------------------------------------------------------\n");
    
    // Percorre todas as vendas realizadas
    for(i=0; i < quantidade_vendas; i++){
        printf("%-5d | %-15s | %-10d | R$ %-12.2f | R$ %-12.2f | %-20s | %-15s\n", vendas[i].id_venda, vendas[i].nome_produto, vendas[i].quantidade, vendas[i].valor_unitario, vendas[i].valor_total, vendas[i].data, vendas[i].forma_pagamento);
        total_faturamento += vendas[i].valor_total;
    }
    printf("---------------------------------------------------------------------------------------------------------------\n");
    
    printf("Total de vendas: %d\n", quantidade_vendas);
    printf("Faturamento total: R$ %.2f\n", total_faturamento);  

}

/*
    A função altera_produto permite ao usuário alterar os dados
    de um produto existente, como nome, quantidade e valor.
*/

void altera_produto(Produto estoque[], int indice){

    printf("\nProduto em alteração: %s\n\n", estoque[indice].nome);

    printf("Nome atual: %s\n", estoque[indice].nome);
    printf("Quantidade atual: %d\n", estoque[indice].quantidade);
    printf("Valor atual: R$%.2f\n\n", estoque[indice].valor);

    // Atulizar nome
    printf("Deseja atualizar o nome? (s/n): ");
    char resposta_nome;
    scanf("%c", &resposta_nome);
    getchar();

    if(resposta_nome == 's' || resposta_nome == 'S') {
        printf("Novo nome: ");
        fgets(estoque[indice].nome, sizeof(estoque[indice].nome), stdin);
        estoque[indice].nome[strcspn(estoque[indice].nome, "\n")] = '\0'; 
        printf("Nome atualizado\n");
    }

    // Atualizar quantidade
    printf("\nDeseja atualizar a quantidade? (s/n): ");
    char resposta_quantidade;
    scanf("%c", &resposta_quantidade);
    getchar();
    
    if(resposta_quantidade == 's' || resposta_quantidade == 'S') {
        printf("Nova quantidade: ");
        scanf("%d", &estoque[indice].quantidade);
        getchar();
        printf("Quantidade atualizada\n");
    }
    
    // Atualizar valor
    printf("Deseja atualizar o valor? (s/n): ");
    char resposta_valor;
    scanf("%c", &resposta_valor);
    getchar();
    
    if(resposta_valor == 's' || resposta_valor == 'S') {
        printf("Novo valor: ");
        scanf("%f", &estoque[indice].valor);
        getchar();
        printf("Valor atualizado\n");
    }
    
    printf("Alterações concluídas\n\n");
}

/*
    A função buscar_estoque busca um produto pelo nome
    digitado pelo usuário. Retorna o índice do produto
    se encontrado, ou -1 se não encontrado.
*/

int buscar_estoque(char nomeDigitado[], Produto estoque[], int quantidade_produto){

    // Remove o \n do final da string do nome digitado
    nomeDigitado[strcspn(nomeDigitado, "\n")] = '\0';

    int i, j;

    for(i=0; nomeDigitado[i] != '\0'; i++){
        nomeDigitado[i] = tolower((unsigned char)nomeDigitado[i]);
    }

    for(i=0; i < quantidade_produto; i++){

        char nome_lower[100];
        strcpy(nome_lower, estoque[i].nome);

        for(j=0; nome_lower[j]; j++){
            nome_lower[j] = tolower((unsigned char)nome_lower[j]);
        }

        if(strcmp(nome_lower, nomeDigitado) == 0){
            // Retorna o índice do produto encontrado
            // Que me permite acessar todo o objeto
            return i; 
        }
    }
    return -1;
}

/*
    A função registrar_data registra a data e hora atual
    em um buffer fornecido pelo usuário.
*/

void registrar_data(char *buffer, int tamanho){

    time_t t;
    struct tm *infoTempo;

    time(&t);
    infoTempo = localtime(&t);

    strftime(buffer, tamanho, "%d/%m/%Y %H:%M:%S", infoTempo);

}

/*
    A função titulo imprime um título em maiúsculas
    para destacar seções do programa.
*/

void titulo(const char *texto){
    int i;
    printf("\n");
    for(i=0; texto[i] != '\0'; i++){
        putchar(toupper((unsigned char)texto[i]));
    }
    printf("\n\n");
}