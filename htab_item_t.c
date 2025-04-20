#include "htab.h"

struct htab_item {
    htab_pair_t pair;
    struct htab_item *next;
} htab_item_t;