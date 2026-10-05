// htab_bucket_count.c
// Řešení DU2, část B, 25. 4. 2025
// Autor: caukub
// Přeloženo: gcc version 11.5.0 (GCC)

#include "htab_t.h"

size_t htab_bucket_count(const htab_t *t) {
    return t->arr_size;
}
