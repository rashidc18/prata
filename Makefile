INCLUDE_DIR = include
SRC_DIR = src

CC = clang  # switch to GCC when compiling for distribution
CFLAGS = -I$(INCLUDE_DIR) -ansi -Wall -Wextra -Wpedantic -Werror -O3

TARGET = prata
SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(SRC:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $@ 

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run

