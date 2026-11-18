#include <stdio.h>
#include <string.h>
#include "domain_index.h"
int main(void)
{
    Annotation records[6] = {0};
    snprintf(records[0].seqname, MAX_SEQNAME_LENGTH, "1");
    snprintf(records[0].gene_name, MAX_GENE_NAME_LENGTH, "DDX11L1");

    snprintf(records[1].seqname, MAX_SEQNAME_LENGTH, "2");
    snprintf(records[1].gene_name, MAX_GENE_NAME_LENGTH, "GENE_B");

    snprintf(records[2].seqname, MAX_SEQNAME_LENGTH, "1");
    snprintf(records[2].gene_name, MAX_GENE_NAME_LENGTH, "WASH7P");

    snprintf(records[3].seqname, MAX_SEQNAME_LENGTH, "X");
    snprintf(records[3].gene_name, MAX_GENE_NAME_LENGTH, "GENE_X");

    snprintf(records[4].seqname, MAX_SEQNAME_LENGTH, "2");
    snprintf(records[4].gene_name, MAX_GENE_NAME_LENGTH, "GENE_C");

    snprintf(records[5].seqname, MAX_SEQNAME_LENGTH, "1");
    snprintf(records[5].gene_name, MAX_GENE_NAME_LENGTH, "GENE_D");

    /* Build the domain index. */
    DomainIndex index = {0};

    if (!domain_index_build(index.entries == NULL ? &index : NULL,
                            records, 6)) {
        printf("Index creation failed.\n");
        return 1;
    }

    printf("Domain index created successfully!\n");

    /* Search for chromosome 1. */
    size_t first;
    size_t match_count;

    if (domain_index_search(
            &index, "1", &first, &match_count)) {

        printf("\nRecords belonging to chromosome 1:\n");

        for (size_t i = first; i < first + match_count; i++) {

            size_t original_position =
                index.entries[i].record_index;

            printf("Record index: %zu | Gene: %s\n",
                   original_position,
                   records[original_position].gene_name);
        }

        printf("\nTotal matching records: %zu\n", match_count);
    }
    else {
        printf("Chromosome not found.\n");
    }

    /* Test a chromosome that does not exist. */
    if (!domain_index_search(
            &index, "Y", &first, &match_count)) {

        printf("\nChromosome Y not found in this dataset.\n");
    }

    /* Release allocated memory. */
    domain_index_free(&index);

    return 0;
}
