#include <stdio.h>
#include<string.h>
#include <inttypes.h>
#include<stdint.h>
#include<limits.h>
#include"dp.h"
#include"crt.h"
#include "annotation.h"
#include <stdlib.h>
#include"genome.h"
#include "greedy.h"
#include "cli.h"
#include"flow.h"
#include"sort.h"
#include "sort.h"
#include"backtracking.h"
#include "search.h"
#include"motif_search.h"
#include "rabin_karp.h"
#include "kmp.h"
#include "finite_automaton.h"
#include "domain_index.h"
#include "divide_conquer.h"
#include <errno.h>
#include <stdlib.h>
#define MAX_MATCH_POSITIONS 10000
static int read_long_long(long long *value)
{
    char buffer[64];
    char *end;
    long long result;
    if (scanf("%63s", buffer) != 1)
        return 0;
    errno = 0;
    result = strtoll(buffer, &end, 10);
    if (errno == ERANGE || end == buffer || *end != '\0')
        return 0;
    *value = result;
    return 1;
}
void display_motif_results(const char *algorithm, size_t matches, const size_t positions[], size_t max_positions)
{
    printf("\n%s Results\n", algorithm);
    printf("Total matches found: %zu\n", matches);
    if (matches == 0)
    {
        printf("No occurrences found.\n");
        return;
    }
    printf("Starting positions (0-based): ");
    size_t displayed = matches < max_positions ? matches : max_positions;
    for (size_t i = 0; i < displayed; i++)
    {
        printf("%zu ", positions[i]);
    }
    printf("\n");
    if (matches > max_positions)
    {
        printf("Only the first %zu positions are displayed.\n",
               max_positions);
    }
}

static void display_menu(void);
static int read_menu_choice(void);
static void display_menu(void)
{
    printf("Your options are the following-\n");
    printf("1- DNA sequence Operation\n");
    printf("2- DNA annotation\n");
    printf("3- Sorting and Searching Menu\n");
    printf("4- DNA Motif\n");
    printf("5- Divide and Conquer Menu\n");
    printf("6- Greedy Algorithm Menu\n");
    printf("7- Dynamic Programming Menu\n");
    printf("8- Backtracking\n");
    printf("9- Network Flow Menu\n");
    printf("10- Chinese Remainder Theorem\n");
    printf("11- Benchmarking and Result\n");
    printf("0- Exit\n");
}

static int read_menu_choice(void)
{
    int choice;
    int ch;

    if (scanf("%d", &choice) == 1)
    {
        return choice;
    }

    if (feof(stdin))
    {
        return 0;
    }

    while ((ch = getchar()) != '\n' && ch != EOF)
    {
    }

    return -1;
}
void run_main_menu(void)
{
    int choice;
    do
    {
        display_menu();
        choice = read_menu_choice();
        switch (choice)
        {
            //DNA sequence operation
            case 1:
            DNA_sequence_menu();
                break;

            case 2:
                annotation_menu();
                break;

            case 3:
            sorting_searching_menu();
                break;

            case 4:
                motif_menu();
                break;

            case 5:
                divide_conquer_menu();
                break;

            case 6:
                greedy_algorithm_menu();
                break;

            case 7:
                dynamic_programming_menu();
                break;

            case 8:
                backtracking_menu();
                break;

            case 9:
                network_flow_menu();
                break;

            case 10:
                crt_menu();
                break;

            case 11:
                benchmarking_result_menu();
                break;

            case 0:
                printf("We are exiting");
                break;

            default:
                printf("Invalid choice");
                break;
        }

    } while (choice != 0);
}

void DNA_sequence_menu(void)
{
    DNASequence dna = {0};
    int choice;
    printf("0- Return to Main Menu\n");
    printf("1- Enter DNA sequence\n");
    printf("Enter your choice- ");
    if (scanf("%d", &choice) != 1)
    {
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF)
        {
        }
        printf("\nInvalid input!\n");
        return;
    }
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF)
    {
    }
    if(choice == 1){
        printf("Enter DNA sequence");
        fgets(dna.bases, sizeof(dna.bases), stdin);
        dna.bases[strcspn(dna.bases, "\n")] = '\0';
     if (dna_is_valid(dna.bases))
        {
            dna.length = strlen(dna.bases);
            printf("Enter sequence name\n");
            fgets(dna.name, sizeof(dna.name), stdin);
            dna.name[strcspn(dna.name, "\n")] = '\0';
            printf("\nDNA SEQUENCE DETAILS\n");
            printf("Sequence Name : %s\n", dna.name);
            printf("DNA Sequence    : %s\n", dna.bases);
            printf("Sequence Length : %zu\n", dna.length);
        }
        else
        {
            printf("\nInvalid DNA sequence!\n");
        }
    }
    else if(choice == 0)
    {
        printf("\nReturn to Main Menu.\n");
        return;
    }
    else
    {
        printf("\nInvalid choice.\n");
    }
}

void annotation_menu(void)
{
    int choice;
    size_t valid = 0, invalid = 0;
    const char *dataset_filename = "datasets/Homo_sapiens.GRCh38.92.csv";
    printf("1. Count Valid and Invalid Records\n");
    printf("0. Return to Main Menu\n");
    printf("\nEnter your choice- ");
    if (scanf("%d", &choice) != 1)
{
    int ch;

    while ((ch = getchar()) != '\n' && ch != EOF)
    {
    }

    printf("\nInvalid input!\n");
    return;
}
    if (choice == 1)
    {
        if (annotation_count_records(dataset_filename, &valid, &invalid))
        {
            printf("Valid Records: %zu\n", valid);
            printf("Invalid Records: %zu\n", invalid);
        }
        else
        {
            printf("\nError\n");
        }
    }
    else if (choice == 0)
    {
        printf("\nReturn to Main Menu\n");
        return;
    }
    else
    {
        printf("\nInvalid choice.\n");
    }
}

