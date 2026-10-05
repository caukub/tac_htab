// maxwordcount.c
// Řešení DU2, část B, 25. 4. 2025
// Autor: caukub
// Přeloženo: gcc version 11.5.0 (GCC)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "htab.h"
#include "io.h"

/*
Počet bucketů v hashtablu by v ideálním případě neměl být nižší než počet ukládaných položek
Také je z hlediska efektivity (resp. rychlosti) vhodné, aby počet bucketů bylo číslo které je mocnina dvou
Vzhledem k očekávané velikosti testovaných dat jsem vybral hashtable o velikosti ~32 000 bucketů
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

int main(void) {
    htab_t *hash_table = htab_init(HASH_TABLE_SIZE);

    if (hash_table == NULL) {
        fprintf(stderr, "htab_init returned NULL (allocation failed), exiting..");
        exit(1);
    }

    #define LINE_LIMIT 256

    char word[LINE_LIMIT];

    while (read_word(LINE_LIMIT, word, stdin) != EOF) {
        add_word(hash_table, word);
    }

    htab_for_each(hash_table, &calc_most_frequent_count);
    htab_for_each(hash_table, &print_most_frequenst_words);

    htab_free(hash_table);
}
