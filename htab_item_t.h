// htab_item_t.h
// Řešení IJC-DU2, část B, 25. 4. 2025
// Autor: Jakub Trumpeš (xtrumpj00), FIT
// Přeloženo: gcc version 11.5.0 (GCC)

#ifndef HTAB_ITEM_T__
#define HTAB_ITEM_T__

#include "htab.h"

typedef struct htab_item {
    htab_pair_t pair;
    struct htab_item *next;
} htab_item_t;

#endif
