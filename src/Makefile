CMAKE_ROOT := .
SRC_DIR := src
TESTS_DIR := tests
BUILD_DIR := build

SRC := $(shell find $(SRC_DIR) $(TESTS_DIR) -name "*.c")
HEADERS := $(shell find $(SRC_DIR) $(TESTS_DIR) -name "*.h")
TESTS_EXEC := $(BUILD_DIR)/tests/calc_rpn/tests_calc_rpn

.PHONY: lint fmt build test tests echo clean

all: build

lint:
	@clang-format --style=Google --Werror --dry-run $(SRC) $(HEADERS) && echo "Everything fine"
	@cppcheck $(SRC) $(HEADERS)

fmt:
	@clang-format --style=Google --Werror -i $(SRC) $(HEADERS) && echo "Formatted"

build:
	cmake -S $(CMAKE_ROOT) -B $(BUILD_DIR) -DCMAKE_BUILD_TYPE=Debug
	cd $(BUILD_DIR) && cmake --build .

app: build
	$(BUILD_DIR)/apps/smart_calc_app

tests: test
test: build
	make -C ${BUILD_DIR} test

valgrind_tests: export CK_FORK = no
valgrind_tests: build
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose $(TESTS_EXEC)

echo:
	@echo CK_FORK=$(CK_FORK)

clean:
	rm -rf $(BUILD_DIR)/*
