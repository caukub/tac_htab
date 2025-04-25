// htab_free.c
// Řešení IJC-DU2, část B, 25. 4. 2025
// Autor: Jakub Trumpeš (xtrumpj00), FIT
// Přeloženo: gcc version 11.5.0 (GCC)

#include "htab.h"
#include <stdlib.h>

void htab_free(htab_t *t) {
    htab_clear(t);
    free(t);
}
