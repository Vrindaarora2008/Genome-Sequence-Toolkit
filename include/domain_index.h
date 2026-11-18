
#ifndef DOMAIN_INDEX_H
#define DOMAIN_INDEX_H
#include "annotation.h"
#include <stddef.h>
//Stores a chromosome name and its original record position.
typedef struct {
    char seqname[MAX_SEQNAME_LENGTH];
    size_t record_index;
} DomainIndexEntry;
//Stores all sorted index entries.
typedef struct {
    DomainIndexEntry *entries;
    size_t count;
} DomainIndex;
//Builds the index from annotation records.
int domain_index_build(
    DomainIndex *index,
    const Annotation records[],
    size_t n
);
//Finds the range of entries belonging to a chromosome.
int domain_index_search(
    const DomainIndex *index,
    const char *seqname,
    size_t *first,
    size_t *match_count
);
void domain_index_free(DomainIndex *index);
#endif
