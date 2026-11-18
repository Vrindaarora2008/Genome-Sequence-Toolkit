#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "domain_index.h"
static int compare_entries(const void *a, const void *b)
{
    const DomainIndexEntry *entry_a = a;
    const DomainIndexEntry *entry_b = b;
    int result = strcmp(entry_a->seqname, entry_b->seqname);
    if (result != 0) {
        return result;
    }
    if (entry_a->record_index < entry_b->record_index) {
        return -1;
    }
    if (entry_a->record_index > entry_b->record_index) {
        return 1;
    }

    return 0;
}
/* Builds a sorted index of chromosome names. */
int domain_index_build(DomainIndex *index, const Annotation records[], size_t n)
{
    if (index == NULL || (records == NULL && n > 0)) {
        return 0;
    }
    index->entries = NULL;
    index->count = 0;
    if (n == 0) {
        return 1;
    }
    if (n > (size_t)-1 / sizeof(DomainIndexEntry)) {
        return 0;
    }
    index->entries = malloc(n * sizeof(DomainIndexEntry));
    if (index->entries == NULL) {
        return 0;
    }
    for (size_t i = 0; i < n; i++) {
        if (records[i].seqname[0] == '\0') {
            continue;
        }
        snprintf(index->entries[index->count].seqname, MAX_SEQNAME_LENGTH,"%s", records[i].seqname);
        index->entries[index->count].record_index = i;
        index->count++;
    }
    qsort(
        index->entries,
        index->count,
        sizeof(DomainIndexEntry),
        compare_entries
    );
    return 1;
}
int domain_index_search(const DomainIndex *index,const char *seqname,size_t *first,size_t *match_count)
{
    if (index == NULL || seqname == NULL || first == NULL || match_count == NULL) {
        return 0;
    }
    *first = 0;
    *match_count = 0;
    size_t left = 0;
    size_t right = index->count;
    while (left < right) {
        size_t middle = left + (right - left) / 2;
        if (strcmp(index->entries[middle].seqname, seqname) < 0) {
            left = middle + 1;
        } 
        else {
            right = middle;
        }
    }
    size_t lower_bound = left;
    if (lower_bound == index->count || strcmp(index->entries[lower_bound].seqname, seqname) != 0) {
        return 0;
    }
    left = lower_bound;
    right = index->count;
    while (left < right) {
        size_t middle = left + (right - left) / 2;
        if (strcmp(index->entries[middle].seqname, seqname) <= 0) {
            left = middle + 1;
        } 
        else {
            right = middle;
        }
    }
    *first = lower_bound;
    *match_count = left - lower_bound;
    return 1;
}
void domain_index_free(DomainIndex *index)
{
    if (index != NULL) {
        free(index->entries);
        index->entries = NULL;
        index->count = 0;
    }
}
