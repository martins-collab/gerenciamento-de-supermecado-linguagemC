# Como compilar e executar

**Para compilar:**
```sh
gcc main.c funcoes.c -o programa -Wall -Wextra
```

**Para executar (no Windows):**
```sh
./programa
```

---

## Observa��es importantes

- **Acentua��o:**  
  O VS Code geralmente n�o aceita acentua��o em C, mesmo utilizando `setlocale`. Para resolver, altere a codifica��o do arquivo de UTF-8 para **Windows 1252**.

- **Separador decimal:**  
  O programa est� pr�-configurado para utilizar **ponto (.)** como separador decimal. Se utilizar v�rgula, ocorrer� erro na leitura de n�meros reais.

- **Limpeza de warnings:**  
  Caso apare�a algum aviso de par�metro n�o utilizado (ex: `unused parameter`), voc� pode adicionar `(void)nome_parametro;` no in�cio da fun��o para evitar o warning.

- **Limite de produtos e vendas:**  
  O sistema suporta at� 3000 produtos (`MAX_PRODUTOS`) e 1000 vendas simult�neas. Ajuste esses valores em `funcoes.h` conforme sua necessidade.


