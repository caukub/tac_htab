// htab_size.c
// Řešení DU2, část B, 25. 4. 2025
// Autor: caukub
// Přeloženo: gcc version 11.5.0 (GCC)

#include "htab_t.h"

size_t htab_size(const htab_t *t) {
    return t->size;
}