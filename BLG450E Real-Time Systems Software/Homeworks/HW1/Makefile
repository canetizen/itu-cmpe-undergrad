# Author: Mustafa Can Caliskan, 150200097

CC = gcc
CFLAGS = -Iinclude/ -Wall -Werror
SRC = src/main.c src/rm.c src/dm.c src/llf.c src/edf.c src/utils.c
OBJ = $(SRC:src/%.c=object/%.o)
TARGET = build/scheduler

all: build run

build: build_dir object_dir $(TARGET)

build_dir:
	@mkdir -p build

object_dir:
	@mkdir -p object

$(TARGET): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

object/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

run:
	@./$(TARGET)

clean:
	rm -f $(OBJ) $(TARGET)
	@rmdir build object 2>/dev/null || true
