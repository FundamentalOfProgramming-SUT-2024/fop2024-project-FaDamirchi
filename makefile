# Compiler
CC = gcc
CFLAGS = -Wall -Wextra -Iinclude -no-pie -g
LDFLAGS = -lncurses -lm
SRC_DIR = src
BIN_DIR = bin
INCLUDE_DIR = include
DATA_DIR = data

# Source
SRCS = $(SRC_DIR)/main.c $(SRC_DIR)/main_menu.c $(SRC_DIR)/ui_utils.c $(SRC_DIR)/signup.c $(SRC_DIR)/login.c $(SRC_DIR)/manage_users.c $(SRC_DIR)/pregame_menu.c $(SRC_DIR)/settings.c $(SRC_DIR)/map.c $(SRC_DIR)/new_game.c $(SRC_DIR)/player.c $(SRC_DIR)/monsters.c

# Objects
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(BIN_DIR)/%.o)

# Program
TARGET = $(BIN_DIR)/rouge

# Target
all: $(TARGET)

# Program making
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LDFLAGS)

# Objects making
$(BIN_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Copy data to bin
copy_data:
	cp -r $(DATA_DIR)/* $(BIN_DIR)/

# Clear Compiled files
clean:
	rm -f $(OBJS) $(TARGET)
	rm -rf $(BIN_DIR)/*

# Create essentials
install:
	mkdir -p $(BIN_DIR) $(DATA_DIR)

# Run the program
run: $(TARGET) copy_data
	./$(TARGET)