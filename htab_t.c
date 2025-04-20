#include "htab.h"
#include "htab_item_t"

typedef struct htab {
    size_t size;
    size_t arr_size;
    htab_item_t *buckets[];
} htab_t;