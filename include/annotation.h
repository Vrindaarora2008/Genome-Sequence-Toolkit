#ifndef ANNOTATION_H
#define ANNOTATION_H
#include <stddef.h>
#define MAX_SEQNAME_LENGTH 32
#define MAX_FEATURE_LENGTH 32
#define MAX_GENE_ID_LENGTH 32
#define MAX_GENE_NAME_LENGTH 64
#define MAX_TRANSCRIPT_ID_LENGTH 32
typedef struct {
    char seqname[MAX_SEQNAME_LENGTH];
    char feature[MAX_FEATURE_LENGTH];
    long start;
    long end;
    char strand;
    char gene_id[MAX_GENE_ID_LENGTH];
    char gene_name[MAX_GENE_NAME_LENGTH];
    char transcript_id[MAX_TRANSCRIPT_ID_LENGTH];
} Annotation;
// Returns 1 if the coordinates are valid, otherwise 0.
int annotation_is_valid(const Annotation *record);
//Reads and counts annotation records from a CSV file.
//Returns 1 on success and 0 on failure.
int annotation_count_records(const char *filename, size_t *record_count, size_t *invalid_count); //prevents the function from being called with NULL pointers
// Parses a single annotation record from a CSV line.
int annotation_parse_csv_line(const char *line, Annotation *record);
#endif

//what was done- we added a new function declaration for annotation_count_records to read and count annotation records from a CSV file, returning 1 on success and 0 on failure. This function also takes pointers to size_t variables to store the record count and invalid count, ensuring that the function is not called with NULL pointers.
