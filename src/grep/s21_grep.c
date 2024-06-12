#include "s21_grep.h"

int main(int argc, char *argv[]) {
  arguments arg = argument_parser(argc, argv);
  output(arg, argc, argv);
  return 0;
}

arguments argument_parser(int argc, char *argv[]) {
  arguments arg = {0};
  int opt;
  while ((opt = getopt(argc, argv, "e:ivclnhsf:o")) != -1) {
    switch (opt) {
      case 'e':
        arg.e = 1;  // поиск шаблона
        pattern_add(&arg, optarg);
        break;
      case 'i':  // регистр АаА
        arg.i = REG_ICASE;
        break;
      case 'v':  // инвертор
        arg.v = 1;
        break;
      case 'c':  // кол. совпадений одним числом
        arg.c = 1;
        break;
      case 'l':  // совпадающие файлы
        arg.c = 1;
        arg.l = 1;
        break;
      case 'n':  // Вывод номера строки
        arg.n = 1;
        break;
      case 'h':  // Вывод без названия файлов
        arg.h = 1;
        break;
      case 's':  // Убрать вывод при неправильной подаче
        arg.s = 1;
        break;
      case 'f':  // форматный вывод
        arg.f = 1;
        add_reg_from_file(&arg, optarg);
        break;
      case 'o':  // совпадающие и непустые строки
        arg.o = 1;
        break;
      case '?':
        if (!arg.s)
          printf(
              "grep: неверный ключ — «%c»\nИспользование: grep [ПАРАМЕТР]… "
              "ШАБЛОНЫ [ФАЙЛ]…\nЗапустите «grep --help» для получения более "
              "подробного описания.\n",
              opt);
        exit(1);
        break;
    }
  }
  if (arg.len_pattenr == 0) {
    pattern_add(&arg, argv[optind]);
    optind++;
  }
  if (argc - optind == 1) arg.h = 1;  // Костыль для одного файла
  return arg;
}

void outline(char const *line, int lenght) {
  for (int i = 0; i < lenght; i++) putchar(line[i]);
  if (line[lenght - 1] != '\n') putchar('\n');  // фича для переноса строки
}

void process_file(arguments arg, char const *path, regex_t *regex) {
  FILE *f = fopen(path, "r");
  if (f == NULL) {
    if (!arg.s) printf("grep: %s: Нет такого файла или каталога\n", path);
    regfree(regex);
    exit(1);
  }
  char *line = NULL;
  size_t memlen = 0;
  int read = 0;
  int line_count_in_file = 1;  // считаем все строки
  int count_coincidence = 0;

  while ((read = getline(&line, &memlen, f)) != -1) {
    int result = regexec(regex, line, 0, NULL, 0);
    if ((result == 0 && !arg.v) || (arg.v && result != 0)) {
      if (!arg.c && !arg.l) {
        if (!arg.h && !arg.o) printf("%s:", path);
        if (arg.n && !arg.o) printf("%d:", line_count_in_file);
        if (arg.o && result == 0) {
          print_o(regex, line, arg, line_count_in_file, path);
        } else if (!arg.o)
          outline(line, read);
      }
      count_coincidence++;
    }
    line_count_in_file++;
  };

  if (arg.c && !arg.l) {
    if (!arg.h) printf("%s:", path);
    printf("%d\n", count_coincidence);
  }
  if (arg.l && count_coincidence >= 1) printf("%s\n", path);
  free(line);
  fclose(f);
}

void output(arguments arg, int argc, char **argv) {
  regex_t regex;
  int error = regcomp(&regex, arg.pattern, REG_EXTENDED | arg.i);
  if (error) perror("error");
  for (int i = optind; i < argc; i++) {
    process_file(arg, argv[i], &regex);
  }
  regfree(&regex);
}

void pattern_add(arguments *arg, char const *pattern) {
  if (arg->len_pattenr != 0) {
    strcat(arg->pattern + arg->len_pattenr, "|");
    arg->len_pattenr++;
  }
  arg->len_pattenr += sprintf(arg->pattern + arg->len_pattenr, "(%s)", pattern);
}

void add_reg_from_file(arguments *arg, char const *path) {
  {
    FILE *f = fopen(path, "r");
    if (f == NULL) {
      if (!arg->s) printf("grep: %s: Нет такого файла или каталога\n", path);
      exit(1);
    }
    char *line = NULL;
    size_t memlen = 0;
    int read = 0;
    while ((read = getline(&line, &memlen, f)) != -1) {
      if (line[strlen(line) - 1] == '\n') line[strlen(line) - 1] = '\0';
      pattern_add(arg, line);
    };
    free(line);
    fclose(f);
  }
}

void print_o(regex_t *regex, char *line, arguments arg, int line_count_in_file,
             char const *path) {
  regmatch_t math;
  int offset = 0;
  while (1) {
    int result = regexec(regex, line + offset, 1, &math, 0);
    if (result != 0) break;
    if (!arg.h) printf("%s:", path);
    if (arg.n && strlen(line) > 0) printf("%d:", line_count_in_file);
    for (int i = math.rm_so; i < math.rm_eo; i++) {
      putchar(line[offset + i]);
    }
    putchar('\n');
    offset += math.rm_eo;
  }
}