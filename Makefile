FLAGS = -std=c99
FLAGS_OSX = $(FLAGS) -x objective-c -framework Cocoa
FLAGS_WIN = $(FLAGS)
FLAGS_LINUX = $(FLAGS)

# List of all .c files in the src directory
SRCS := $(wildcard ./src/*.c)

# Create a list of object files from the source files
OBJS := $(SRCS:.c=.o)

# List of platform-specific object files
OBJS_OSX := $(OBJS) ./src/clipboard.m.o
OBJS_WIN := $(OBJS)
OBJS_LINUX := $(OBJS)

BINS = test runtime_test test_dbg runtime_test_dbg

all: clean $(BINS)

# Platform-specific rules
ifeq ($(OS),Windows_NT) # Windows

libutils.a: $(OBJS_WIN)
	ar rcs $@ $^

libutils.so: $(OBJS_WIN)
	$(CC) $(FLAGS_WIN) -fPIC -shared -o $@ $^

test: test.c libutils.a
	$(CC) $(FLAGS_WIN) -o $@ $^ -L. -lutils

test_dbg: test.c libutils.a
	$(CC) $(FLAGS_WIN) -o $@ $^ -L. -lutils -g

runtime_test: test.c
	$(CC) $(FLAGS_WIN) -o $@ $^ -L. -lutils

runtime_test_dbg: test.c
	$(CC) $(FLAGS_WIN) -o $@ $^ -L. -lutils -g

clean:
	rm -f $(BINS) $(OBJS_WIN) *.o libutils.a
	rm -rf *.dSYM

else ifeq ($(shell uname),Darwin) # macOS

# objective c
%.m.o: %.m
	$(CC) -c $< -o $@

libutils.a: $(OBJS_OSX)
	ar rcs $@ $^

libutils.so: $(OBJS_OSX)
	$(CC) $(FLAGS_OSX) -fPIC -shared -o $@ $^

test: test.c libutils.a
	$(CC) $(FLAGS_OSX) -o $@ $< -L. -lutils

test_dbg: test.c libutils.a
	$(CC) $(FLAGS_OSX) -o $@ $< -L. -lutils -g

runtime_test: test.c
	$(CC) $(FLAGS_OSX) -o $@ $^ -L. -lutils

runtime_test_dbg: test.c
	$(CC) $(FLAGS_OSX) -o $@ $^ -L. -lutils -g

clean:
	rm -f $(BINS) $(OBJS_OSX) *.o libutils.a
	rm -rf *.dSYM

else # Linux (assumed)

libutils.a: $(OBJS_LINUX)
	ar rcs $@ $^

libutils.so: $(OBJS_LINUX)
	$(CC) $(FLAGS_LINUX) -fPIC -shared -o $@ $^

test: test.c libutils.a
	$(CC) $(FLAGS_LINUX) -o $@ $< -L. -lutils

test_dbg: test.c libutils.a
	$(CC) $(FLAGS_LINUX) -o $@ $< -L. -lutils -g

runtime_test: test.c
	$(CC) $(FLAGS_LINUX) -o $@ $^ -L. -lutils

runtime_test_dbg: test.c
	$(CC) $(FLAGS_LINUX) -o $@ $^ -L. -lutils -g

clean:
	rm -f $(BINS) $(OBJS_LINUX) *.o libutils.a
	rm -rf *.dSYM
endif
#
# Rules to build object files from C source files
%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@
