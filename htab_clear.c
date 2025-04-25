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
