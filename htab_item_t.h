#ifndef HTAB_ITEM_T__
#define HTAB_ITEM_T__

#include "htab.h"

typedef struct htab_item {
    htab_pair_t pair;
    struct htab_item *next;
} htab_item_t;

#endif
