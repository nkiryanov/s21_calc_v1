CC :=                   gcc
CFLAGS +=               -Wall -Werror -Wextra
LDFLAGS +=              -Wall -Werror -Wextra

SRC_DIR := ./lib/
OBJ_DIR := ./objects/
TEST_OBJ_DIR := ./objects/tests/

SRC :=                  $(wildcard $(SRC_DIR)*.c)
OBJ :=                  $(SRC:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)
OBJ_PROFILED :=         $(OBJ:.o=_profiled.o)

TEST_DIR :=             ./tests/
TEST_SRC :=             $(wildcard $(TEST_DIR)*.c)
TEST_OBJ :=             $(TEST_SRC:$(TEST_DIR)%.c=$(TEST_OBJ_DIR)%.o)
TEST_EXEC :=            $(TEST_DIR)tests_s21_calc.out

TEST_PROFILE_DATA =     $(wildcard $(OBJ_DIR)*.gcda $(OBJ_DIR)*.gcno)

COVERAGE_REPORT_DIR :=  ./coverage/
COVERAGE_FILE :=        coverage.info

LIB :=                  s21_calc.a

.PHONY: all test tests echo clean lint coverage_report gcov_report

all: $(LIB)

echo:
	@echo LIB=$(LIB)
	@echo CFLAGS=$(CFLAGS)
	@echo CC=$(CC)
	@echo SRC_DIR=$(SRC_DIR)
	@echo SRC=$(SRC)
	@echo OBJ=$(OBJ)
	@echo LDLIBS=$(LDLIBS)
	@echo OBJ_PROFILED=$(OBJ_PROFILED)
	@echo TEST_PROFILE_DATA=$(TEST_PROFILE_DATA)

lint:
	@clang-format --style=Google --Werror --dry-run $(SRC_DIR)* $(TEST_DIR)* && echo "Everything fine"
	@cppcheck $(SRC)

fmt:
	@clang-format --style=Google --Werror -i $(SRC_DIR)* $(TEST_DIR)* && echo "Formatted"

test: tests

tests: CFLAGS += -fsanitize=address
tests: LDFLAGS += -fsanitize=address
tests: $(TEST_EXEC)
	@$^

coverage_report: tests
	lcov --capture --directory $(OBJ_DIR) --output-file $(COVERAGE_FILE)

gcov_report: coverage_report
	genhtml $(COVERAGE_FILE) --output-directory $(COVERAGE_REPORT_DIR)

valgrind_tests: $(TEST_EXEC)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose $^

$(LIB): $(OBJ)
	$(AR) -rcs $@ $^

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	$(CC) -c $(CFLAGS) $< -o $@

$(OBJ_DIR)%_profiled.o: CFLAGS += --coverage -g
$(OBJ_DIR)%_profiled.o: $(SRC_DIR)%.c
	$(CC) -c $(CFLAGS) $< -o $@

$(TEST_OBJ_DIR)%.o: $(TEST_DIR)%.c
	$(CC) -c $(CFLAGS) $^ -o $@

$(TEST_EXEC): CFLAGS += $(shell pkg-config --cflags-only-I check) -g
$(TEST_EXEC): LDLIBS += $(shell pkg-config --libs check) --coverage
$(TEST_EXEC): $(TEST_OBJ) $(OBJ_PROFILED)
	$(CC) $(LDFLAGS) $^ -o $@ $(LDLIBS)

clean:
	rm -rf $(LIB) $(OBJ) $(OBJ_PROFILED)
	rm -rf $(TEST_EXEC) $(TEST_OBJ) $(TEST_PROFILE_DATA)
	rm -rf $(COVERAGE_FILE) $(COVERAGE_REPORT_DIR)
