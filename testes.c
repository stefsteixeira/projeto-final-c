#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "data.h"
#include "util.h"
#include "wug.h"

static void separador(const char* titulo) {
    printf("\n=== %s ===\n", titulo);
}

int main(void) {
    printf("--- INICIANDO TESTES ---\n\n");

    // -------------------------------------------------------------------------
    // A. Smoke test (criação + impressão)
    // -------------------------------------------------------------------------
    separador("A. Smoke test (criação + impressão)");

    int g_super[16] = {1,0,1,1, 1,0,0,1, 0,1,0,0, 1,1,0,0}; // igual ao super_genome
    int g_zeros[16] = {0};
    int g_mix  [16] = {1,1,0,0, 0,1,0,1, 1,0,1,0, 0,0,1,1};

    wug_t *w1 = create_wug(g_super, M);
    wug_t *w2 = create_wug(g_zeros, F);
    wug_t *w3 = create_wug(g_mix,   M);

    print_wug(w1);
    print_wug(w2);
    print_wug(w3);
    // sanidade: não deve se quebrar
    print_wug(NULL);

    // -------------------------------------------------------------------------
    // B. Teste de genome2features e rank
    // -------------------------------------------------------------------------
    separador("B. genome2features + rank");

    int feats[4];

    genome2features(g_super, feats);
    printf("g_super -> features esperadas ~[1,1,1,1]; rank=%d | got: ", rank(w1));
    for (int i = 0; i < 4; i++) printf("%d%s", feats[i], (i<3?",":""));
    printf("\n");

    genome2features(g_zeros, feats);
    printf("g_zeros -> features (muitas zeros) ; rank=%d | got: ", rank(w2));
    for (int i = 0; i < 4; i++) printf("%d%s", feats[i], (i<3?",":""));
    printf("\n");

    genome2features(g_mix, feats);
    printf("g_mix   -> rank=%d | features: ", rank(w3));
    for (int i = 0; i < 4; i++) printf("%d%s", feats[i], (i<3?",":""));
    printf("\n");

    // -------------------------------------------------------------------------
    // C. Teste de insert_ranked (ordem por rank e com respeito à capacidade)
    // -------------------------------------------------------------------------
    separador("C. insert_ranked (ordem decrescente + capacidade)");
    int cap = 3, size = 0;
    wug_t* pop[3];

    // cria mais um genoma de rank intermediário
    int g_mid[16] = {1,0,1,1, 0,0,0,1, 0,1,0,0, 1,1,0,0};
    wug_t *w4 = create_wug(g_mid, F);

    printf("Inserindo w1 (rank=%d)\n", rank(w1));
    insert_ranked(pop, w1, &size, cap);
    print_population(pop, size);

    printf("Inserindo w2 (rank=%d)\n", rank(w2));
    insert_ranked(pop, w2, &size, cap);
    print_population(pop, size);

    printf("Inserindo w3 (rank=%d)\n", rank(w3));
    insert_ranked(pop, w3, &size, cap);
    print_population(pop, size);

    printf("Inserindo w4 (rank=%d) com população cheia (cap=%d)\n", rank(w4), cap);
    bool ok = insert_ranked(pop, w4, &size, cap);
    printf("Resultado da inserção: %s\n", ok ? "true" : "false");
    print_population(pop, size);

    // -------------------------------------------------------------------------
    // D. Teste de report_population (conta os superwugs)
    // -------------------------------------------------------------------------
    separador("D. report_population (conta superwugs rank==4)");
    int qtd = report_population(pop, size);
    printf("superwugs: %d\n", qtd);

    // -------------------------------------------------------------------------
    // Liberação de memória
    // -------------------------------------------------------------------------
    for (int i = 0; i < size; i++) free(pop[i]);
    if (!ok) free(w4); // se não entrou na pop, precisa liberar
    // w1/w2/w3 já foram liberados acima ao limpar a pop
    // Obs: nesta sequência, w1..w3 estão na pop mas w4 pode ter ficado fora.

    printf("\n--- FIM DOS TESTES ---\n");
    return 0;
}
