SHELL := /bin/bash
CC=gcc
CFLAGS=-Wall -Wextra -Werror
CLANG=clang-format -i
CPP=cppcheck --enable=all --suppress=missingIncludeSystem
LDFLAGS=
SOURCES=s21_cat.c
EXECUTABLE=s21_cat
FILE=*.txt
FILE2=all.txt

all: s21_cat
	
s21_cat: Makefile s21_cat.h s21_cat.c
	$(CC) $(CFLAGS) $(SOURCES) -o $(EXECUTABLE)

test:
	-diff <(./$(EXECUTABLE) $(FILE)) <(cat $(FILE))
	-diff <(./$(EXECUTABLE) -b $(FILE)) <(cat -b $(FILE)) 
	-diff <(./$(EXECUTABLE) --number-nonblank $(FILE)) <(cat --number-nonblank $(FILE))
	-diff <(./$(EXECUTABLE) -E $(FILE)) <(cat -E $(FILE))
	-diff <(./$(EXECUTABLE) -v $(FILE)) <(cat -v $(FILE))
	-diff <(./$(EXECUTABLE) -e $(FILE)) <(cat -e $(FILE))
	-diff <(./$(EXECUTABLE) -n $(FILE)) <(cat -n $(FILE))
	-diff <(./$(EXECUTABLE) -s $(FILE)) <(cat -s $(FILE))
	-diff <(./$(EXECUTABLE) --squeeze-blank $(FILE)) <(cat --squeeze-blank $(FILE))
	-diff <(./$(EXECUTABLE) -t $(FILE)) <(cat -t $(FILE))
	-diff <(./$(EXECUTABLE) -T $(FILE)) <(cat -T $(FILE))
	-diff <(./$(EXECUTABLE) -etsnb $(FILE)) <(cat -etsnb $(FILE))
	-diff <(./$(EXECUTABLE) -bevEnstT $(FILE)) <(cat -bevEnstT $(FILE))
	
	
check:
	clang-format -style=Google -n *.c

valgrind:
	valgrind --tool=memcheck --leak-check=yes  ./$(EXECUTABLE) -b $(FILE)

cppcheck: 
	$(CPP)

rebuild:
	make clean
	make all

clean:
	rm -f s21_cat