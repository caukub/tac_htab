#include <stdbool.h>

bool htab_erase(htab_t *t, htab_key_t key) {
    size_t hash = htab_hash_function(key);
    size_t bucket_idx = (hash % htab_bucket_count(t));

    htab_item_t *bucket_ptr = t->buckets[bucket_idx];

    htab_item_t *current_item = bucket_ptr;
    htab_item_t *previous_item = NULL;

    while (current_item != NULL) {
        if (strcmp(current_item->pair.key, key) == 0) {
            if (previous_item == NULL) {
                bucket_ptr = current_item->next;
            } else {
                previous_item->next = current_item->next;
            }

            free((void *) current_item->pair.key);
            free(current_item);
            t->size -= 1;
            return true;
        }
        previous_item = current_item;
        current_item = current_item->next;
    }
    return false;
}
