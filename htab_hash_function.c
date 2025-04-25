// htab_hash_function.c
// Řešení IJC-DU2, část B, 25. 4. 2025
// Autor: Jakub Trumpeš (xtrumpj00), FIT
// Přeloženo: gcc version 11.5.0 (GCC)

#include <stdint.h>
#include <string.h>

size_t htab_hash_function(const char *str) {
  uint32_t h=0;     // musí mít 32 bitů
  const unsigned char *p;
  for(p=(const unsigned char*)str; *p!='\0'; p++)
    h = 65599*h + *p;
  return h;
}
