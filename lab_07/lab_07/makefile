# Компилятор
CC := gcc

# Названия папок
INC_DIR := ./inc
SRC_DIR := ./src
OUT_DIR := ./out

OBJS := $(OUT_DIR)/tree.o $(OUT_DIR)/efficiency.o $(OUT_DIR)/balance_tree.o $(OUT_DIR)/efficiency.o $(OUT_DIR)/hash_table.o 

HEADERS := $(INC_DIR)/tree.h $(INC_DIR)/efficiency.h $(INC_DIR)/balance_tree.h $(INC_DIR)/hash_table.h

CFLAGS := -I$(INC_DIR) -Wall -Wpedantic

debug : CFLAGS += -g3
debug : app.exe

release : app.exe

app.exe : $(OBJS) $(OUT_DIR)/main.o
	$(CC) $^ -o $@ -lm

$(OUT_DIR)/%.o : $(SRC_DIR)/%.c $(HEADERS)
	mkdir -p $(OUT_DIR)
	$(CC) -o ./$@ $(CFLAGS) -c $<

.PHONY : clean debug release
clean :
	rm -f -r $(OUT_DIR)
	rm -f ./*.exe ./*tmp*
