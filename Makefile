CC = gcc
CFLAGS = -Wall -Isrc -Isrc/assert -Isrc/parser -Isrc/reader -Isrc/strings

SRC = src/main.c \
      src/assert/assert.c \
      src/parser/parser.c \
      src/reader/reader.c \
      src/strings/strings.c

OBJ = $(SRC:.c=.o)

all: main

main: $(OBJ)
	$(CC) $(OBJ) -o main

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

run: main
	./main

clean:
	rm -f $(OBJ) main