int load_annotation_subset(const char *filename, Annotation **records, size_t *loaded_count, size_t maximum_records)
{
    FILE *file;
    Annotation *allocated_records;
    char line[100000];
    size_t count = 0;
    *records = NULL;
    *loaded_count = 0;
    file = fopen(filename, "r");
    if (file == NULL)
    {
        return 0;
    }
    allocated_records = malloc(maximum_records * sizeof(Annotation));
    if (allocated_records == NULL)
    {
        fclose(file);
        return 0;
    }
    if (fgets(line, sizeof(line), file) == NULL)
    {
        fclose(file);
        free(allocated_records);
        return 0;
    }
    while (count < maximum_records && fgets(line, sizeof(line), file) != NULL)
    {
        Annotation temp_record;
        if (annotation_parse_csv_line(line, &temp_record))
        {
            allocated_records[count] = temp_record;
            count++;
        }
    }
    if (ferror(file))
{
    fclose(file);
    free(allocated_records);
    return 0;
}
    fclose(file);
    if (count == 0)
    {
        free(allocated_records);
        return 0;
    }
    *records = allocated_records;
    *loaded_count = count;
    return 1;
}


void sorting_searching_menu(void)
{
    int choice;
    const size_t MAX_RECORDS = 100000;
    const char *filename = "datasets/Homo_sapiens.GRCh38.92.csv";

    do
    {
        printf("1. Merge Sort\n");
        printf("2. Quick Sort\n");
        printf("3. Linear Search\n");
        printf("4. Binary Search\n");
        printf("5. Recursive Binary Search\n");
        printf("6. Domain Indexing\n");
        printf("0. Return to Main Menu\n");
        printf("\nEnter your choice- ");
        if (scanf("%d", &choice) != 1)
        {
            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF)
            {
            }
            printf("\nInvalid input.\n");
            continue;
        }

        if (choice >= 1 && choice <= 6)
        {
            Annotation *records = NULL;
            size_t count = 0;
            if (!load_annotation_subset(filename, &records, &count, MAX_RECORDS))
            {
                printf("\nUnable to load annotation records.\n");
                continue;
            }
            if (choice == 1)
            {
                merge_sort(records, 0, (int)count - 1);

                printf("\nMerge Sort completed!\n");
                printf("Records sorted: %zu\n", count);
            }
            else if (choice == 2)
            {
                quick_sort(records, 0, (int)count - 1);
                printf("\nQuick Sort completed!\n");
                printf("Records sorted: %zu\n", count);
            }

            else if (choice == 3)
            {
                long long target;
                printf("\nEnter genomic start coordinate");
                if (read_long_long(&target) != 1)
                {
                    printf("Invalid coordinate.\n");
                    free(records);
                    continue;
                }
                int result = linear_search(records, (int)count, target);
                if (result != -1)
                {
                    printf("\nRecord found!\n");
                    printf("Index: %d\n", result);
                    printf("Gene: %s\n", records[result].gene_name);
                    printf("Chromosome: %s\n", records[result].seqname);
                    printf("Start: %ld\n", records[result].start);
                }
                else
                {
                    printf("\nRecord not found.\n");
                }
            }
            else if (choice == 4)
            {
                long long target;
                merge_sort(records, 0, (int)count - 1);
                printf("\nEnter genomic start coordinate- ");
                if (read_long_long(&target) != 1)
                {
                    printf("Invalid coordinate.\n");
                    free(records);
                    continue;
                }
                int result = binary_search(records, (int)count, target);
                if (result != -1)
                {
                    printf("\nRecord found!\n");
                    printf("Index: %d\n", result);
                    printf("Gene: %s\n", records[result].gene_name);
                    printf("Chromosome: %s\n", records[result].seqname);
                    printf("Start: %ld\n", records[result].start);
                }
                else
                {
                    printf("\nRecord not found.\n");
                }
            }
            else if (choice == 5)
            {
                long long target;
                merge_sort(records, 0, (int)count - 1);
                printf("\nEnter genomic start coordinate- ");
                if (read_long_long(&target) != 1)
                {
                    printf("Invalid coordinate.\n");
                    free(records);
                    continue;
                }
                int result = recursive_binary_search(records, 0, (int)count - 1, target);
                if (result != -1)
                {
                    printf("\nRecord found!\n");
                    printf("Index: %d\n", result);
                    printf("Gene: %s\n", records[result].gene_name);
                    printf("Chromosome: %s\n", records[result].seqname);
                    printf("Start: %ld\n", records[result].start);
                }
                else
                {
                    printf("\nRecord not found.\n");
                }
            }
            else if (choice == 6)
            {
                DomainIndex index = {0};
                char chromosome[MAX_SEQNAME_LENGTH];
                size_t first = 0;
                size_t matches = 0;
                if (domain_index_build(&index, records, count))
                {
                    printf("\nEnter chromosome name (e.g. 1, 2, X, Y): ");
                    if (scanf("%31s", chromosome) == 1)
                    {
                        if (domain_index_search(&index, chromosome, &first, &matches))
                        {
                            printf("\nMatching records: %zu\n", matches);
                            for (size_t i = first; i < first + matches; i++)
                            {
                                size_t record_index = index.entries[i].record_index;

                                printf("Gene: %s | Start: %ld | End: %ld\n", records[record_index].gene_name, records[record_index].start, records[record_index].end);
                            }
                        }
                        else
                        {
                            printf("\nChromosome not found in loaded subset.\n");
                        }
                    }
                    else
                    {
                        printf("\nInvalid chromosome input.\n");
                    }
                    domain_index_free(&index);
                }
                else
                {
                    printf("\nUnable to build domain index.\n");
                }
            }

            free(records);
        }
        else if (choice == 0)
        {
            printf("\nReturn to Main Menu.\n");
        }
        else
        {
            printf("\nInvalid choice.\n");
        }
    } while (choice != 0);
}


