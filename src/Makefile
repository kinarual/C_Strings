CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11
LIBS = -lcheck
OS = $(shell uname)
GCOV=-coverage

ifeq ($(OS), Darwin)
	LIBS=-lcheck
else
	LIBS=-lcheck -lsubunit -pthread -lrt -lm
endif

all: clean s21_string.a test

s21_string.a:
	$(CC) -c s21_string.c s21_sprintf.c s21_sscanf.c 
	ar rcs s21_string.a s21_string.o s21_sprintf.o s21_sscanf.o 

test:	check.c s21_string.a
	$(CC) $(CFLAGS) -c check.c -o check.o
	$(CC) check.o s21_string.a $(LIBS) -o test
	./test
style:
	clang-format -i -style=Google *.c *.h

gcov_report: s21_string.a
	$(CC) $(GCOV) -c s21_string.c s21_sprintf.c s21_sscanf.c 
	$(CC) -c check.c $(LIBS)
	$(CC) $(GCOV) -o string_test check.o s21_string.o s21_sprintf.o s21_sscanf.o  $(LIBS)
	./string_test

	lcov -t "string_tests" -o string_test.info -c -d .
	genhtml -o report/ string_test.info
	open ./report/index.html

clean:
	rm -rf ./*.o ./*.a test ./report ./*.gcno ./*.gcda ./*.info string_test
