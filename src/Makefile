CMAKE_ROOT := .
SRC_DIR := src
TESTS_DIR := tests
BUILD_DIR := build

SRC := $(shell find $(SRC_DIR) $(TESTS_DIR) -name "*.c")
HEADERS := $(shell find $(SRC_DIR) $(TESTS_DIR) -name "*.h")
TESTS_EXEC := $(BUILD_DIR)/tests/calc_rpn/tests_calc_rpn

COVERAGE_REPORT := $(BUILD_DIR)/coverage.info
COVERAGE_REPORT_DIR := $(BUILD_DIR)/coverage

.PHONY: lint fmt build test tests echo clean install uninstall coverage_report gcov_report

all: install

lint:
	@clang-format --style=Google --Werror --dry-run $(SRC) $(HEADERS) && echo "Everything fine"
	@cppcheck $(SRC) $(HEADERS)

fmt:
	@clang-format --style=Google --Werror -i $(SRC) $(HEADERS) && echo "Formatted"

build: build_dir
	cmake -S $(CMAKE_ROOT) -B $(BUILD_DIR) -DCMAKE_BUILD_TYPE=${DCMAKE_BUILD_TYPE}
	cd $(BUILD_DIR) && cmake --build .

install: DCMAKE_BUILD_TYPE := Release
install: build
	cd $(BUILD_DIR) && cmake --install .

uninstall:
	rm -f imgui.ini
	rm -f smart_calc.app

test: tests
tests: DCMAKE_BUILD_TYPE := Debug
tests: build
	make -C $(BUILD_DIR) test

valgrind_tests: tests
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose $(TESTS_EXEC)

coverage_report: tests
	lcov --capture --directory $(BUILD_DIR)/src/ --output-file=$(COVERAGE_REPORT)

gcov_report: coverage_report
	genhtml $(COVERAGE_REPORT) --output-directory $(COVERAGE_REPORT_DIR)
	open $(COVERAGE_REPORT_DIR)/index.html

echo:
	@echo CK_FORK=$(CK_FORK)

clean: uninstall
	rm -rf $(BUILD_DIR)/*

build_dir:
	mkdir -p $(BUILD_DIR)
