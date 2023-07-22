FLAGS=-std=c99 -g
# List of all .c files in the src directory
SRCS := $(wildcard ./src/*.c)

# Create a list of object files from the source files
OBJS := $(SRCS:.c=.o)

BINS=libutils.o libutils.a test libutils.so runtime_test

all: $(BINS)

libutils.o: $(OBJS)
	$(CC) -c $^

libutils.a: $(OBJS)
	ar rcs $@ $^

libutils.so: $(OBJS)
	$(CC) $(FLAGS) -fPIC -shared -o $@ $^

test: test.c libutils.a
	$(CC) $(FLAGS) -o $@ $^ -L. -lutils

runtime_test: test.c
	$(CC) $(FLAGS) -o $@ $^ -L. -lutils

clean:
	rm -f $(BINS) $(OBJS)
	rm -rf *.dSYM