void motif_menu(void)
{
    int choice;
    char *sequence = malloc(MAX_SEQUENCE_LENGTH + 1);
    char *motif = malloc(MAX_MOTIF_LENGTH + 1);
    size_t *positions = malloc(MAX_MATCH_POSITIONS * sizeof(size_t));
    if (sequence == NULL || motif == NULL || positions == NULL)
    {
        printf("Memory allocation failed!\n");
        free(sequence);
        free(motif);
        free(positions);
        return;
    }

    printf("\nEnter DNA sequence: ");
    if (scanf("%10000s", sequence) != 1)
    {
        printf("Error\n");
        free(sequence);
        free(motif);
        free(positions);
        return;
    }

    if (strlen(sequence) > MAX_SEQUENCE_LENGTH || !dna_is_valid(sequence))
    {
        printf("Invalid DNA sequence!\n");
        free(sequence);
        free(motif);
        free(positions);
        return;
    }
    do
    {
        printf("1. Naive Pattern Search\n");
        printf("2. Rabin-Karp Search\n");
        printf("3. KMP Search\n");
        printf("4. Finite Automaton Search\n");
        printf("5. Compare All Algorithms\n");
        printf("0. Return to Main Menu\n");
        printf("Enter choice: ");

        if (scanf("%d", &choice) != 1)
        {
            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF)
            {
            }
            printf("Invalid input. Enter a number.\n");
            choice = -1;
            continue;
        }
        if (choice == 0)
        {
            printf("Return to main menu.\n");
            break;
        }
        if (choice < 1 || choice > 5)
        {
            printf("Invalid choice.\n");
            continue;
        }
        printf("Enter motif to search");

        if (scanf("%1000s", motif) != 1)
        {
            printf("Error\n");
            continue;
        }
        if (strlen(motif) > MAX_MOTIF_LENGTH || !dna_is_valid(motif))
        {
            printf("Invalid motif!\n");
            continue;
        }
        printf("\nSearching for motif: %10000s\n", motif);
        printf("In DNA sequence: %10000s\n", sequence);
        size_t matches;
        switch (choice)
        {
            case 1:
                matches = naive_search(sequence, motif, positions, MAX_MATCH_POSITIONS);
                display_motif_results("Naive Search", matches, positions, MAX_MATCH_POSITIONS);
                break;
            case 2:
                matches = rabin_karp_search(sequence, motif, positions, MAX_MATCH_POSITIONS);
                display_motif_results("Rabin-Karp Search", matches, positions, MAX_MATCH_POSITIONS);
                break;
            case 3:
                matches = kmp_search(sequence, motif, positions, MAX_MATCH_POSITIONS);
                display_motif_results("KMP Search", matches, positions, MAX_MATCH_POSITIONS);
                break;
            case 4:
                matches = finite_automaton_search(sequence, motif, positions, MAX_MATCH_POSITIONS);
                display_motif_results("Finite Automaton Search", matches, positions, MAX_MATCH_POSITIONS);
                break;
            case 5:
                matches = naive_search(sequence, motif, positions, MAX_MATCH_POSITIONS);
                display_motif_results("Naive Search", matches,positions, MAX_MATCH_POSITIONS);
                matches = rabin_karp_search(sequence, motif, positions, MAX_MATCH_POSITIONS);
                display_motif_results("Rabin-Karp Search", matches, positions, MAX_MATCH_POSITIONS);
                matches = kmp_search(sequence, motif, positions, MAX_MATCH_POSITIONS);
                display_motif_results("KMP Search", matches, positions, MAX_MATCH_POSITIONS);
                matches = finite_automaton_search(sequence, motif, positions, MAX_MATCH_POSITIONS);
                display_motif_results("Finite Automaton Search", matches, positions, MAX_MATCH_POSITIONS);
                break;
        }
    } while (choice != 0);
    free(sequence);
    free(motif);
    free(positions);
}


void divide_conquer_menu(void)
{
    int choice;
    do
    {
        printf("1. Maximum Subarray Problem\n");
        printf("2. Fast Exponentiation\n");
        printf("3. Celebrity Problem\n");
        printf("4. Classical Matrix Multiplication\n");
        printf("5. Strassen Matrix Multiplication\n");
        printf("0. Return to Main Menu\n");
        printf("Enter choice: ");
        if (scanf("%d", &choice) != 1)
        {
            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF)
            {
            }
            printf("Invalid input.\n");
            choice = -1;
            continue;
        }
        switch (choice)
        {
            case 1:
            {
                int n;
                int arr[100];
                long long result;
                printf("Enter number of elements (1-100): ");
                if (scanf("%d", &n) != 1)
                {
                    int ch;
                    while ((ch = getchar()) != '\n' && ch != EOF){

                    }
                    printf("Invalid array size.\n");
                    break;
                }
                if (n < 1 || n > 100)
                {
                    printf("Invalid array size.\n");
                    break;
                }
                printf("Enter array elements:\n");
                int valid = 1;
                for (int i = 0; i < n; i++)
                {
                    if (scanf("%d", &arr[i]) != 1)
                    {
                        int ch;
                        while ((ch = getchar()) != '\n' && ch != EOF)
                        {

                        }
                        valid = 0;
                        break;
                    }
                }
                if (!valid) {
                    printf("Invalid array element.\n");
                    break;
                }
                if (max_subarray_sum(arr, n, &result))
                {
                    printf("Maximum subarray sum: %lld\n", result);
                }
                else
                {
                    printf("Maximum subarray calculation failed.\n");
                }

                break;
            }
            case 2:
            {
                long long base;
                long long exponent_input;
                unsigned int exponent;
                printf("Enter base: ");
                if (!read_long_long(&base))
                {
                    printf("Invalid base.\n");
                    break;
                }
                printf("Enter non-negative exponent: ");
                if (!read_long_long(&exponent_input) || exponent_input < 0 || (unsigned long long)exponent_input > UINT_MAX)
                {
                    printf("Invalid exponent.\n");
                    break;
                }
                exponent = (unsigned int)exponent_input;
                printf("Result: %lld\n", fast_power(base, exponent));
                break;
            }
            case 3:
{
    int n;
    int matrix[100];
    int valid = 1;

    printf("Enter number of people (1-10): ");

    if (scanf("%d", &n) != 1)
    {
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF)
        {
        }
        printf("Invalid number of people.\n");
        break;
    }

    if (n < 1 || n > 10)
    {
        printf("Invalid number of people.\n");
        break;
    }

    printf("Enter the acquaintance matrix (0 or 1):\n");
    printf("1 = Knows, 0 = Does not know\n");

    for (int i = 0; i < n * n; i++)
    {
        if (scanf("%d", &matrix[i]) != 1)
        {
            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF)
            {
            }
            valid = 0;
            break;
        }

        if (matrix[i] != 0 && matrix[i] != 1)
        {
            valid = 0;
            break;
        }
    }

    if (!valid)
    {
        printf("Invalid acquaintance matrix.\n");
        break;
    }

    int celebrity = find_celebrity(matrix, n);

    if (celebrity == -1)
    {
        printf("No celebrity found.\n");
    }
    else
    {
        printf("Celebrity found: Person %d\n", celebrity + 1);
    }

    break;
}
            case 4:
            case 5:
            {
                int n;
                int valid = 1;
                long long A[64], B[64], C[64];
                printf("Enter matrix dimension (1-8): ");
                if (scanf("%d", &n) != 1)
                {
                    int ch;
                    while ((ch = getchar()) != '\n' && ch != EOF)
                    {

                    }
                    printf("Invalid matrix dimension.\n");
                    break;
                }
                if (n < 1 || n > 8)
                {
                     printf("Invalid matrix dimension.\n");
                      break; 
                    }
                    printf("Enter elements of Matrix A:\n");
                    for (int i = 0; i < n * n; i++)
                    {
                        if (!read_long_long(&A[i]))
                        {
                            valid = 0;
                            break;
                        }
                    }
                    if (!valid)
                    {
                        int ch; 
                        while ((ch = getchar()) != '\n' && ch != EOF) {

                        }
                        printf("Invalid Matrix A element.\n");
                        break;
                    }
                    printf("Enter elements of Matrix B:\n");
                    for (int i = 0; i < n * n; i++)
                    {
                        if (!read_long_long(&B[i]))
                        {
                            valid = 0;
                            break;
                        }
                    }
                    if (!valid)
                    {
                        int ch;
                        while ((ch = getchar()) != '\n' && ch != EOF) {

                        }
                        printf("Invalid Matrix B element.\n");
                        break;
                    }
                    int success;
                    if (choice == 4) {
                        success = matrix_multiply_classical(A, B, C, n);
                        printf("\nClassical Matrix Multiplication:\n");
                    }
                    else
                    {
                        success = matrix_multiply_strassen(A, B, C, n);
                        printf("\nStrassen Matrix Multiplication:\n");
                    }
                    if (success)
                    {
                        for (int i = 0; i < n; i++)
                        {
                            for (int j = 0; j < n; j++)
                            {
                                printf("%lld ", C[i * n + j]);
                            }
                            printf("\n");
                        }
                    }
                    else
                    {
                        printf("Matrix multiplication failed.\n");
                    }
                    break;
                }
            case 0:
                printf("Return to main menu.\n");
                break;
            default:
                printf("Invalid choice.\n");
        }
    } while (choice != 0);
}


