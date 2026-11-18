#include <stdio.h>
#include "annotation.h"
int main(void)
{
    FILE *file = fopen("datasets/Homo_sapiens.GRCh38.92.csv", "r");
    if (file == NULL) {
        printf("Could not open dataset.\n");
        return 1;
    }
    char line[8192];
    fgets(line, sizeof(line), file);
    if (fgets(line, sizeof(line), file) == NULL) {
        printf("Could not read annotation record.\n");
        fclose(file);
        return 1;
    }
    Annotation record;
    if (annotation_parse_csv_line(line, &record)) {
        printf("Parsing successful!\n");
        printf("Chromosome: %s\n", record.seqname);
        printf("Feature: %s\n", record.feature);
        printf("Start: %ld\n", record.start);
        printf("End: %ld\n", record.end);
        printf("Strand: %c\n", record.strand);
        printf("Gene ID: %s\n", record.gene_id);
        printf("Gene Name: %s\n", record.gene_name);
    } 
    else 
    {
        printf("Parsing failed!\n");
    }
    fclose(file);
    return 0;
}
