.PHONY: clean test my_c_matrix.a gcov_report
CC = gcc
# CFLAGS = -Wall -Werror -Wextra -std=c11
GCOVFLAGS = -fprofile-arcs -ftest-coverage
OS = $(shell uname)
ifeq ($(OS),Darwin)
	CHECKFLAGS = -lcheck
else
	CHECKFLAGS = -lcheck -lpthread -lrt -lm -lsubunit
endif

all: clean test

my_c_matrix.a: 
	$(CC) $(CFLAGS) -c my_c_matrix.c -o my_c_matrix.o
	ar rc my_c_matrix.a my_c_matrix.o
	ranlib my_c_matrix.a

test: my_c_matrix.a
	$(CC) $(CFLAGS) test.c my_c_matrix.a $(CHECKFLAGS) -o a.out
	./a.out

gcov_report: my_c_matrix.a
	$(CC) $(CFLAGS) $(GCOVFLAGS) my_c_matrix.c test.c $(CHECKFLAGS) -o gcov_rep.out
	./gcov_rep.out
	lcov -t "gcov_rep" --output-file=coverag.info --capture --directory .
	genhtml -o ./report coverag.info

clean:
	@clear
	rm -f *.o *.a *.gcno *.gcda *.info *.out
	rm -rf ./report
