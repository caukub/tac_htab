#include <stdint.h>
#include <string.h>

#ifndef MY_HASH_FUNCTION
#define MY_HASH_FUNCTION

size_t htab_hash_function(const char *str) {
  uint32_t h=0;     // musí mít 32 bitů
  const unsigned char *p;
  for(p=(const unsigned char*)str; *p!='\0'; p++)
    h = 65599*h + *p;
  return h;
}

#endif // MY_HASH_FUNCTION