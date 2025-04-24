gcc -O2 -o maxwordcount htab_bucket_count.c htab_hash_function.c htab_init.c htab_for_each.c htab_lookup_add.c htab_clear.c htab_free.c maxwordcount.c io.c

tail: tail.o
	$(CC) $^ -o $@


CC = gcc
CFLAGS = -O2 -Wall
LDFLAGS = 

LD_LIBRARY_PATH="."

-fPIC
-shared

CFLAGS += -fsanitize=address
LDFLAGS += -fsanitize=address

all:

# Pˇr´ıklad: Program s knihovnou libtest.a
# gcc -o program -static m1.c m2.c -L. -ltest
maxwordcount: libhtab.a
	$(CC) -o $@

# Pˇr´ıklad: Program s knihovnou libtest.so
# gcc -o program m1.c m2.c -L. -ltest
maxwordcount-dynamic:

libhtab.a: htab_bucket_count.o htab_hash_function.o htab_init.o htab_for_each.o htab_lookup_add.o htab_clear.o htab_free.o maxwordcount.o io.o

libhtab.so:

# all, phony

clean:
  rm -rf *.o *.so *.a maxwordcount maxwordcount-dynamic tail

htab_bucket_count.o: htab_bucket_count.c
	$(CC) -c $^ -o $@

htab_clear.o: htab_clear.c
	$(CC) -c $^ -o $@

htab_erase.o: htab_erase.c
	$(CC) -c $^ -o $@

htab_find.o: htab_find.c
	$(CC) -c $^ -o $@

htab_for_each.o: htab_for_each.c
	$(CC) -c $^ -o $@

htab_free.o: htab_free.c
	$(CC) -c $^ -o $@

htab_hash_function.o: htab_hash_function.c
	$(CC) -c $^ -o $@

htab_init.o: htab_init.c
	$(CC) -c $^ -o $@

htab_lookup_add.o: htab_lookup_add.c
	$(CC) -c $^ -o $@

htab_size.o: htab_size.c
	$(CC) -c $^ -o $@

tail.o: tail.c
	$(CC) -c $^ -o $@

io.o: io.c
	$(CC) -c $^ -o $@