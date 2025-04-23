#include <stdio.h>
#include "htab.h"

#include <stdio.h>
#include <unistd.h>

void add(htab_t *hash_table, htab_key_t key) {
    htab_pair_t *pair = htab_lookup_add(hash_table, key);
    pair->value += 1;
}
int main(const int argc, const char *argv[]) {
    htab_t *hash_table = htab_init(3);

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

    htab_pair_t *pair = htab_lookup_add(hash_table, "all");
    printf("%d\n", pair->value);

    htab_free(hash_table);
}