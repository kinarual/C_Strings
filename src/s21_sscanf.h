#ifndef S21_SSCANF_H
#define S21_SSCANF_H

#include <math.h>
#include <stdarg.h>

#include "s21_string.h"

#define LLONG_MAX 0x7fffffffffffffff
#define LLONG_MIN (-LLONG_MAX - 1LL)
#define ULLONG_MAX 0xffffffffffffffff
#define INT_MAX 0x7fffffff

typedef enum {
  spec_c,  //  cимвол
  spec_d,  //  Знаковое десятичное целое число
  spec_i,  //  Знаковое целое число (десятичное, восьмеричное или
           //  шестнадцатеричное)
  spec_e,  //  десятичное число с плавающей точкой или научная нотация
           //  (мантисса/экспонента)
  spec_E,  //  десятичное число с плавающей точкой или научная нотация
           //  (мантисса/экспонента)
  spec_f,  //  десятичное число с плавающей точкой или научная нотация
           //  (мантисса/экспонента)
  spec_g,  //  десятичное число с плавающей точкой или научная нотация
           //  (мантисса/экспонента)
  spec_G,  //  десятичное число с плавающей точкой или научная нотация
           //  (мантисса/экспонента)
  spec_o,  //  беззнаковое восьмеричное число
  spec_s,  //  строка
  spec_u,  //  беззнаковое десятичное целое число
  spec_x,  //  беззнаковое шестнадцатеричное целое число (любые буквы)
  spec_X,  //  беззнаковое шестнадцатеричное целое число (любые буквы)
  spec_p,  //  адрес указателя
  spec_n,  //  количество символов, считанных до появления %n
  spec_unknown
} sspecs;

typedef enum lens {
  len_none,
  len_h,
  len_l,
  len_L,
} lens;

typedef struct {
  sspecs spec;
  int width;
  lens len;
  bool skip;
} specifier;

int s21_sscanf(const char *str, const char *format, ...);
specifier scan_specifier(char **format);
bool is_digit(char c, int base);
s21_size_t to_digit(char c, int base);
bool strstr_icase(char **str, char *pat);
char chr_lower(char c);
int scan_width(char **f_str);
bool scan(specifier spec, char **str, va_list ap, int *res, char *start);

bool parse_string(specifier spec, char **str, va_list ap);

bool parse_int(specifier spec, char **str, va_list ap);
bool scan_int(char **str, int width, long long *dest);

bool parse_i_uint(specifier spec, char **str, va_list ap);
bool parse_hex(specifier spec, char **str, va_list ap, bool neg);
bool parse_oct(specifier spec, char **str, va_list ap, bool neg);
bool parse_uint(specifier spec, char **str, va_list ap, bool neg);
bool parse_based_uint(specifier spec, char **str, va_list ap, int base,
                      bool neg);
bool scan_based_uint(char **str, int width, unsigned long long *dest, int base,
                     bool neg);

bool parse_float(specifier spec, char **str, va_list ap);
bool scan_float(char **str, int width, long double *dest);
bool nan_inf(char **str, long double *dest);
long double s21_atof(char **str, int *width);
bool scientific(char **str, int *width, long double *res);

bool parse_ptr(specifier spec, char **str, va_list ap);

#endif
