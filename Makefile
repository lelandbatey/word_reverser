ODIR=bin
IDIR=include
SRCDIR=src
# The "-I{something}" tells the compiler to include those directories when
# searching for system headers specified in source code via system header
# notation (e.g. "include <stdio.h>")
CFLAGS=-g -O2 -Wall -Wextra -I$(SRCDIR) -I$(IDIR) $(OPTFLAGS)
LIBS=-ldl $(OPTLIBS)
PREFIX?=/usr/local

UNAME := $(shell uname)

ifneq (,$(findstring CYGWIN, $(UNAME)))
	# GCC on Cygwin compiles everything as position independant, and emits
	# warning if compiled with -fPIC
	STATIC_FLAGS=
else
	STATIC_FLAGS=-fPIC
endif

SOURCES=$(wildcard $(SRCDIR)/**/*.c $(SRCDIR)/*.c)
OBJECTS=$(patsubst $(SRCDIR)/%.c,$(ODIR)/%.o,$(SOURCES))

TEST_SRC=$(wildcard tests/*_tests.c)
TESTS=$(patsubst %.c,%,$(TEST_SRC))

TEST_OBJS=$(patsubst tests/%_tests.c,$(ODIR)/%.o,$(TEST_SRC))

LIBTARGET=build/libwordreverse.a
TARGET=build/wordreverse
SO_TARGET=$(patsubst %.a,%.so,$(LIBTARGET))

# The Target Build
all: build $(TARGET) $(LIBTARGET) $(SO_TARGET)

print-%: ; @echo $* is $($*)

dev: CFLAGS=-g -Wall -I$(SRCDIR) -I$(IDIR) -DDEBUG_FLAG -Wextra $(OPTFLAGS)
dev: all

$(ODIR)/%.o: $(SRCDIR)/%.c
	# Building objects
	$(CC) $(CFLAGS) -c $(STATIC_FLAGS) $< -o $@

$(TARGET): $(OBJECTS)
	# Building target
	$(CC) $(CFLAGS) -o $(TARGET) $^


$(LIBTARGET): CFLAGS += $(STATIC_FLAGS)
$(LIBTARGET): build $(OBJECTS)
	# Building LIBTARGET
	ar rcs $@ $(OBJECTS)
	ranlib $@

$(SO_TARGET): $(LIBTARGET) $(OBJECTS)
	# SO_TARGET
	$(CC) -shared -o $@ $(OBJECTS)

# Makes the build and bin directories if they don't exist.
build:
	@mkdir -p build
	@mkdir -p bin

# The Unit Tests
.PHONY: tests

tests/%_tests: $(LIBTARGET)
	$(CC) $(CFLAGS) -o $@ $(TEST_OBJS) $@.c

# tests: OBJECTS := $(filter-out $(wildcard *main*),$(OBJECTS))
tests: build $(TEST_OBJS) $(LIBTARGET) $(TESTS)
	# tests
	sh ./tests/runtests.sh

# testprep: CFLAGS += $(LIBTARGET)
	# testprep
testprep: 
testprep: $(TESTS)

# The Cleaner
clean:
		rm -rf build $(OBJECTS) $(TESTS)
		rm -rf bin/*
		rm -f tests/tests.log
		find . -name "*.gc*" -exec rm {} \;
		rm -rf `find . -name "*.dSYM" -print`

# The Install
install: all
		install -d $(DESTDIR)/$(PREFIX)/lib/
		install $(TARGET) $(DESTDIR)/$(PREFIX)/lib/

# The Checker
BADFUNCS='[^_.>a-zA-Z0-9](str(n?cpy|n?cat|xfrm|n?dup|str|pbrk|tok|_)|stpn?cpy|a?sn?printf|byte_)'
check:
		@echo Files with potentially dangerous functions.
		@egrep $(BADFUNCS) $(SOURCES) || true
