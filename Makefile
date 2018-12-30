CC = gcc
OUT_FILE_NAME = libhash-table.a

CFLAGS= -fPIC -g -Wall -c -O3 -Wno-pointer-to-int-cast

INC = -I./inc

OBJ_DIR=./build/obj
SRC_DIR=./src
OUT_DIR=./build/lib

# Enumerating of every *.c as *.o and using that as dependency
$(OUT_FILE_NAME): $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(wildcard $(SRC_DIR)/*.c))
	ar -r -o $(OUT_DIR)/$@ $^

#Compiling every *.c to *.o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c dirmake
	@$(CC) -c $(INC) $(CFLAGS) -o $@  $< 
	
dirmake:
	@mkdir -p $(OUT_DIR) > /dev/null
	@mkdir -p $(OBJ_DIR) > /dev/null
	
clean:
	@rm -fr build > /dev/null
	@rm -f Makefile.bak > /dev/null
	@rm -fr CMakeFiles > /dev/null
	@rm -fr tests/CMakeFiles > /dev/null

rebuild: clean build


