SRC_DIR := src
BUILD_DIR := ../build

SRC := $(shell find $(SRC_DIR) -name "*.c")
HEADERS := $(shell find $(SRC_DIR) -name "*.h")
TESTS_EXEC := $(BUILD_DIR)/tests/calc_tests_exec

build: $(TESTS_EXEC)

lint:
	@clang-format --style=Google --Werror --dry-run $(SRC) $(HEADERS) && echo "Everything fine"
	@cppcheck $(SRC) $(HEADERS)

fmt:
	@clang-format --style=Google --Werror -i $(SRC) $(HEADERS) && echo "Formatted"

$(TESTS_EXEC):
	cmake -S $(SRC_DIR) -B $(BUILD_DIR)
	cd $(BUILD_DIR) && cmake --build .

tests: test

test: $(TESTS_EXEC)
	@$^

valgrind_tests: $(TESTS_EXEC)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose $^

echo:
	@echo TESTS_EXEC=$(TESTS_EXEC)

clean:
	rm -rf $(BUILD_DIR)
