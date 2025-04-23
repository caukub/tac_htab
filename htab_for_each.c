#include "htab_item_t.h"
#include "htab.h"
#include "htab_t.h"

void htab_for_each(const htab_t *t, void (*f)(htab_pair_t *data)) {
    for (size_t idx = 0; idx < htab_bucket_count(t); ++idx) {
        htab_item_t *current_item = t->buckets[idx];

        while (current_item != NULL) {
            f(&current_item->pair);
            current_item = current_item->next;
        }
    }
}