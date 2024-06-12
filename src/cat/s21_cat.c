#include "s21_cat.h"

int main(int argc, char* argv[]) {
  int flag_error = 0;
  int tmp_str_len = 1;   // Кол непустых строк
  int full_str_len = 1;  // Кол пустых строк
  if (argc > 1) {
    arguments arg = argument_parser(argc, argv, &flag_error);
    if (!flag_error) {
      while (arg.number_files < argc) {
        scanline(argv[arg.number_files], &arg, &tmp_str_len, &full_str_len);
        arg.number_files += 1;
      }
    }
  }

  return 0;
}

arguments argument_parser(int argc, char* argv[], int* flag_error) {
  arguments arg = {0};
  struct option long_options[] = {{"number", no_argument, NULL, 'n'},
                                  {"number-nonblank", no_argument, NULL, 'b'},
                                  {"squeeze-blank", no_argument, NULL, 's'},
                                  {0, 0, 0, 0}};
  int opt;
  while ((opt = getopt_long(argc, argv, "bnEeTtsv", long_options, 0)) != -1) {
    switch (opt) {
      case 'b':
        arg.b = 1;
        break;
      case 'n':
        arg.n = 1;
        break;
      case 's':
        arg.s = 1;
        break;
      case 'e':
        arg.E = 1;
        arg.v = 1;
        break;
      case 'E':
        arg.E = 1;
        break;
      case 'v':
        arg.v = 1;
        break;
      case 't':
        arg.T = 1;
        arg.v = 1;
        break;
      case 'T':
        arg.T = 1;
        break;
      case '?':
        *flag_error = 1;
        break;
      default:
        printf(
            "неверный ключ — «%d»\nПо команде «cat --help» можно получить "
            "дополнительную информацию.\n",
            opt);
        break;
    }
  }
  if (arg.n && arg.b) arg.n = 0;

  arg.number_files = optind;
  return arg;
}

void scanline(const char* imput_file_name, arguments* arg, int* tmp_str_len,
              int* full_str_len) {
  FILE* file = fopen(imput_file_name, "r");
  if (file == NULL) {
    printf("cat: %s: Нет такого файла или каталога\n", imput_file_name);
  } else {
    char* line = NULL;
    size_t len = 0;
    int test_tpm = 0;            // Чек файл новый или нет
    int right_lenght = 0;        // Правильная длина строки
    int s_count_emply_line = 0;  // Чекнуть предыдущю строку
    while ((right_lenght = getline(&line, &len, file)) != -1) {
      if (arg->s) {
        if (line[0] == '\n')
          s_count_emply_line++;
        else
          s_count_emply_line = 0;
      }
      if (arg->n || arg->b) {
        if (arg->b && line[0] != '\n' && (*tmp_str_len == 1 || test_tpm != 0)) {
          printf("%6d\t", (*tmp_str_len)++);
        } else if (arg->n && (*full_str_len == 1 || test_tpm != 0)) {
          printf("%6d\t", (*full_str_len)++);
        }
      }

      if (s_count_emply_line <= 1) outline(line, right_lenght, arg);
      test_tpm++;
    }
    free(line);
    fclose(file);
  }
}

char v_converses(char ch) {
  if (ch == '\n' || ch == '\t') return ch;
  if (ch < 0) {
    printf("M-");
    ch = ch & 0x7F;
  }
  if (ch >= 0 && ch <= 31) {
    putchar('^');
    ch += 64;
  } else if (ch == 127) {
    putchar('^');
    ch = '?';
  }
  return ch;
}

void outline(char* line, int lenght, const arguments* arg) {
  for (int i = 0; i < lenght; i++) {
    if (arg->E && line[i] == '\n') printf("$");
    if (arg->v) line[i] = v_converses(line[i]);
    if (arg->T && line[i] == '\t') {
      putchar('^');
      line[i] = 'I';
    }
    putchar(line[i]);
  }
}
