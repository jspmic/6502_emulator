CC=gcc
CFLAGS=-Wall

SRC_DIR=src
BUILD_DIR=build
BIN=main

SRC=$(shell ls $(SRC_DIR)/*.c)

.PHONY: build make-build clean view

build: make-build
	$(CC) $(CFLAGS) $(SRC) -o $(BUILD_DIR)/$(BIN)

view:
	./$(BUILD_DIR)/$(BIN)

make-build:
	@if [ -d "$(BUILD_DIR)" ]; then \
		echo "$(BUILD_DIR) exists..."; \
	else \
		@mkdir $(BUILD_DIR); \
	fi

clean:
	@rm $(BUILD_DIR)/*