void greedy_algorithm_menu(void)
{
    int choice;
    do
    {
        printf("1. Activity Selection\n");
        printf("2. Interval Partitioning\n");
        printf("3. Huffman Coding\n");
        printf("4. Dijkstra's Shortest Path\n");
        printf("5. Prim's Minimum Spanning Tree\n");
        printf("6. Kruskal's Minimum Spanning Tree\n");
        printf("0. Return to Main Menu\n");
        printf("Enter choice: ");
        if (scanf("%d", &choice) != 1)
        {
            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF)
            {
            }
            printf("Invalid input.\n");
            choice = -1;
            continue;
        }
        switch (choice)
        {
            case 1:
            {
                int n;
                Activity activities[100];
                int selected[100];
                printf("Enter number of activities (1-100): ");
                scanf("%d", &n);
                if (n < 1 || n > 100)
                {
                    printf("Invalid number of activities.\n");
                    break;
                }
                for (int i = 0; i < n; i++)
                {
                    activities[i].id = i + 1;
                    printf("Activity %d start and finish: ", i + 1);
                    scanf("%d %d", &activities[i].start, &activities[i].finish);
                }
                int count = activity_selection( activities, n, selected);
                printf("\nSelected activities:\n");
                for (int i = 0; i < count; i++)
                {
                    printf("Activity %d\n", selected[i]);
                }
                printf("Total selected: %d\n", count);
                break;
            }
            case 2:
            {
                int n;
                Interval intervals[100];
                int room_assignment[100];
                printf("Enter number of intervals (1-100): ");
                if (scanf("%d", &n) != 1 || n < 1 || n > 100)
                {
                    int ch;
                    while ((ch = getchar()) != '\n' && ch != EOF) {}
                    printf("Invalid number of intervals.\n");
                    break;
                }
                int valid = 1;
                for (int i = 0; i < n; i++)
                {
                    intervals[i].id = i;
                    printf("Interval %d start and finish: ", i + 1);
                    if (scanf("%d %d", &intervals[i].start, &intervals[i].finish) != 2 || intervals[i].start > intervals[i].finish)
                    {
                        int ch;
                        while ((ch = getchar()) != '\n' && ch != EOF) {}
                        valid = 0;
                        break;
                    }
                }
                if (!valid)
                {
                    printf("Invalid interval input.\n");
                    break;
                }
                int rooms = interval_partitioning(intervals, n, room_assignment);
                printf("\nRoom assignments:\n");
                for (int i = 0; i < n; i++)
                {
                    printf("Interval %d -> Room %d\n", i + 1, room_assignment[i]);
                }
                printf("Total rooms required: %d\n", rooms);
                break;
            }
            case 3:
            {
                char text[1000];
                printf("Enter text for Huffman coding: ");
                if (scanf("%999s", text) != 1)
                {
                    printf("Error reading text.\n");
                    break;
                }
                huffman_coding(text);
                break;
            }
            case 4:
            case 5:
            {
                int n, source = 0;
                int graph[MAX_VERTICES][MAX_VERTICES];
                printf("Enter number of vertices (1-%d): ", MAX_VERTICES);
                if (scanf("%d", &n) != 1 || n < 1 || n > MAX_VERTICES)
                {
                    int ch;
                    while ((ch = getchar()) != '\n' && ch != EOF) {}
                    printf("Invalid number of vertices.\n");
                    break;
                }
                if (n < 1 || n > MAX_VERTICES)
                {
                    printf("Invalid number of vertices.\n");
                    break;
                }
                printf("Enter adjacency matrix (0 = no edge):\n");
                for (int i = 0; i < n; i++)
                {
                    for (int j = 0; j < n; j++)
                    {
                        scanf("%d", &graph[i][j]);
                    }
                }
                if (choice == 4)
                {
                    printf("Enter source vertex (1-%d): ", n);
                    scanf("%d", &source);
                    if (source < 1 || source > n)
                    {
                        printf("Invalid source vertex.\n");
                        break;
                    }
                    dijkstra(graph, n, source - 1);
                }
                else
                {
                    prim_mst(graph, n);
                }
                break;
            }
            case 6:
            {
                int vertices, edge_count;
                Edge edges[190];
                printf("Enter number of vertices (1-%d): ", MAX_VERTICES);
                if (scanf("%d", &vertices) != 1 || vertices < 1 || vertices > MAX_VERTICES)
                {
                    int ch;
                    while ((ch = getchar()) != '\n' && ch != EOF) 
                    {
                    }
                    printf("Invalid number of vertices.\n");
                    break;
                }
                printf("Enter number of edges (0-190): ");
                if (scanf("%d", &edge_count) != 1 || edge_count < 0 || edge_count > 190)
                {
                    int ch;
                    while ((ch = getchar()) != '\n' && ch != EOF) {

                    }
                    printf("Invalid number of edges.\n");
                    break;
                }
                printf("Enter each edge: source destination weight\n");
                printf("Use vertex numbers starting from 1.\n");
                int valid = 1;
                for (int i = 0; i < edge_count; i++)
                {
                    if (scanf("%d %d %d", &edges[i].src, &edges[i].dest, &edges[i].weight) != 3)
                    {
                        valid = 0;
                        break;
                    }
                    if (edges[i].src < 1 || edges[i].src > vertices || edges[i].dest < 1 || edges[i].dest > vertices)
                    {
                        valid = 0;
                        break;
                    }
                    edges[i].src--;
                    edges[i].dest--;
                }
                if (!valid)
                {
                    int ch;
                    while ((ch = getchar()) != '\n' && ch != EOF)
                    {
                    }
                    printf("Invalid edge input.\n");
                    break;
                }
                kruskal_mst(edges, vertices, edge_count);
                break;
            }
            case 0:
                printf("Return to main menu.\n");
                break;
            default:
                printf("Invalid choice.\n");
        }

    } while (choice != 0);
}

