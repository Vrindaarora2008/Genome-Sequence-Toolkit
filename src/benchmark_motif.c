#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "motif_search.h"
#include "rabin_karp.h"
#include "kmp.h"
#include "finite_automaton.h"
#define MOTIF "ACGTACGT"
#define REPETITIONS 100
#define NUM_ALGORITHMS 4
typedef size_t (*SearchFunction)(
    const char *, const char *, size_t [], size_t
);
typedef struct {
    const char *name;
    SearchFunction function;
} Algorithm;
static void generate_dna(char *dna, size_t length)
{
    const char bases[] = "ACGT";
    unsigned int seed = 42;
    for (size_t i = 0; i < length; i++) {
        seed = seed * 1103515245u + 12345u;
        dna[i] = bases[(seed / 65536u) % 4u];
    }
    dna[length] = '\0';
    size_t motif_length = strlen(MOTIF);
    for (size_t i = 1000; i + motif_length <= length; i += 10000) {
        memcpy(dna + i, MOTIF, motif_length);
    }
}
static int results_match(
    const size_t expected[],
    size_t expected_count,
    const size_t actual[],
    size_t actual_count)
{
    if (expected_count != actual_count) {
        return 0;
    }
    return memcmp(expected,actual,expected_count * sizeof(size_t)) == 0;
}
static int benchmark_algorithm(
    const Algorithm *algorithm,
    const char *dna,
    const char *motif,
    size_t dna_length,
    const size_t expected_positions[],
    size_t expected_count,
    size_t *actual_positions,
    FILE *csv)
{
    size_t motif_length = strlen(motif);
    size_t count;
    count = algorithm->function(dna, motif, actual_positions, dna_length + 1);
    if (!results_match(expected_positions, expected_count, actual_positions, count)) {
        printf("ERROR: %s produced incorrect results!\n", algorithm->name);
        return 0;
    }
    clock_t start = clock();
    for (int i = 0; i < REPETITIONS; i++) {
        count = algorithm->function(dna, motif, actual_positions, dna_length + 1);
    }
    clock_t end = clock();
    double total_ms = ((double)(end - start) * 1000.0) / CLOCKS_PER_SEC;
    double average_ms = total_ms / REPETITIONS;
    printf("%-20s %10zu %12.4f ms\n", algorithm->name, count, average_ms);
    fprintf(csv,
            "%zu,%zu,%s,%zu,%d,%.6f,%.6f\n",
            dna_length,
            motif_length,
            algorithm->name,
            count,
            REPETITIONS,
            total_ms,
            average_ms);

    return 1;
}
int main(void)
{
    const size_t dataset_sizes[] = {
        10000,
        100000,
        500000
    };
    const Algorithm algorithms[NUM_ALGORITHMS] = {
        {"Naive", naive_search},
        {"Rabin-Karp", rabin_karp_search},
        {"KMP", kmp_search},
        {"Finite Automaton", finite_automaton_search}
    };
    FILE *csv = fopen(
        "results/motif_benchmark.csv", "w"
    );
    if (csv == NULL) {
        printf("Error\n");
        return 1;
    }
    fprintf(csv,
        "sequence_length,motif_length,algorithm,"
        "matches,repetitions,total_time_ms,average_time_ms\n"
    );
    printf("DNA MOTIF SEARCH BENCHMARK\n");
    printf("\n");
    for (size_t d = 0; d < sizeof(dataset_sizes) / sizeof(dataset_sizes[0]); d++) {
        size_t n = dataset_sizes[d];
        char *dna = malloc((n + 1) * sizeof(char));
        size_t *expected = malloc((n + 1) * sizeof(size_t));
        size_t *actual = malloc((n + 1) * sizeof(size_t));
        if (dna == NULL || expected == NULL || actual == NULL) {
            printf("Memory allocation failed.\n");
            free(dna);
            free(expected);
            free(actual);
            fclose(csv);
            return 1;
        }
        generate_dna(dna, n);
        size_t expected_count = naive_search(dna, MOTIF, expected, n + 1);
        printf("\nSequence length: %zu bases\n", n);
        printf("Motif: %s\n", MOTIF);
        printf("Verified matches: %zu\n\n", expected_count);
        printf("%-20s %-10s %s\n","Algorithm", "Matches", "Average time");
        printf("\n");
        for (int a = 0; a < NUM_ALGORITHMS; a++) {
            if (!benchmark_algorithm(&algorithms[a], dna, MOTIF, n, expected, expected_count, actual, csv)) {
                free(dna);
                free(expected);
                free(actual);
                fclose(csv);
                return 1;
            }
        }
        free(dna);
        free(expected);
        free(actual);
    }
    fclose(csv);
    printf("\nBenchmark completed successfully!\n");
    printf("Results saved to results/motif_benchmark.csv\n");
    return 0;
}
