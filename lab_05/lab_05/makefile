CC = gcc
CFLAGS = -I$(INC_DIR) -std=c99 -Wall -Werror -Wextra -Wpedantic -Wvla -g -fprofile-arcs
LDFLAGS = -fprofile-arcs -lcheck -lsubunit -lpthread -lrt -lm

OUT_DIR = out
SRC_DIR = src
INC_DIR = inc
TEST_DIR = unit_tests

APP_SRC = $(wildcard $(SRC_DIR)/*.c)
APP_OBJ = $(APP_SRC:$(SRC_DIR)/%.c=$(OUT_DIR)/%.o)

UNIT_TEST_SRC = $(wildcard $(TEST_DIR)/check_*.c)
UNIT_TEST_OBJ = $(UNIT_TEST_SRC:$(TEST_DIR)/%.c=$(OUT_DIR)/%.o)

APP_EXEC = app.exe
UNIT_TEST_EXEC = unit_tests.exe

$(APP_EXEC): $(APP_OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

$(OUT_DIR)/%.o: $(SRC_DIR)/%.c | $(OUT_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(UNIT_TEST_EXEC): $(UNIT_TEST_OBJ) $(filter-out $(OUT_DIR)/main.o, $(APP_OBJ))
	$(CC) -o $@ $^ $(LDFLAGS)

$(OUT_DIR)/%.o: $(TEST_DIR)/%.c | $(OUT_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OUT_DIR):
	mkdir -p $(OUT_DIR)

unit: $(UNIT_TEST_EXEC)
	export CK_FORK=no
	valgrind ./unit_tests.exe

func: $(APP_EXEC)
	./func_tests/scripts/func_tests.sh

valgrind : $(APP_EXEC)
	./func_tests/scripts/func_tests.sh -v

gcov : CFLAGS += --coverage
gcov : LDFLAGS += --coverage
gcov : $(APP_EXEC)
	mv $(wildcard ./*.gcno) $(OUT_DIR) 2> /dev/null || true

asan : CC = clang
asan : CFLAGS += -fno-omit-frame-pointer -fsanitize=address
asan : LDFLAGS += -fsanitize=address
asan : $(APP_EXEC)

msan : CC = clang
msan : CFLAGS += -fPIE  -fno-omit-frame-pointer -fsanitize=memory
msan : LDFLAGS += -fsanitize=memory
msan : $(APP_EXEC)

ubsan : CC = clang
ubsan : CFLAGS += -fno-omit-frame-pointer -fsanitize=undefined
ubsan : LDFLAGS += -fsanitize=undefined
ubsan : $(APP_EXEC)

all : $(UNIT_TEST_EXEC)
	./func_tests/scripts/test_all.sh

clean:
	rm -rf $(OUT_DIR) $(APP_EXEC) $(UNIT_TEST_EXEC) output.txt tmp

release: CFLAGS = -I$(INC_DIR) -std=c99 -Wall -Werror -Wextra -Wpedantic -Wfloat-equal -Wfloat-conversion -Wvla
release: LDFLAGS = -lm
release: $(APP_EXEC)

debug: $(APP_EXEC)

.PHONY: all clean unit func release debug