void dynamic_programming_menu(void)
{
    int choice;
    do
    {
        printf("1. 0/1 Knapsack\n");
        printf("2. Matrix Chain Multiplication\n");
        printf("3. Longest Common Subsequence (LCS)\n");
        printf("4. Optimal Binary Search Tree\n");
        printf("5. Bellman-Ford Algorithm\n");
        printf("6. Floyd-Warshall Algorithm\n");
        printf("7. Travelling Salesperson (Held-Karp)\n");
        printf("0. Return to Main Menu\n");
        printf("Enter choice: ");
        if (scanf("%d", &choice) != 1)
        {
            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF)
            {
            }

            printf("Invalid input.\n");
            choice = -1;
            continue;
        }
        switch (choice)
        {
            case 1:
            {
                int n, capacity;
                int weights[100], values[100];
                printf("Enter number of items- ");
                if (scanf("%d", &n) != 1 || n < 1 || n > 100)
                { 
                    int ch;
                    while ((ch = getchar()) != '\n' && ch != EOF) {
                    }
                    printf("Invalid number of items.\n");
                    break;
                }
                printf("Enter knapsack capacity- ");
                if (scanf("%d", &capacity) != 1 || capacity < 0 || capacity > 100000)
                {
                    printf("Invalid capacity.\n");
                    break;
                }
                for (int i = 0; i < n; i++)
                {
                    printf("Enter weight and value of item %d: ", i + 1);
                    if (scanf("%d %d", &weights[i], &values[i]) != 2 || weights[i] < 0)
                    {
                        int ch;
                        while ((ch = getchar()) != '\n' && ch != EOF)
                        {
                        }
                        printf("Invalid item input.\n");
                        break;
                    }
                }
                long long result = knapsack_01( weights, values, n, capacity);
                if (result == -1)
                    printf("Knapsack calculation failed.\n");
                else
                    printf("Maximum obtainable profit: %lld\n", result);
                break;
            }
            case 2:
            {
                int n;
                int dimensions[21];
                int split[400];
                printf("Enter number of matrices: ");

                if (scanf("%d", &n) != 1 || n < 1 || n > 20)
                {int ch;
                    while ((ch = getchar()) != '\n' && ch != EOF)
                    {
                    }
                    printf("Invalid number of matrices.\n");
                    break;
                }
                printf("Enter %d dimensions:\n", n + 1);
                int valid = 1;
                for (int i = 0; i <= n; i++)
                {
                    if (scanf("%d", &dimensions[i]) != 1 || dimensions[i] <= 0)
                    {
                        int ch;
                        while ((ch = getchar()) != '\n' && ch != EOF)
                        {
                        }
                        valid = 0;
                        break;
                    }
                }
                if (!valid)
                {
                    printf("Invalid dimensions.\n");
                    break;
                }
                long long result = matrix_chain_order(dimensions, n, split);
                if (result == -1)
                    printf("Matrix chain calculation failed.\n");
                else
                    printf("Minimum scalar multiplications: %lld\n", result);
                break;
            }
            case 3:
            {
                char a[1001], b[1001];
                char result[1001];
                printf("Enter first DNA sequence: ");
                if (scanf("%1000s", a) != 1)
                {
                    printf("Input error.\n");
                    break;
                }
                printf("Enter second DNA sequence: ");
                if (scanf("%1000s", b) != 1)
                {
                    printf("Input error.\n");
                    break;
                }
                int length = lcs_length(a, b);
                int sequence_length = lcs_sequence(a, b, result, sizeof(result));
                if (length < 0 || sequence_length < 0)
                {
                    printf("LCS calculation failed.\n");
                }
                else
                {
                    printf("LCS length: %d\n", length);
                    printf("Longest Common Subsequence: %10000s\n", result);
                }
                break;
            }
            case 4:
            {
                int n;
                int frequencies[100];
                printf("Enter number of keys- ");
                if (scanf("%d", &n) != 1 || n < 1 || n > 100)
                {
                    int ch;
                    while ((ch = getchar()) != '\n' && ch != EOF)
                    {
                    }
                    printf("Invalid number of keys.\n");
                    break;
                }
                printf("Enter search frequencies:\n");
                int valid = 1;
                for (int i = 0; i < n; i++)
                {
                    if (scanf("%d", &frequencies[i]) != 1)
                    {
                        int ch;
                        while ((ch = getchar()) != '\n' && ch != EOF)
                        {

                        }
                        valid = 0;
                        break;
                    }
                }
                if (!valid)
                {
                    printf("Invalid frequency input.\n");
                    break;
                }
                long long result = optimal_bst(frequencies, n);
                if (result == -1)
                    printf("Optimal BST calculation failed.\n");
                else
                    printf("Minimum search cost: %lld\n", result);
                break;
            }
            case 5:
            {
                int vertices, edge_count, source;
                int edges[500][3];
                long long distances[100];
                printf("Enter number of vertices-");
                if (scanf("%d", &vertices) != 1 || vertices < 1 || vertices > 100)
                {
                    printf("Invalid number of vertices.\n");
                    break;
                }
                printf("Enter number of edges- ");
                if (scanf("%d", &edge_count) != 1 || edge_count < 0 || edge_count > 500)
                {
                    int ch;
                    while ((ch = getchar()) != '\n' && ch != EOF)
                    {
                    }
                    printf("Invalid number of edges.\n");
                    break;
                }
                printf("Enter each edge: source destination weight\n");
                printf("Use vertex numbers starting from 1.\n");
                int valid = 1;
                for (int i = 0; i < edge_count; i++)
                {
                    if (scanf("%d %d %d", &edges[i][0], &edges[i][1], &edges[i][2]) != 3)
                    {
                        valid = 0;
                        break;
                    }
                    edges[i][0]--;
                    edges[i][1]--;
                }
                if (!valid)
                {
                    printf("Invalid edge input.\n");
                    break;
                }

                printf("Enter source vertex- ", vertices);
                if (scanf("%d", &source) != 1 || source < 1 || source > vertices)
                {
                    int ch;
                    while ((ch = getchar()) != '\n' && ch != EOF)
                    {
                    }
                    printf("Invalid source vertex.\n");
                    break;
                }
                int status = bellman_ford(vertices,(const int (*)[3]) edges, edge_count, source - 1, distances);
                if (status == -1)
                {
                    printf("Reachable negative weight cycle detected.\n");
                }
                else if (status == 0)
                {
                    printf("Invalid input or calculation failed.\n");
                }
                else
                {
                    printf("\nShortest distances from vertex %d:\n", source);
                    for (int i = 0; i < vertices; i++)
                    {
                        if (distances[i] == DP_INF)
                            printf("Vertex %d: Unreachable\n", i + 1);
                        else
                            printf("Vertex %d: %lld\n",
                                   i + 1, distances[i]);
                    }
                }
                break;
            }
            case 6:
            {
                int n;
                long long distances[MAX_TSP_CITIES][MAX_TSP_CITIES];
                printf("Enter number of vertices%d", MAX_TSP_CITIES);
                if (scanf("%d", &n) != 1 || n < 1 || n > MAX_TSP_CITIES)
                {
                    int ch;
                    while ((ch = getchar()) != '\n' && ch != EOF)
                    {
                    }
                    printf("Invalid number of vertices.\n");
                    break;
                }
                printf("Enter adjacency matrix:\n");
                printf("Use %lld to represent no direct edge.\n", DP_INF);
                int valid = 1;
                for (int i = 0; i < n; i++)
                {
                    for (int j = 0; j < n; j++)
                    {
                        if (read_long_long(&distances[i][j]) != 1)
                        {
                            valid = 0;
                            break;
                        }
                    }
                    if (!valid)
                        break;
                }
                if (!valid)
                {
                    int ch;
                    while ((ch = getchar()) != '\n' && ch != EOF)
                    {
                    }
                    printf("Invalid matrix input.\n");
                    break;
                }
                floyd_warshall(n, distances);
                printf("\nAll-Pairs Shortest Distance Matrix:\n");
                for (int i = 0; i < n; i++)
                {
                    for (int j = 0; j < n; j++)
                    {
                        if (distances[i][j] == DP_INF)
                            printf("%8s", "INF");
                        else
                            printf("%8lld", distances[i][j]);
                    }
                    printf("\n");
                }
                break;
            }
            case 7:
            {
                int n;
                long long graph[MAX_TSP_CITIES][MAX_TSP_CITIES];
                printf("Enter number of cities (2-%d): ", MAX_TSP_CITIES);
                if (scanf("%d", &n) != 1 || n < 2 || n > MAX_TSP_CITIES)
                {
                    int ch;
                    while ((ch = getchar()) != '\n' && ch != EOF)
                    {
                    }
                    printf("Invalid number of cities.\n");
                    break;
                }
                printf("Enter cost matrix:\n");
                printf("Use %lld to represent no direct route.\n", DP_INF);
                int valid = 1;
                for (int i = 0; i < n; i++)
                {
                    for (int j = 0; j < n; j++)
                    {
                        if (read_long_long(&graph[i][j]) != 1)
                        {
                            valid = 0;
                            break;
                        }
                    }
                    if (!valid)
                        break;
                }
                if (!valid)
                {
                    int ch;
                    while ((ch = getchar()) != '\n' && ch != EOF)
                    {
                    }
                    printf("Invalid matrix input.\n");
                    break;
                }
                long long result = tsp_held_karp(n,(const long long (*)[MAX_TSP_CITIES]) graph);
                if (result == -1)
                    printf("No valid tour found or calculation failed.\n");
                else
                    printf("Minimum travelling cost: %lld\n", result);
                break;
            }
            case 0:
                printf("Return to main menu.\n");
                break;
            default:
                printf("Invalid choice.\n");
        }
    } while (choice != 0);
}

