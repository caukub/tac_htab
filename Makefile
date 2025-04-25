CC = gcc
CFLAGS = -O2 -Wall -std=c11
# LDFLAGS = 
PROGS = maxwordcount maxwordcount-dynamic tail

LD_LIBRARY_PATH="."

# -fPIC
# -shared

# -static

# CFLAGS += -fsanitize=address
# LDFLAGS += -fsanitize=address

# all:

# .PHONY:

# 1) pˇreklad modul ˚u: cc -c moduly.c
# 2) vytvoření knihovny ar parametry knihovna.a moduly.o
# 3) gcc -o program -static m1.c m2.c -L. -ltest
maxwordcount: libhtab.a
	$(CC) $(CFLAGS) maxwordcount.o io.o -o $@ -static -L. -lhtab

tail: tail.o
	$(CC) $^ -o $@

libhtab.a: htab_bucket_count.o htab_hash_function.o htab_init.o htab_for_each.o htab_lookup_add.o htab_clear.o htab_free.o maxwordcount.o io.o
	ar rcs $@ $^

libhtab.so:

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