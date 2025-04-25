// htab_t.h
// Řešení IJC-DU2, část B, 25. 4. 2025
// Autor: Jakub Trumpeš (xtrumpj00), FIT
// Přeloženo: gcc version 11.5.0 (GCC)

#include "htab.h"
#include "htab_item_t.h"

typedef struct htab {
    size_t size;
    size_t arr_size;
    htab_item_t *buckets[];
} htab_t;
