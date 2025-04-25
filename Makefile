# Makefile
# Řešení IJC-DU2, část A + B, 25. 4. 2025
# Autor: Jakub Trumpeš (xtrumpj00), FIT
# Přeloženo: gcc version 11.5.0 (GCC)

CC = gcc
CFLAGS = -O2 -Wall -std=c11 -fPIC
PROGS = maxwordcount maxwordcount-dynamic tail

GENERATED-OBJECTS = htab_bucket_count.o htab_hash_function.o htab_init.o htab_for_each.o htab_lookup_add.o htab_clear.o htab_free.o maxwordcount.o io.o

.PHONY: all clean check check-types

all: maxwordcount maxwordcount-dynamic tail

export LD_LIBRARY_PATH="."

# CFLAGS += -fsanitize=address

maxwordcount: libhtab.a maxwordcount.o io.o
	$(CC) $(CFLAGS) maxwordcount.o io.o -o $@ -static -L. -lhtab

maxwordcount-dynamic: libhtab.so maxwordcount.o io.o
	$(CC) $(CFLAGS) maxwordcount.o io.o -o $@ ./libhtab.so

tail: tail.o
	$(CC) $(CFLAGS) $^ -o $@

libhtab.a: $(GENERATED-OBJECTS)
	ar rcs $@ $^

libhtab.so: $(GENERATED-OBJECTS)
	$(CC) $(CFLAGS) -shared -fPIC $^ -o $@

htab_bucket_count.o: htab_bucket_count.c
	$(CC) $(CFLAGS) -c $^ -o $@

htab_clear.o: htab_clear.c
	$(CC) $(CFLAGS) -c $^ -o $@

htab_erase.o: htab_erase.c
	$(CC) $(CFLAGS) -c $^ -o $@

htab_find.o: htab_find.c
	$(CC) $(CFLAGS) -c $^ -o $@

htab_for_each.o: htab_for_each.c
	$(CC) $(CFLAGS) -c $^ -o $@

htab_free.o: htab_free.c
	$(CC) $(CFLAGS) -c $^ -o $@

htab_hash_function.o: htab_hash_function.c
	$(CC) $(CFLAGS) -c $^ -o $@

htab_init.o: htab_init.c
	$(CC) $(CFLAGS) -c $^ -o $@

htab_lookup_add.o: htab_lookup_add.c
	$(CC) $(CFLAGS) -c $^ -o $@

htab_size.o: htab_size.c
	$(CC) $(CFLAGS) -c $^ -o $@

tail.o: tail.c
	$(CC) $(CFLAGS) -c $^ -o $@

maxwordcount.o: maxwordcount.c
	$(CC) $(CFLAGS) -c $^ -o $@

io.o: io.c
	$(CC) $(CFLAGS) -c $^ -o $@

clean:
	rm -rf *.o *.so *.a $(PROGS)

check-types:
	file maxwordcount && file maxwordcount-dynamic