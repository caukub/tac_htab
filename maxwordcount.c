#include <stdio.h>
#include "htab.h"

#include <stdio.h>

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

void add(htab_t *hash_table, htab_key_t key) {
    htab_pair_t *pair = htab_lookup_add(hash_table, key);
    pair->value += 1;
}

int main(const int argc, const char *argv[]) {
    htab_t *hash_table = htab_init(HASH_TABLE_SIZE);

    FILE *file = fopen("ahoj.txt", "r");

    if (file == NULL) {
        printf("Chyba při otevírání souboru!\n");
        return 1;
    }

    char word[256];

    while (fscanf(file, "%s", word) == 1) {
        add(hash_table, word);
    }

    fclose(file);

    htab_for_each(hash_table, &calc_max_words);
    htab_for_each(hash_table, &print_max_words);

    htab_free(hash_table);
}