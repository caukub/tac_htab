#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "htab.h"
#include <ctype.h>

/*
Počet bucketů v hashtablu by v ideálním případě neměl být nižší než počet ukládaných položek
Z hlediska efektivity (rychlosti) je vhodné aby počet bucketů byla mocnina 2
Vzhledem k očekávané velikosti testovaných dat jsem vybral hashtable o
velikosti ~32 000 bucketů
*/
#define HASH_TABLE_SIZE 32768

unsigned most_frequent_count = 0;

void calc_most_frequent_count(htab_pair_t *pair) {
    if (pair->value > most_frequent_count) {
        most_frequent_count = pair->value;
    }
}

void print_most_frequenst_words(htab_pair_t *pair) {
    if (pair->value == most_frequent_count) {
        printf("%s\t%d\n", pair->key, pair->value);
    }
}

void add_word(htab_t *hash_table, htab_key_t key) {
    htab_pair_t *pair = htab_lookup_add(hash_table, key);

    if (pair == NULL) {
        fprintf(stderr, "htab_lookup_add returned NULL (allocation failed), exiting..");
        exit(1);
    }

    pair->value += 1;
}

int main(const int argc, const char *argv[]) {
    htab_t *hash_table = htab_init(HASH_TABLE_SIZE);

    if (hash_table == NULL) {
        fprintf(stderr, "htab_init returned NULL (allocation failed), exiting..");
        exit(1);
    }

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

    htab_for_each(hash_table, &calc_most_frequent_count);
    htab_for_each(hash_table, &print_most_frequenst_words);

    htab_free(hash_table);
}