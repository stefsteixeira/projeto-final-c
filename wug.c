#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "data.h"
#include "util.h"
#include "wug.h"

// Função para criar um wug
wug_t* create_wug(int genome[16], gender_t g) {
    // destina memória pra um novo wug
    wug_t *w = (wug_t*)malloc(sizeof(wug_t));
    if (!w) return NULL;

    // copia e normaliza o genoma (só aceita 0 ou 1)
    for (int i = 0; i < 16; i++) {
        int v = (genome ? genome[i] : 0);
        w->genome[i] = (v != 0) ? 1 : 0;
    }

    // define o gênero
    w->gender = g;

    return w;
}

// Função pra decodificar o genoma:
void genome2features(const int genome[16], int features[4]) {
    // O "genoma perfeito" p/ comparação:
    int super_genome[16] = {1,0,1,1,1,0,0,1,0,1,0,0,1,1,0,0};
    int zones[16] = {0, 1, 0, 2, 3, 3, 1, 0, 2, 1, 1, 2, 3, 0, 3, 2};

    // Assumindo que todas as features são excepcionais (valor 1).
    for (int i = 0; i < 4; i++) {
        features[i] = 1;
    }

    // Procurando por qualquer diferença:
    for (int i = 0; i < 16; i++) {
        if (genome[i] != super_genome[i]) {
            int feature_index = zones[i];
            features[feature_index] = 0;
        }
    }
}

// Função para calcular o rank:
int rank(const wug_t* w) {
    if (w == NULL) {
        return 0;
    }
    int features[4];
    genome2features(w->genome, features);

    int wug_rank = 0;
    // Conta quantas features são "1".
    for (int i = 0; i < 4; i++) {
        if (features[i] == 1) {
            wug_rank++;
        }
    }
    return wug_rank;
}

// Versão final da função de impressão, que atende aos requisitos do projeto:
void print_wug(wug_t *w) {
    if (w == NULL) {
        printf("Wug inválido!\n");
        return;
    }

    int features[4];
    genome2features(w->genome, features);
    int wug_rank = rank(w);

    char* genome_str = array_string(w->genome, 16);
    char* features_str = array_string(features, 4);

    // Imprime em uma única linha, como pedido.
    printf("%c %s %s %d\n", w->gender, genome_str, features_str, wug_rank);

    // Libera a memória alocada.
    free(genome_str);
    free(features_str);
}

// Função pra imprimir a população:
void print_population(wug_t** population, const int size) {
    printf("--- POPULAÇÃO ATUAL (Tamanho: %d) ---\n", size);
    for (int i = 0; i < size; i++) {
        printf("%d: ", i); // Imprime a posição na lista.
        print_wug(population[i]); // Reutiliza a função print_wug.
    }
    printf("-------------------------------------\n");
}

// Função pra contar os SuperWugs:
int report_population(wug_t** population, const int size) {
    int superwug_count = 0;
    if (population == NULL) {
        return 0;
    }
    
    for (int i = 0; i < size; i++) {
        // Se o rank do wug for 4, ele é um "SuperWug".
        if (rank(population[i]) == 4) {
            superwug_count++;
        }
    }
    return superwug_count;
}

// Função de inserção organizada:
bool insert_ranked(wug_t** population, wug_t* w, int* size, int capacity) {
    int new_wug_rank = rank(w);
    int insert_pos = -1;

    // Posição correta pra inserir se baseado no rank.
    for (int i = 0; i < *size; i++) {
        if (new_wug_rank > rank(population[i])) {
            insert_pos = i;
            break;
        }
    }

    // Se não achou posição e a população não está cheia, insere no final.
    if (insert_pos == -1 && *size < capacity) {
        insert_pos = *size;
    }

    // Se não tem posição (população cheia e rank baixo), não insere.
    if (insert_pos == -1) {
        return false;
    }

    int limit = (*size < capacity) ? (*size) : (*size - 1);

    // Desloca os wugs com rank menor para a direita pra abrir espaço.
    for (int i = limit; i > insert_pos; i--) {
        population[i] = population[i - 1];
    }

    // Adiciona o novo wug.
    population[insert_pos] = w;

    // Aumenta o tamanho da população se ela já não estava cheia.
    if (*size < capacity) {
        (*size)++;
    }

    return true;
}