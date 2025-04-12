CC=gcc
CFLAGS=-Wall -g
CFLAGS_TEST=-Wall -g -lm -I
SRC_TEST=../src
END_FLAG=-lcheck

SRC_DIR=src
TEST_DIR=tests
BUILD_DIR=build
BIN=main
BIN_TEST=test

TEST_SRC=$(shell ls $(SRC_DIR)/*.c | grep -v main) $(shell ls $(TEST_DIR)/*.c)
SRC=$(shell ls $(SRC_DIR)/*.c)

.PHONY: build make-build clean view vreset

build: make-build
	$(CC) $(CFLAGS) $(SRC) -o $(BUILD_DIR)/$(BIN)

view:
	./$(BUILD_DIR)/$(BIN)

vtest: test
	./$(BUILD_DIR)/$(BIN_TEST)

make-build:
	@if [ -d "$(BUILD_DIR)" ]; then \
		echo "$(BUILD_DIR) exists..."; \
	else \
		@mkdir $(BUILD_DIR); \
	fi

test:
	$(CC) $(CFLAGS_TEST) $(SRC_TEST) $(TEST_SRC) -o $(BUILD_DIR)/$(BIN_TEST) $(END_FLAG)

clean:
	@rm $(BUILD_DIR)/*
