#ifndef S21_SPRINTF_H_
#define S21_SPRINTF_H_

#include <math.h>

#include "s21_string.h"
#include "stdarg.h"

typedef struct {
  int minus;
  int plus;
  int space;
  int hash;
  int zero;
  int width;
  int accuracy;
  char length;
  int dot;
  int minus_accuracy;
} Spec;

int s21_sprintf(char *str, const char *format, ...);
const char *get_flags(const char *format, Spec *specs);
char *parser(char *str, const char *format, Spec specs, va_list *arguments);
const char *set_specs(Spec *specs, const char *format, va_list *arguments);
const char *get_length(const char *format, Spec *specs);
void print_c(char *str, Spec specs, int symbol);
void print_s(char *str, Spec specs, va_list *arguments);
void print_d(char *str, Spec specs, va_list *arguments);
void strrev(char *buff);
void print_u(char *str, Spec specs, va_list *arguments);
const char *check_width(const char *format, Spec *specs, va_list *arguments);
char *s21_strcat(char *dest, const char *src);
void add_f(char *str, Spec specs, va_list *arguments);

#endif
