#include <stdlib.h>

#include "htab.h"
#include "htab_t.h"

htab_t* htab_init(size_t n) {
    htab_t *hash_table = malloc(sizeof(htab_t) + n * sizeof(htab_item_t*));

    if (hash_table == NULL) {
        // print err
        return NULL;
    }

    hash_table->size = 0;
    hash_table->arr_size = n;

    for (size_t idx = 0; idx < n; ++idx) {
        hash_table->buckets[idx] = NULL;
    }

    return hash_table;
}