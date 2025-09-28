# Projeto Final Superwug // Introdução à Computação

Este projeto foi desenvolvido para a disciplina Introdução à Computação, com o objetivo de praticar os conceitos de programação estruturada em C a partir da simulação de uma população de “wugs” (criaturas fictícias). O programa implementa os conceitos pedidos de genética (genomas e características), ranking de indivíduos e gerenciamento de uma população ordenada com capacidade limitada, demonstrando o uso de estruturas de dados, alocação de memória e modularização de código.

## Estrutura do Projeto

data.h -> definição das estruturas de dados (wug_t, gender_t, etc);

util.h / util.c -> funções utilitárias;

wug.h / wug.c -> funções principais do projeto (criação de wug, decodificação do genoma, rank, inserção na população, impressão, relatórios);

main.c -> execução básica do projeto;

testes.c -> conjunto de testes unitários/didáticos;

Makefile -> automatiza compilação e limpeza dos binários.

## Como Usar

### Pré-requisitos

Para compilar e executar este projeto, você precisará de:
* Um compilador C (ex: `gcc`).
* A ferramenta `make`.

### Compilação

```bash
# Compilar programa principal
make

# Compilar programa de testes
make testes

# Limpar arquivos objeto e executáveis
make clean
```

### Execução

./projeto   # Executa versão principal
./testes    # Executa a suíte de testes

---

## Autor:
Stefany de Sousa Teixeira