#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "htab.h"
#include "htab_t.h"

htab_pair_t* htab_find(const htab_t *t, htab_key_t key) {
    size_t hash = htab_hash_function(key);
    size_t bucket_idx = (hash % htab_bucket_count(t));

    htab_item_t *bucket_ptr = t->buckets[bucket_idx];

    htab_item_t *current_item = bucket_ptr;

    while (current_item != NULL) {
        if (strcmp(current_item->pair.key, key) == 0) {
            return &(current_item->pair);
        }
        current_item = current_item->next;
    }

    return NULL;
}
