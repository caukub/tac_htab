#include "htab.h"

typedef struct htab {
    size_t size;
    size_t arr_size;
    htab_item_t *buckets[];
} htab_t;