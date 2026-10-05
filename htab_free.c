// htab_free.c
// Řešení DU2, část B, 25. 4. 2025
// Autor: caukub
// Přeloženo: gcc version 11.5.0 (GCC)

#include "htab.h"
#include <stdlib.h>

void htab_free(htab_t *t) {
    htab_clear(t);
    free(t);
}
