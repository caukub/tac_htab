#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "htab.h"

#define HASH_TABLE_SIZE 30000

unsigned max_words = 0;

void calc_max_words(htab_pair_t *pair) {
    if (pair->value > max_words) {
        max_words = pair->value;
    }
}

void print_max_words(htab_pair_t *pair) {
    if (pair->value == max_words) {
        printf("%s\t%d\n", pair->key, pair->value);
    }
}

void add_word(htab_t *hash_table, htab_key_t key) {
    htab_pair_t *pair = htab_lookup_add(hash_table, key);
    pair->value += 1;
}

int main(const int argc, const char *argv[]) {
    htab_t *hash_table = htab_init(HASH_TABLE_SIZE);

    char word[256];
    int c, i = 0;

    while ((c = getchar()) != EOF) {
        if (isspace(c)) {
            if (i > 0) {
                word[i] = '\0';
                add_word(hash_table, word);
                i = 0;
            }
        } else {
            if (i < 256 - 1) {
                word[i++] = (char)c;
            }
        }
    }

    if (i > 0) {
        word[i] = '\0';
        add_word(hash_table, word);
    }

    htab_for_each(hash_table, &calc_max_words);
    htab_for_each(hash_table, &print_max_words);

    htab_free(hash_table);
}