void backtracking_menu(void)
{
    int choice;
    do
    {
        printf("1. N-Queens Problem\n");
        printf("2. Subset Sum Problem\n");
        printf("3. Branch-and-Bound Knapsack\n");
        printf("0. Return to Main Menu\n");
        printf("Enter choice: ");
        if (scanf("%d", &choice) != 1)
        {
            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF)
            {
            }
            printf("Invalid input.\n");
            choice = -1;
            continue;
        }
        switch (choice)
        {
            case 1:
            {
                int n;
                int solution[MAX_NQUEENS];
                printf("Enter number of queens (1-%d): ", MAX_NQUEENS);
                if (scanf("%d", &n) != 1 || n < 1 || n > MAX_NQUEENS)
                {
                    printf("Invalid board size.\n");
                    break;
                }

                long long count = nqueens_solve(n, solution);
                if (count < 0)
                {
                    printf("N-Queens calculation failed.\n");
                }
                else if (count == 0)
                {
                    printf("No solutions found.\n");
                }
                else
                {
                    printf("Total solutions: %lld\n", count);
                    printf("One valid solution (column per row): ");
                    for (int i = 0; i < n; i++)
                    {
                        printf("%d ", solution[i]);
                    }
                    printf("\n");
                }
                break;
            }
            case 2:
            {
                int n;
                int values[100];
                int selected[100];
                long long target;
                printf("Enter number of elements- ");
                if (scanf("%d", &n) != 1 || n < 1 || n > 100)
                {
                    printf("Invalid number of elements.\n");
                    break;
                }
                printf("Enter the elements:\n");
                int valid = 1;
                for (int i = 0; i < n; i++)
                {
                    if (scanf("%d", &values[i]) != 1)
                    {
                        valid = 0;
                        break;
                    }
                }
                if (!valid)
                {
                    printf("Invalid element input.\n");
                    break;
                }
                printf("Enter target sum: ");
                if (read_long_long(&target) != 1)
                {
                    printf("Invalid target.\n");
                    break;
                }
                int status = subset_sum_find(values, n, target, selected);
                if (status == -1)
                {
                    printf("Subset Sum calculation failed.\n");
                }
                else if (status == 0)
                {
                    printf("No subset with the target sum exists.\n");
                }
                else
                {
                    long long sum = 0;
                    printf("Subset found: ");
                    for (int i = 0; i < n; i++)
                    {
                        if (selected[i])
                        {
                            printf("%d ", values[i]);
                            sum += values[i];
                        }
                    }
                    printf("\nSubset sum: %lld\n", sum);
                }
                break;
            }
            case 3:
            {
                int n, capacity;
                int weights[63], values[63];
                int selected[63];
                long long best_profit;
                long long max_nodes;
                int strategy_choice;
                printf("Enter number of items- ");

                if (scanf("%d", &n) != 1 || n < 1 || n > 63)
                {
                    printf("Invalid number of items.\n");
                    break;
                }
                printf("Enter knapsack capacity: ");
                if (scanf("%d", &capacity) != 1 || capacity < 0)
                {
                    printf("Invalid capacity.\n");
                    break;
                }
                printf("Enter weight and value of each item:\n");
                int valid = 1;
                for (int i = 0; i < n; i++)
                {
                    printf("Item %d: ", i + 1);
                    if (scanf("%d %d", &weights[i], &values[i]) != 2)
                    {
                        valid = 0;
                        break;
                    }
                }
                if (!valid)
                {
                    printf("Invalid item input.\n");
                    break;
                }
                printf("\nSelect Branch-and-Bound strategy:\n");
                printf("1. FIFO\n");
                printf("2. LIFO\n");
                printf("3. Least-Cost / Best-Bound\n");
                printf("Enter strategy: ");
                if (scanf("%d", &strategy_choice) != 1 || strategy_choice < 1 || strategy_choice > 3)
                {
                    printf("Invalid strategy.\n");
                    break;
                }
                printf("Enter maximum node expansions: ");
                if (read_long_long(&max_nodes) != 1 ||
                    max_nodes <= 0)
                {
                    printf("Invalid node limit.\n");
                    break;
                }
                BnBStrategy strategy = (BnBStrategy)strategy_choice;
                int status = bnb_knapsack(weights, values, n, capacity, strategy, max_nodes, &best_profit, selected);
                if (status == 1)
                {
                    printf("\nOptimal profit: %lld\n", best_profit);
                    printf("Selected items: ");

                    for (int i = 0; i < n; i++)
                    {
                        if (selected[i])
                        {
                            printf("%d ", i + 1);
                        }
                    }
                    printf("\n");
                }
                else if (status == -2)
                {
                    printf("Node expansion limit reached.\n");
                }
                else if (status == -1)
                {
                    printf("Memory allocation or processing failed.\n");
                }
                else
                {
                    printf("Invalid input or item constraints.\n");
                }
                break;
            }
            case 0:
                printf("Returning to main menu...\n");
                break;
            default:
                printf("Invalid choice.\n");
        }
    } while (choice != 0);
}

