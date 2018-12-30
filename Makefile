CC = g++
OUT_FILE_NAME = libhash-table.a

CFLAGS= -fPIC -g -Wall -c -fpermissive -O3 -Wno-pointer-to-int-cast

INC = -I./inc

OBJ_DIR=./build/obj

OUT_DIR=./build/lib

# Enumerating of every *.c as *.o and using that as dependency
$(OUT_FILE_NAME): $(patsubst %.c,$(OBJ_DIR)/%.o,$(wildcard *.c))
	ar -r -o $(OUT_DIR)/$@ $^

#Compiling every *.c to *.o
$(OBJ_DIR)/%.o: %.c dirmake
	$(CC) -c $(INC) $(CFLAGS) -o $@  $<
	
dirmake:
	@mkdir -p $(OUT_DIR)
	@mkdir -p $(OBJ_DIR)
	
clean:
	rm -fr $(OBJ_DIR)
	rm -f 	Makefile.bak

rebuild: clean build


