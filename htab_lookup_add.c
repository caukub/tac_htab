// htab_lookup_add.c
// Řešení DU2, část B, 25. 4. 2025
// Autor: caukub
// Přeloženo: gcc version 11.5.0 (GCC)

#define _POSIX_C_SOURCE 200809L

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "htab.h"
#include "htab_t.h"

htab_pair_t* htab_lookup_add(htab_t *t, htab_key_t key) {
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

    htab_item_t *new_item = malloc(sizeof(htab_item_t));

    if (new_item == NULL) {
        return NULL;
    }

    new_item->pair.key = strdup(key);

    if (new_item->pair.key == NULL) {
        free(new_item);
        return NULL;
    }
    new_item->pair.value = 0;
    
    new_item->next = t->buckets[bucket_idx];
    t->buckets[bucket_idx] = new_item;

    t->size += 1;

    return &(new_item->pair);
}
