# FLAGS=-std=c99 -x objective-c -O0 -w
CC=gcc
FLAGS=-std=c99 -g
# BINS=test libutils.so runtime_test
BINS=libutils.o libutils.a test libutils.so runtime_test

all: $(BINS)

libutils.o: ./src/*
	$(CC) $(FLAGS) -c $^

libutils.a: ./*.o
	ar rcs $@ $^

libutils.so: ./*.o
	$(CC) $(FLAGS) -fPIC -shared -o $@ $^

test: test.c libutils.a
	$(CC) $(FLAGS) -o test test.c -L. -lutils

runtime_test: test.c
	$(CC) $(FLAGS) -o $@ $^ -L. -lutils

clean:
	rm -f $(BINS)
	rm -f ./*.o
	rm -f ./src/*.gch
	rm -rf *.dSYM
