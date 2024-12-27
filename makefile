# Main makefile
CC := gcc
SRCDIR := src
BUILDDIR := build
TARGET := convert

SOURCES := $(shell find $(SRCDIR) -type f -name *.c)
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.c=.o))

CFLAGS := -std=c99 -Wall -Wextra -Wpedantic -Werror -Wshadow -Wstrict-overflow -fstack-protector -O2
LIBS := -lm -lpthread
INC := -I include

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $^ -o $(TARGET) $(INC) $(CFLAGS) $(LIBS)

$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	mkdir -p $(BUILDDIR) || true
	$(CC) -c -o $@ $< $(INC) $(CFLAGS)

.PHONY: clean
clean:
	-@rm -rf $(BUILDDIR) $(TARGET)

