# Define C compiler & flags
CC = gcc
CFLAGS = -Wall -g

# Define sets of source files and object files for dict2
# Define sets of source files and object files for dict3
# Define the executable name(s)

SRC_DICT2 = main_stage2.c cafe.c array_implementation.c
SRC_DICT3 = main_stage3.c cafe.c bit_operations.c radix_tree_implementation.c

EXE_DICT2 = dict2
EXE_DICT3 = dict3

OBJ_DICT2 = $(SRC_DICT2:.c=.o)
OBJ_DICT3 = $(SRC_DICT3:.c=.o)

all: $(EXE_DICT2) $(EXE_DICT3)

$(EXE_DICT2): $(OBJ_DICT2)
	$(CC) $(CFLAGS) -o $(EXE_DICT2) $(OBJ_DICT2)

$(EXE_DICT3): $(OBJ_DICT3)
	$(CC) $(CFLAGS) -o $(EXE_DICT3) $(OBJ_DICT3)

clean:
	rm -f $(OBJ_DICT2) $(EXE_DICT2) $(OBJ_DICT3) $(EXE_DICT3)