void network_flow_menu(void)
{
 int choice;
    do
    {
        printf("1. Ford-Fulkerson Maximum Flow\n");
        printf("2. Maximum Bipartite Matching\n");
        printf("0. Return to Main Menu\n");
        printf("Enter choice: ");
        if (scanf("%d", &choice) != 1)
        {
            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF)
            {
            }
            printf("Invalid input.\n");
            choice = -1;
            continue;
        }
        switch (choice)
        {
            case 1:   {
            int vertices, source, sink;
            if (scanf("%d", &vertices) != 1 ||vertices <= 0 || vertices > FLOW_MAX_VERTICES)
            {
                printf("Invalid number of vertices.\n");
                break;
            }
            int capacity[FLOW_MAX_VERTICES][FLOW_MAX_VERTICES];
            printf("Enter source vertex (0 to %d): ", vertices - 1);
            if (scanf("%d", &source) != 1 || source < 0 || source >= vertices)
            {
                printf("Invalid source vertex.\n");
                break;
            }
            printf("Enter sink vertex (0 to %d): ", vertices - 1);
            if (scanf("%d", &sink) != 1 || sink < 0 || sink >= vertices || sink == source)
            {
                printf("Invalid sink vertex.\n");
                break;
            }
            printf("Enter the capacity matrix:\n");
            int valid = 1;
            for (int i = 0; i < vertices; i++)
            {
                for (int j = 0; j < vertices; j++)
                {
                    printf("Capacity from vertex %d to %d: ", i, j);
                    if (scanf("%d", &capacity[i][j]) != 1 || capacity[i][j] < 0)
                    {
                        valid = 0;
                        break;
                    }
                }
                if (!valid)
                break;
            }
            if (!valid)
            {
                printf("Invalid capacity matrix. Capacities must be non-negative integers.\n");
                break;
            }
            long long result = ford_fulkerson(capacity, vertices, source, sink);
            if (result == -1)
            {
                printf("Invalid input or network configuration.\n");
            }
            else
            {
                printf("Maximum flow: %lld\n", result);
            }
            break;
        }
            case 2:
            {
            int left, right_count;
                int adjacency[FLOW_MAX_VERTICES][FLOW_MAX_VERTICES];
                int left_match[FLOW_MAX_VERTICES];
                int right_match[FLOW_MAX_VERTICES];
                printf("Enter number of left vertices: ");
                if (scanf("%d", &left) != 1)
                {
                    int ch;
                    while ((ch = getchar()) != '\n' && ch != EOF)
                    {
                    }
                    printf("Invalid input.\n");
                    break;
                }
                printf("Enter number of right vertices: ");
                if (scanf("%d", &right_count) != 1)
                {
                    int ch;
                    while ((ch = getchar()) != '\n' && ch != EOF)
                    {
                    }
                    printf("Invalid input.\n");
                    break;
                }
                if (left <= 0 || left > FLOW_MAX_VERTICES ||
                    right_count <= 0 || right_count > FLOW_MAX_VERTICES)
                {
                    int ch;
                    while ((ch = getchar()) != '\n' && ch != EOF)
                    {
                    }
                    printf("Invalid number of vertices.\n");
                    break;
                }
                printf("Enter the adjacency matrix (0 or 1):\n");
                int valid = 1;
                for (int i = 0; i < left; i++)
                {
                    for (int j = 0; j < right_count; j++)
                    {
                        printf("Connection from left %d to right %d: ", i, j);
                        if (scanf("%d", &adjacency[i][j]) != 1 || (adjacency[i][j] != 0 && adjacency[i][j] != 1))
                        {
                            printf("Invalid matrix input");
                            valid = 0;
                            break;
                        }
                    }
                    if (!valid)
                        break;
                }
                if (!valid)
                {
                    printf("Invalid matrix input.\n");
                    break;
                }
                int result = maximum_bipartite_matching(left, right_count, adjacency, left_match, right_match);
                if (result == -1)
                {
                    printf("Invalid input or network configuration.\n");
                }
                else
                {
                    printf("Maximum matching size: %d\n", result);
                    printf("Assignments:\n");
                    for (int i = 0; i < left; i++)
                    {
                        if (left_match[i] != -1)
                        {
                            printf("Left vertex %d -> Right vertex %d\n", i, left_match[i]);
                        }
                    }
                }
                break;
        }
        default : {
            printf("Invalid choice");
        }
    }
}while(choice != 0);
}

