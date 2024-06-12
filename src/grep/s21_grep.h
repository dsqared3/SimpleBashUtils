#ifndef S21_GREP_H
#define S21_GREP_H

#define _POSIX_C_SOURCE 200809L

#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct arguments {
  int e, i, u, v, c, l, n, h, s, f, o;
  char pattern[4096];
  int len_pattenr;

} arguments;

arguments argument_parser(int argc, char *argv[]);
void outline(char const *line, int lenght);
void process_file(arguments arg, char const *path, regex_t *regex);
void output(arguments arg, int argc, char **argv);
void pattern_add(arguments *arg, char const *pattern);
void add_reg_from_file(arguments *arg, char const *path);
void print_o(regex_t *regex, char *line, arguments arg, int line_count_in_file,
             char const *path);

#endif  // S21_GREP_H