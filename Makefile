FLAGS = -std=c99
LIBS = -L. -lutils

# List of all .c files in the src directory
SRCS := $(wildcard ./src/*.c)

# Create a list of object files from the source files
OBJS := $(SRCS:.c=.o)

BINS = test runtime_test test_dbg runtime_test_dbg

all: clean $(BINS)

# Platform-specific rules
# TODO: Linux/WIN
ifeq ($(OS),Windows_NT) # Windows

libutils.a: $(OBJS_WIN)
	ar rcs $@ $^

libutils.so: $(OBJS_WIN)
	$(CC) $(FLAGS) -fPIC -shared -o $@ $^

test: test.c libutils.a
	$(CC) $(FLAGS) $(LIBS) -o $@ $^

test_dbg: test.c libutils.a
	$(CC) $(FLAGS) $(LIBS) -o $@ $^ -g

runtime_test: test.c libutils.so
	$(CC) $(FLAGS) -o $@ $?

runtime_test_dbg: test.c libutils.so
	$(CC) $(FLAGS) -o $@ $? -g

clean:
	rm -f $(BINS) $(OBJS_WIN) *.o libutils.a libutils.so
	rm -rf *.dSYM

else ifeq ($(shell uname),Darwin) # macOS

SRCS_OBJC += $(wildcard ./src/*.m)
SRCS += $(SRCS_OBJC)
OBJS += $(patsubst %.m, %.m.o, $(SRCS_OBJC))
FLAGS += -framework Cocoa

# objective c
%.m.o: %.m
	$(CC) -x objective-c -c $< -o $@

libutils.a: $(OBJS)
	ar rcs $@ $^

libutils.dylib: $(SRCS)
	$(CC) $(FLAGS) -dynamiclib -o $@ $^

test: test.c libutils.a
	$(CC) $(FLAGS) $(LIBS) -o $@ $<

test_dbg: test.c libutils.a
	$(CC) $(FLAGS) $(LIBS) -o $@ $< -g

runtime_test: test.c libutils.dylib
	$(CC) $(FLAGS) -o $@ $?

runtime_test_dbg: test.c libutils.dylib
	$(CC) $(FLAGS) -o $@ $? -g

clean:
	rm -f $(BINS) $(OBJS) *.o libutils.a libutils.dylib
	rm -rf *.dSYM

else # Linux (assumed)

libutils.a: $(OBJS_LINUX)
	ar rcs $@ $^

libutils.so: $(OBJS_LINUX)
	$(CC) $(FLAGS) -fPIC -shared -o $@ $^

test: test.c libutils.a
	$(CC) $(FLAGS) $(LIBS) -o $@ $<

test_dbg: test.c libutils.a
	$(CC) $(FLAGS) $(LIBS) -o $@ $< -g

runtime_test: test.c libutils.so
	$(CC) $(FLAGS) -o $@ $^

runtime_test_dbg: test.c libutils.so
	$(CC) $(FLAGS) -o $@ $^ -g

clean:
	rm -f $(BINS) $(OBJS_LINUX) *.o libutils.a
	rm -rf *.dSYM
endif

# Rules to build object files from C source files
%.o: %.c
	$(CC) -std=c99 -c $< -o $@
