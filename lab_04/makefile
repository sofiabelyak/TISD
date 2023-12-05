CFLAGS := -std=gnu99 -pedantic -Wall -Werror -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion -ggdb
CC := gcc
OBJ_PATH := out/
INC_PATH := inc/
SRC_PATH := src/

app.exe: $(OBJ_PATH)liststack.o $(OBJ_PATH)arrstack.o $(OBJ_PATH)main.o
	$(CC) $(CFLAGS) -o $@ $^ -I $(INC_PATH)

$(OBJ_PATH)arrstack.o: $(SRC_PATH)arrstack.c
	mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) -o $@ -c $< -I $(INC_PATH)

$(OBJ_PATH)liststack.o: $(SRC_PATH)liststack.c
	mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) -o $@ -c $< -I $(INC_PATH)

$(OBJ_PATH)main.o: $(SRC_PATH)main.c
	mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) -o $@ -c $< -I $(INC_PATH)


clean:
	rm $(OBJ_PATH)*.o *.exe