CC = gcc
CFLAGS = -Wall -Wextra -g
TARGET = bin/asset_sync

SRC = src/asset_sync.c
OBJ = $(SRC:.c=.o)

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(OBJ)
	@mkdir -p bin
	$(CC) $(CFLAGS) -o $@ $^

src/%.o: src/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

run: $(TARGET)
	./$(TARGET)

clean:
	rm -rf bin src/*.o
