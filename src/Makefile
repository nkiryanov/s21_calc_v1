SRC_DIR := src

SRC := $(shell find $(SRC_DIR) -name "*.c")
TESTS_EXEC := ../build/tests/calc_tests_exec

lint:
	@clang-format --style=Google --Werror --dry-run $(SRC) && echo "Everything fine"
	@cppcheck $(SRC)

fmt:
	@clang-format --style=Google --Werror -i $(SRC) && echo "Formatted"

build: $(TESTS_EXEC)

$(TESTS_EXEC):
	cmake -S src -B ../build
	cd ../build && cmake --build .

tests:
test: $(TESTS_EXEC)
	@$^

valgrind_tests: $(TEST_EXEC)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose $^
