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

## Observações importantes

- **Acentuação:**  
  O VS Code geralmente não aceita acentuação em C, mesmo utilizando `setlocale`. Para resolver, altere a codificação do arquivo de UTF-8 para **Windows 1252**.

- **Separador decimal:**  
  O programa está pré-configurado para utilizar **ponto (.)** como separador decimal. Se utilizar vírgula, ocorrerá erro na leitura de números reais.

- **Limpeza de warnings:**  
  Caso apareça algum aviso de parâmetro não utilizado (ex: `unused parameter`), você pode adicionar `(void)nome_parametro;` no início da função para evitar o warning.

- **Limite de produtos e vendas:**  
  O sistema suporta até 3000 produtos (`MAX_PRODUTOS`) e 1000 vendas simultâneas. Ajuste esses valores em `funcoes.h` conforme sua necessidade.


