CC = gcc
CFLAGS = -Wall -Wextra -I$(INC_DIR)

BUILD_DIR = ./build
OUT_DIR = ./app
SRC_DIR = ./src
INC_DIR = ./headers

MAIN_FILE   := main.c
SRC_C_FILES := $(MAIN_FILE) $(wildcard $(SRC_DIR)/*.c)

O_FILES := $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRC_C_FILES))
H_FILES := $(wildcard $(INC_DIR)/*.h)

BIN_FILE := $(OUT_DIR)/exe

$(BIN_FILE): $(O_FILES)
	@mkdir -p $(OUT_DIR)
	$(CC) $(O_FILES) -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c $(H_FILES)
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR) $(OUT_DIR)
