// htab_clear.c
// Řešení DU2, část B, 25. 4. 2025
// Autor: caukub
// Přeloženo: gcc version 11.5.0 (GCC)

#include <stdlib.h>

#include "htab_t.h"

void htab_clear(htab_t *t) {
    for (size_t idx = 0; idx < htab_bucket_count(t); ++idx) {
        htab_item_t *current_item = t->buckets[idx];

        while (current_item != NULL) {
            htab_item_t *next_item = current_item->next;
            
            free((void *) current_item->pair.key);
            free(current_item);
            
            current_item = next_item;
        }

        t->buckets[idx] = NULL;
    }
}
