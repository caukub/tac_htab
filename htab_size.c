// htab_size.c
// Řešení IJC-DU2, část B, 25. 4. 2025
// Autor: Jakub Trumpeš (xtrumpj00), FIT
// Přeloženo: gcc version 11.5.0 (GCC)

#include "htab_t.h"

size_t htab_size(const htab_t *t) {
    return t->size;
}