void crt_menu(void)
{
    int choice;
    do
    {
        printf("1. Solve a system of congruences\n");
        printf("0. Return to Main Menu\n");
        printf("Enter choice: ");
        if (scanf("%d", &choice) != 1)
        {
            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF)
            {
            }
            printf("Invalid input.\n");
            choice = -1;
            continue;
        }
        switch (choice)
        {
            case 1:
            {
                size_t n;
                long long residues[CRT_MAX_EQUATIONS];
                long long moduli[CRT_MAX_EQUATIONS];
                long long solution;
                long long combined_modulus;
                printf("Enter number of equations (1-%d): ", CRT_MAX_EQUATIONS);
                long long n_input;
                if (!read_long_long(&n_input))
                {
                    printf("Invalid input.\n");
                    break;
                }
                if (n_input < 1 || n_input > CRT_MAX_EQUATIONS)
                {
                    printf("Invalid number of equations.\n");
                    break;
                }
                n = (size_t)n_input;
                printf("\nEnter each residue and modulus:\n");
                int valid = 1;
                for (size_t i = 0; i < n; i++)
                {
                    printf("Equation %zu (residue): ", i + 1);
                    if (read_long_long(&residues[i]) != 1)
                    {
                        valid = 0;
                        break;
                    }
                    printf("Equation %zu (modulus): ", i + 1);
                    if (read_long_long(&moduli[i]) != 1)
                    {
                        valid = 0;
                        break;
                    }
                }
                if (!valid)
                {
                    printf("Invalid input.\n");
                    break;
                }
                int status = chinese_remainder_theorem(residues, moduli,n, &solution, &combined_modulus);
                if (status == 1)
                {
                    printf("\nSolution: x = %lld\n", solution);
                    printf("Combined modulus: %lld\n", combined_modulus);
                    printf("\nVerification:\n");
                    for (size_t i = 0; i < n; i++)
                    {
                        printf("%lld mod %lld = %lld\n", solution, moduli[i], solution % moduli[i]);
                    }
                }
                else
                {
                    printf("CRT could not solve the given system.\n");
                }
                break;
            }
            case 0:
                printf("Return to Main Menu.\n");
                break;
            default:
                printf("Invalid choice.\n");
                break;
        }

    } while (choice != 0);
}

void benchmarking_result_menu(void)
{
    int choice;
    do
    {
        printf("\nBENCHMARK RESULTS MENU\n");
        printf("1. View Motif Search Benchmark Results\n");
        printf("0. Return to Main Menu\n");
        printf("Enter choice: ");
        if (scanf("%d", &choice) != 1)
        {
            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF)
            {
            }
            printf("Invalid input.\n");
            choice = -1;
            continue;
        }
        switch (choice)
        {
            case 1:
            {
                FILE *file;
                char line[512];
                file = fopen("results/motif_benchmark.csv", "r");
                if (file == NULL)
                {
                    printf("Benchmark results file not found.\n");
                    printf("Run the separate motif benchmark program first.\n");
                    break;
                }
                if (fgets(line, sizeof(line), file) == NULL)
                {
                    printf("Benchmark file is empty.\n");
                    fclose(file);
                    break;
                }
                printf("\nMOTIF SEARCH BENCHMARK RESULTS\n\n");
                printf("%-12s %-12s %-20s %-10s %-12s %-15s\n", "Sequence", "Motif", "Algorithm", "Matches", "Repetitions", "Average(ms)");
                int records = 0;
                while (fgets(line, sizeof(line), file) != NULL)
                {
                    size_t sequence_length;
                    size_t motif_length;
                    size_t matches;
                    int repetitions;
                    double total_time;
                    double average_time;
                    char algorithm[64];
                    char seq_text[32];
                    char motif_text[32];
                    char matches_text[32];
                    char repetitions_text[32];
                    char total_text[32];
                    char average_text[32];
                    int fields = sscanf(line, "%31[^,],%31[^,],%63[^,],%31[^,],%31[^,],%31[^,],%31[^\r\n]", seq_text, motif_text, algorithm, matches_text, repetitions_text,total_text, average_text);
                    printf("DEBUG: fields = %d | row = %s", fields, line);
                    if (fields == 7)
                    {
                        sequence_length = (size_t)strtoul(seq_text, NULL, 10);
                        motif_length = (size_t)strtoul(motif_text, NULL, 10);
                        matches = (size_t)strtoul(matches_text, NULL, 10);
                        repetitions = (int)strtol(repetitions_text, NULL, 10);
                        total_time = strtod(total_text, NULL);
                        average_time = strtod(average_text, NULL);
                        printf("%-12zu %-12zu %-20s %-10zu %-12d %-15.6f %-15.6f\n", sequence_length, motif_length, algorithm, matches, repetitions,total_time, average_time);
                        records++;
                    }
                }
                if (records == 0)
                {
                    printf("No valid benchmark records found.\n");
                }
                else
                {
                    printf("\nTotal benchmark records: %d\n", records);
                }
                fclose(file);
                break;
            }
            case 0:
                printf("Return to Main Menu.\n");
                break;
            default:
                printf("Invalid choice.\n");
                break;
        }
    } while (choice != 0);
}
