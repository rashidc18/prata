INCLUDE_DIR = include

# PRATAC - COMPILER
COMPILER_DIR = compiler
COMPILER_INCLUDE_DIR = $(COMPILER_DIR)/$(INCLUDE_DIR)
COMPILER_TARGET = pratac
COMPILER_SRC = $(wildcard $(COMPILER_DIR)/*.c $(COMPILER_DIR)/*/*.c)
COMPILER_OBJ = $(COMPILER_SRC:.c=.o)

# PRATAVM - VIRTUAL MACHINE
VM_DIR = vm
VM_INCLUDE_DIR = $(VM_DIR)/$(INCLUDE_DIR)
VM_TARGET = pratavm
VM_SRC = $(wildcard $(VM_DIR)/*.c $(VM_DIR)/*/*.c)
VM_OBJ = $(VM_SRC:.c=.o)

# COMMON
COMMON_DIR = common
COMMON_INCLUDE_DIR = $(COMMON_DIR)/$(INCLUDE_DIR)
COMMON_SRC = $(wildcard $(COMMON_DIR)/*.c $(COMMON_DIR)/*/*.c)
COMMON_OBJ = $(COMMON_SRC:.c=.o)

# CC
CC = clang
CFLAGS = -ansi -Wall -Wextra -Wpedantic -Werror -O3 \
	-I$(COMPILER_INCLUDE_DIR) \
	-I$(VM_INCLUDE_DIR) \
	-I$(COMMON_INCLUDE_DIR)

# ALL
all: $(COMPILER_TARGET) $(VM_TARGET)

# LINK
$(COMPILER_TARGET): $(COMPILER_OBJ) $(COMMON_OBJ)
	$(CC) $^ -o $@

$(VM_TARGET): $(VM_OBJ) $(COMMON_OBJ)
	$(CC) $^ -o $@

# COMPILE
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# CLEAN
clean:
	rm -f $(COMPILER_OBJ) $(VM_OBJ) $(COMMON_OBJ)
	rm -f $(COMPILER_TARGET) $(VM_TARGET)

# RUN
run-compiler: $(COMPILER_TARGET)
	./$(COMPILER_TARGET)

run-vm: $(VM_TARGET)
	./$(VM_TARGET)

.PHONY: all clean run-compiler run-vm
