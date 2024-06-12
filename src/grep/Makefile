SHELL := /bin/bash
CC=gcc
CFLAGS=-Wall -Wextra -Werror
CLANG=clang-format -i
CPP=cppcheck --enable=all --suppress=missingIncludeSystem --checkers-report=SimpleTest.txt
VALG=2>&1 valgrind --tool=memcheck --leak-check=yes --leak-check=full --show-leak-kinds=all
LDFLAGS=
SOURCES=s21_grep.c
EXECUTABLE=s21_grep
FILE=patterns.txt
PATTERN=a

all: s21_grep
	
s21_grep: Makefile s21_grep.h s21_grep.c
	$(CC) $(CFLAGS) $(SOURCES) -o $(EXECUTABLE)

test:
	-diff <(./$(EXECUTABLE) -e $(PATTERN) $(FILE)) <(grep -e $(PATTERN) $(FILE))
	-diff <(./$(EXECUTABLE) -i $(PATTERN) $(FILE)) <(grep -i $(PATTERN) $(FILE))
	-diff <(./$(EXECUTABLE) -v $(PATTERN) $(FILE)) <(grep -v $(PATTERN) $(FILE))
	-diff <(./$(EXECUTABLE) -v patterns.txt $(SOURCES) Makefile) <(grep -v patterns.txt $(SOURCES) Makefile)
	-diff <(./$(EXECUTABLE) -c $(PATTERN) $(FILE)) <(grep -c $(PATTERN) $(FILE))
	-diff <(./$(EXECUTABLE) -l $(PATTERN) $(FILE)) <(grep -l $(PATTERN) $(FILE))
	-diff <(./$(EXECUTABLE) -n $(PATTERN) $(FILE)) <(grep -n $(PATTERN) $(FILE))
	-diff <(./$(EXECUTABLE) -l $(PATTERN) *.txt) <(grep -l $(PATTERN) *.txt)
	-diff <(./$(EXECUTABLE) -h $(PATTERN) *.txt) <(grep -h $(PATTERN) *.txt)
	-diff <(./$(EXECUTABLE) -ci $(PATTERN) *.txt) <(grep -ci $(PATTERN) *.txt)
	-diff <(./$(EXECUTABLE) -e cle -e CLE *.txt) <(grep -e cle -e CLE *.txt)
	-diff <(./$(EXECUTABLE) -f patterns.txt $(SOURCES) Makefile) <(grep -f patterns.txt $(SOURCES) Makefile)
	-diff <(./$(EXECUTABLE) -o for $(SOURCES) Makefile) <(grep -o for $(SOURCES) Makefile)
	-diff <(./$(EXECUTABLE) -iv for $(SOURCES) Makefile) <(grep -iv for $(SOURCES) Makefile)
	-diff <(./$(EXECUTABLE) -in for $(SOURCES) Makefile) <(grep -in for $(SOURCES) Makefile)
	-diff <(./$(EXECUTABLE) -vo patterns.txt $(SOURCES) Makefile) <(grep -vo patterns.txt $(SOURCES) Makefile)

	
check:
	clang-format -style=Google -n *.c

valgrind:
	$(VALG) ./$(EXECUTABLE) -n for $(FILE)

cppcheck: 
	$(CPP) *.c

rebuild:
	make clean
	make all

clean:
	rm -f s21_grep