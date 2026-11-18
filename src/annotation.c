#include "annotation.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int annotation_is_valid(const Annotation *record)
{
    if (record == NULL) {
        return 0;
    }
// Check for empty fields
    if (record->seqname[0] == '\0' || record->feature[0] == '\0') {
        return 0;
    }
//check for valid start and end positions
    if (record->start < 1 || record->end < 1) {
        return 0;
    }
//check for valid strand values
    if (record->strand != '+' && record->strand != '-' && record->strand != '.') {
        return 0;
    }
//check for valid gene_id, gene_name, and transcript_id lengths
    if (strlen(record->gene_id) >= MAX_GENE_ID_LENGTH ||  strlen(record->gene_name) >= MAX_GENE_NAME_LENGTH || strlen(record->transcript_id) >= MAX_TRANSCRIPT_ID_LENGTH) {
        return 0;
    }
//check if start is less than or equal to end
    if (record->start > record->end) {
        return 0;
    }
    return 1;
}

int annotation_parse_csv_line(const char *line, Annotation *record)
{
    if (line == NULL || record == NULL) {
        return 0;
    }
    char copy[8192];
    if (strlen(line) >= sizeof(copy)) {
        return 0;
    }
    strcpy(copy, line);
 
char *fields[32];
int count = 0;

fields[count++] = copy;

for (int i = 0; copy[i] != '\0' && count < 32; i++) {
    if (copy[i] == ',') {
        copy[i] = '\0';
        fields[count++] = &copy[i + 1];
    }

    if (copy[i] == '\n' || copy[i] == '\r') {
        copy[i] = '\0';
        break;
    }
}
    if (count < 5) {
        return 0;
    }
    memset(record, 0, sizeof(Annotation));
    snprintf(record->seqname, MAX_SEQNAME_LENGTH, "%s", fields[0]); //snprintf is used to safely copy the string into the seqname field of the record, ensuring that it does not exceed the maximum length defined by MAX_SEQNAME_LENGTH.
    snprintf(record->feature, MAX_FEATURE_LENGTH, "%s", fields[2]);
    char *end_pointer;
    record->start = strtol(fields[3], &end_pointer, 10); //strtol is used to convert the string representation of the start position (fields[3]) into a long integer. The end_pointer is used to check if the conversion was successful and if there are any remaining characters in the string after the number.
    if (*end_pointer != '\0') {
        return 0;
    }

    record->end = strtol(fields[4], &end_pointer, 10); //strtol is used to convert the string representation of the end position (fields[4]) into a long integer. The end_pointer is used to check if the conversion was successful and if there are any remaining characters in the string after the number.
    if (*end_pointer != '\0') {
        return 0;
    }

    if (count > 6 && fields[6][0] != '\0') {
        record->strand = fields[6][0];
    }

    if (count > 17) {
        snprintf(record->gene_id, MAX_GENE_ID_LENGTH, "%s", fields[17]);
    }

    if (count > 18) {
        snprintf(record->gene_name, MAX_GENE_NAME_LENGTH, "%s", fields[18]);
    }

    if (count > 27) {
        snprintf(record->transcript_id, MAX_TRANSCRIPT_ID_LENGTH,
                 "%s", fields[27]);
    }

    return annotation_is_valid(record);
}

// Counts valid and invalid records in a CSV file.
int annotation_count_records(const char *filename, size_t *record_count, size_t *invalid_count)
{
    if (filename == NULL || record_count == NULL || invalid_count == NULL) {
        return 0;
    }

    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        return 0;
    }

    *record_count = 0;
    *invalid_count = 0;

    char line[8192];
 if (fgets(line, sizeof(line), file) == NULL) {
        fclose(file);
        return 0;
    }
    while (fgets(line, sizeof(line), file) != NULL) {
        Annotation record;
        if (annotation_parse_csv_line(line, &record)) {
            (*record_count)++;
        } 
        else 
        {
            (*invalid_count)++;
        }
    }
    fclose(file);
    return 1;
}

/*annotation_is_valid()	Checks whether an annotation record is valid.
annotation_parse_csv_line()	Extracts important information from one CSV row.
annotation_count_records()	Reads the entire CSV and counts valid and invalid rows.*/
