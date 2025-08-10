CC = gcc
CFLAGS = -Wall -Wextra -I$(INC_DIR)

BUILD_DIR = ./build
OUT_DIR = ./app
SRC_DIR = ./src
INC_DIR = ./headers
INPUT_FILES_DIR = ./input_files

MAIN_FILE       := main.c
SRC_C_FILES     := $(MAIN_FILE) $(wildcard $(SRC_DIR)/*.c)
INST_GEN_C_FILE := $(INPUT_FILES_DIR)/instance_generator.c

O_FILES         := $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRC_C_FILES))
H_FILES         := $(wildcard $(INC_DIR)/*.h)
INST_GEN_O_FILE := $(BUILD_DIR)/instance_generator.o

BIN_FILE      := $(OUT_DIR)/exe
BIN_INST_FILE := $(INPUT_FILES_DIR)/exe

$(BIN_FILE): $(O_FILES)
	@mkdir -p $(OUT_DIR)
	$(CC) $(O_FILES) -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c $(H_FILES)
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: gen

gen: $(BIN_INST_FILE)

$(BIN_INST_FILE): $(INST_GEN_O_FILE)
	$(CC) $(INST_GEN_O_FILE) -o $@

$(INST_GEN_O_FILE): $(INST_GEN_C_FILE)
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $(INST_GEN_O_FILE)

clean:
	rm -rf $(BUILD_DIR) $(OUT_DIR)