#ifndef S21_CAT_H
#define S21_CAT_H

#define _POSIX_C_SOURCE 200809L
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct arguments {
  int b, n, s, E, T, v;
  int number_files;
} arguments;

arguments argument_parser(int argc, char* argv[], int* flag_error);
void scanline(const char* imput_file_name, arguments* arg, int* tmp_str_len,
              int* full_str_len);
void outline(char* line, int lenght, const arguments* arg);
char v_converses(char ch);
#endif  // S21_CAT_H