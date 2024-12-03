#include "s21_sprintf.h"

int s21_sprintf(char *str, const char *format, ...) {
  if (format == s21_NULL || str == s21_NULL) {
    if (format == s21_NULL) str[0] = '\0';
    return 0;
  }
  str[0] = '\0';
  char specificiers[] =
      "diuoxXcsnpfFeEgG%";  // изменить спецификаторы до выполненных
  va_list arguments;
  va_start(arguments, format);

  while (*format) {
    if (*format == '%') {
      format++;
      Spec specs = {0};
      format = set_specs(&specs, format, &arguments);
      while (!s21_strchr(specificiers, *format)) format++;
      str = parser(str, format, specs, &arguments);
    } else {
      char tmp[2];
      tmp[0] = *format;
      tmp[1] = '\0';
      s21_strcat(str, tmp);
    }
    format++;
  }
  va_end(arguments);
  return (int)s21_strlen(str);
}

const char *set_specs(Spec *specs, const char *format, va_list *arguments) {
  format = get_flags(format, specs);
  format = check_width(format, specs, arguments);
  if (*format == '.') {
    specs->dot = 1;
    specs->zero = 0;
    format++;
    format = check_width(format, specs, arguments);
  }
  format = get_length(format, specs);
  return format;
}

const char *get_flags(const char *format, Spec *specs) {
  while (*format == '-' || *format == '+' || *format == '#' || *format == ' ' ||
         *format == '0') {
    switch (*format) {
      case '-': {
        specs->minus = 1;
        break;
      }
      case '+': {
        specs->plus = 1;
        break;
      }
      case '#': {
        specs->hash = 1;
        break;
      }
      case ' ': {
        specs->space = 1;
        break;
      }
      case '0': {
        specs->zero = 1;
        break;
      }
      default:
        break;
    }
    format++;
  }
  specs->space = (specs->space && !specs->plus);
  specs->zero = (specs->zero && !specs->minus);
  return format;
}

char *parser(char *str, const char *format, Spec specs, va_list *arguments) {
  switch (*format) {
    case 'd': {
      print_d(str, specs, arguments);
      break;
    }
    case 'i': {
      print_d(str, specs, arguments);
      break;
    }
    case 'c': {
      int symbol = va_arg(*arguments, int);
      print_c(str, specs, symbol);
      break;
    }
    case 'u': {
      print_u(str, specs, arguments);
      break;
    }
    case 's': {
      print_s(str, specs, arguments);
      break;
    }
    case 'f': {
      add_f(str, specs, arguments);
      break;
    }
    case '%': {
      print_c(str, specs, '%');
      break;
    }
    default: {
      str = s21_NULL;
    }
  }
  return str;
}

const char *get_length(const char *format, Spec *specs) {
  if (format) {
    switch (*format) {
      case 'h':
        specs->length = 'h';
        break;
      case 'l':
        specs->length = 'l';
        break;
      case 'L':
        specs->length = 'L';
        break;
      default:
        break;
    }
    if (specs->length != 0) format++;
  }
  return format;
}

const char *check_width(const char *format, Spec *specs, va_list *arguments) {
  if (*format == '*') {
    if (specs->dot == 0) {
      specs->width = va_arg(*arguments, int);
    } else {
      specs->accuracy = va_arg(*arguments, int);
    }
    format++;
  }
  while (format != s21_NULL) {
    if (*format == '-') {
      specs->minus_accuracy = 1;
      format++;
    }
    if (*format >= '0' && *format <= '9') {
      if (specs->dot == 0) {
        specs->width = specs->width * 10 + *format - '0';
      } else {
        specs->accuracy = specs->accuracy * 10 + *format - '0';
      }
    } else
      break;
    format++;
  }
  return format;
}

void print_c(char *str, Spec specs, int symbol) {
  char tmp[2] = {0, '\0'};
  while (specs.width > 1 && !specs.minus) {
    tmp[0] = ' ';
    s21_strcat(str, tmp);
    specs.width--;
  }
  if (symbol <= 127) {
    tmp[0] = symbol;
    s21_strcat(str, tmp);
    while (specs.width > 1 && specs.minus) {
      tmp[0] = ' ';
      s21_strcat(str, tmp);
      specs.width--;
    }
  }
}

void print_s(char *str, Spec specs, va_list *arguments) {
  char *arg_str = va_arg(*arguments, char *);
  int init_width = specs.width;  //изначальная ширина
  if (arg_str != s21_NULL) {
    s21_size_t init_str_length = s21_strlen(str);
    s21_size_t arg_length = s21_strlen(arg_str);
    char tmp[2] = {0, '\0'};
    if ((s21_size_t)specs.width < arg_length)
      specs.width =
          arg_length;  //если ширина меньше длины строки, печатается ВСЯ строка
    s21_size_t space_count = (s21_size_t)specs.width - arg_length;
    if (specs.accuracy == 0 && specs.dot == 1) space_count = specs.width;
    if (specs.accuracy != 0 && specs.accuracy < init_width)
      space_count = init_width - specs.accuracy;
    if (specs.accuracy != 0 && specs.minus_accuracy == 1) {
      space_count = specs.accuracy;
      arg_length = 0;
    }
    s21_size_t chars_to_write = arg_length + space_count;
    if (specs.minus == 0) {
      while (space_count > 0) {
        tmp[0] = ' ';
        s21_strcat(str, tmp);
        space_count--;
      }
    }
    while (*arg_str != '\0') {
      if (specs.accuracy == 0 && specs.dot) break;
      tmp[0] = *arg_str;
      s21_strcat(str, tmp);
      arg_str++;
      specs.accuracy--;
    }
    if (specs.minus > 0) {
      while (space_count > 0) {
        tmp[0] = ' ';
        s21_strcat(str, tmp);
        space_count--;
      }
    }
    str[chars_to_write + init_str_length] = '\0';
  } else {
    str = s21_memcpy(str, "(null)", 6);
    str = str + 6;
  }
}

void s21_ftoa(long double value /*num*/, char *buff /*arg_str*/, Spec specs) {
  int accuracy = 6;
  if ((specs.accuracy != 6 && specs.accuracy != 0) ||
      (specs.accuracy == 0 && specs.dot == 1)) {
    accuracy = specs.accuracy;
  }
  buff[0] = '\0';
  int i = 0;
  long double y = 0;

  if (value - 0.0000001 == 0.0 - 0.0000001) {  // проверка был ли подан 0
    buff[0] = '0';
    if (specs.accuracy == 0 &&
        specs.dot == 1) {  //с точностью . печатается только целая часть
      buff[1] = '\0';
    } else {
      buff[1] = '.';
      for (int j = 2; j < accuracy + 2;
           j++) {  // от второго элемента массива размером в точность печатается
                   // 0
        buff[j] = '0';
        buff[j + 1] = '\0';
      }
    }
  } else {
    long double temp = value;
    if (value < 0) {
      temp *= -1;
      buff[i++] = '-';
    }
    temp = temp + 0.0000001;
    y = temp - (int)temp;  // выводим дробную часть числа value
    while (temp > 0 && (int)temp != 0) {
      double x = (long long int)temp % 10;  // поиск последней цифры числа
      buff[i++] = x + '0';  // запись цифры через символы в строку
      temp /= 10.0;  //переходим к следующей цифре
    }
    strrev(buff);

    if (temp > 0 && !(specs.accuracy == 0 && specs.dot == 1))
      buff[s21_strlen(buff)] = '.';
  }
  i++;
  int last_digit = 0;
  if (!(specs.accuracy == 0 &&
        specs.dot == 1)) {  //с точностью . печатается только целая часть
    while (y > 0 &&
           accuracy-- !=
               0) {  //Этот код добавляет десятичные цифры числа y к строке buff
      long int x = (long int)(y * 10);  // получение следующей десятичной цифры
      last_digit = x;
      buff[i++] = x + '0';  // запись цифры через символы в строку
      y = fmod((y * 10), 1.0);  // получаем десятичную часть числа
    }
    if (last_digit > 4) buff[s21_strlen(buff) - 1] = (last_digit + 1) + '0';
  }
  buff[s21_strlen(buff) + 1] = '\0';
}

void s21_uitoa(unsigned long long int value, char *buff) {
  int i = 0;
  while (value > 0) {
    int x = value % 10;
    buff[i++] = x + '0';
    value /= 10;
  }
  strrev(buff);
}

void s21_itoa(long long int value, char *buff) {
  int value_w = value < 0;
  int i = 0;
  if (value_w == 1) {
    value *= -1;
    buff[i++] = '-';
  }
  while (value > 0) {
    int x = value % 10;
    buff[i++] = x + '0';
    value /= 10;
  }
  strrev(buff);
}

void strrev(char *buff) {
  s21_size_t length = s21_strlen(buff);
  s21_size_t i = 0;
  if (buff[i] == '-') {
    i++;
    length++;
  }
  for (; i < length / 2; i++) {  // меняет местами символы
    char temp = buff[i];
    buff[i] = buff[length - i - 1];
    buff[length - i - 1] = temp;
  }
}

void print_d(char *str, Spec specs, va_list *arguments) {
  long int num = 0;
  if (specs.length == 'l') {
    num = (long int)va_arg(*arguments, long int);
  } else if (specs.length == 'h') {
    num = (short)va_arg(*arguments, int);
  } else {
    num = (int)va_arg(*arguments, int);
  }
  char arg_str[512] = "";
  s21_itoa(num, arg_str);

  size_t n = 0;
  size_t i = 0;
  char numb_buff[100] = "";

  if (num < 0) specs.space = 0;

  if (specs.accuracy > 0) {
    int y = s21_strlen(str) - specs.accuracy - 1;
    str[y] = '\0';
  }

  if (specs.minus > 0 && specs.zero == 0) {
    s21_strcat(numb_buff, arg_str);
  }

  if (specs.minus == 0 && specs.plus == 0) {
    if (specs.space == 0) {
      s21_strcat(numb_buff, arg_str);
    }
    if (specs.space == 1) {
      s21_strcat(numb_buff, " ");
      s21_strcat(numb_buff, arg_str);
    }
  }
  if (specs.plus == 1) {
    if (specs.minus == 0) {
      s21_strcat(numb_buff, "+");
      s21_strcat(numb_buff, arg_str);
    }
  }
  if ((s21_size_t)specs.width < specs.width - s21_strlen(numb_buff) &&
      specs.minus == 0) {
    s21_strcat(str, numb_buff);
  }
  if ((s21_size_t)specs.width < specs.width - s21_strlen(numb_buff) &&
      specs.minus == 1) {
    s21_strcat(str, numb_buff);
  }

  if ((s21_size_t)specs.width > specs.width - s21_strlen(arg_str) &&
      specs.minus == 0) {
    n = specs.width - s21_strlen(numb_buff);

    if (specs.zero == 0) {
      while (i < n) {
        s21_strcat(str, " ");
        i++;
      }
    }
    if (specs.zero == 1) {
      n = specs.width - s21_strlen(arg_str);
      if (specs.minus > 0) {
        s21_strcat(str, "-");
        i++;
      }
      if (specs.plus == 1 && specs.minus == 0) {
        s21_strcat(str, "+");
        i++;
      }
      while (i < n) {
        s21_strcat(str, "0");
        i++;
      }
      s21_strcat(str, arg_str);
    }
    if (specs.zero == 0) {
      s21_strcat(str, numb_buff);
    }
  }
  if ((s21_size_t)specs.width > specs.width - s21_strlen(numb_buff) &&
      specs.minus == 1) {
    s21_strcat(str, numb_buff);
    n = specs.width - s21_strlen(str);
    while (i < n) {
      s21_strcat(str, " ");
      i++;
    }
  }
  if (specs.minus > 0 &&
      (s21_size_t)specs.width < specs.width - s21_strlen(str) &&
      specs.zero == 1) {
    s21_strcat(str, "-");
    s21_strcat(str, arg_str);
  }
}

void print_u(char *str, Spec specs, va_list *arguments) {
  unsigned long int num = 0;
  if (specs.length == 'l') {
    num = (unsigned long int)va_arg(*arguments, unsigned long int);
  } else if (specs.length == 'h') {
    num = (unsigned short)va_arg(*arguments, unsigned int);
  } else {
    num = (unsigned int)va_arg(*arguments, unsigned int);
  }
  char arg_str[512] = "";
  s21_uitoa(num, arg_str);

  size_t n = 0;
  size_t i = 0;
  char numb_buff[100] = "";
  if (specs.accuracy > 0) {
    int y = s21_strlen(str) - specs.accuracy - 1;
    str[y] = '\0';
  }

  if (specs.minus > 0 && specs.zero == 0) {
    s21_strcat(numb_buff, arg_str);
  }

  if (specs.minus == 0 && specs.plus == 0) {
    s21_strcat(numb_buff, arg_str);
  }
  if (specs.plus == 1) {
    if (specs.minus == 0) {
      s21_strcat(numb_buff, "+");
      s21_strcat(numb_buff, arg_str);
    }
  }
  if ((s21_size_t)specs.width < specs.width - s21_strlen(numb_buff) &&
      specs.minus == 0) {
    s21_strcat(str, numb_buff);
  }
  if ((s21_size_t)specs.width < specs.width - s21_strlen(numb_buff) &&
      specs.minus == 1) {
    s21_strcat(str, numb_buff);
  }

  if ((s21_size_t)specs.width > specs.width - s21_strlen(arg_str) &&
      specs.minus == 0) {
    n = specs.width - s21_strlen(numb_buff);

    if (specs.zero == 0) {
      while (i < n) {
        s21_strcat(str, " ");
        i++;
      }
    }
    if (specs.zero == 1) {
      n = specs.width - s21_strlen(arg_str);
      if (specs.minus > 0) {
        s21_strcat(str, "-");
        i++;
      }
      if (specs.plus == 1 && specs.minus == 0) {
        s21_strcat(str, "+");
        i++;
      }
      while (i < n) {
        s21_strcat(str, "0");
        i++;
      }
      s21_strcat(str, arg_str);
    }
    if (specs.zero == 0) {
      s21_strcat(str, numb_buff);
    }
  }
  if ((s21_size_t)specs.width > specs.width - s21_strlen(numb_buff) &&
      specs.minus == 1) {
    s21_strcat(str, numb_buff);
    n = specs.width - s21_strlen(str);
    while (i < n) {
      s21_strcat(str, " ");
      i++;
    }
  }
  if (specs.minus > 0 &&
      (s21_size_t)specs.width < specs.width - s21_strlen(str) &&
      specs.zero == 1) {
    s21_strcat(str, "-");
    s21_strcat(str, arg_str);
  }
}

void add_f(char *str, Spec specs, va_list *arguments) {
  long double num = 0;

  if (specs.length == 'L') {
    num = va_arg(*arguments, long double);
  } else {
    num = va_arg(*arguments, double);
  }

  char arg_str[512] = "";
  arg_str[0] = '\0';
  s21_ftoa(num, arg_str, specs);

  char numb_buff[512];
  numb_buff[0] = '\0';

  if (num < 0) specs.space = 0;

  if (specs.minus == 1 || specs.plus == 1 || specs.hash == 0) {
    if (specs.space == 0) {
      s21_strcat(numb_buff, arg_str);
    }
    if (specs.space == 1) {
      s21_strcat(numb_buff, " ");
      s21_strcat(numb_buff, arg_str);
    }
  }
  if (specs.hash == 1) {
    if (specs.space == 0) {
      s21_strcat(numb_buff, arg_str);
    }
    if (specs.space == 1) {
      s21_strcat(numb_buff, " ");
      s21_strcat(numb_buff, arg_str);
    }
  }
  if (specs.plus == 1) {
    s21_strcat(str, "+");
  }

  if ((s21_size_t)specs.width <
          (s21_size_t)specs.width - s21_strlen(numb_buff) &&
      specs.minus == 0) {
    s21_strcat(str, numb_buff);
  }
  if ((s21_size_t)specs.width <
          (s21_size_t)specs.width - s21_strlen(numb_buff) &&
      specs.minus == 1) {
    s21_strcat(str, numb_buff);
  }

  int numb_length = s21_strlen(numb_buff);
  int chars_to_write = (s21_size_t)specs.width - numb_length;
  if (chars_to_write > 0) {
    if (specs.minus == 1) {
      for (int m = 0; m < chars_to_write; m++) {
        numb_buff[numb_length + m] = ' ';
        numb_buff[numb_length + m + 1] = '\0';
      }
    } else {
      char new_str[(chars_to_write + numb_length)];
      new_str[0] = '\0';
      for (int k = 0; k < chars_to_write; k++) {
        new_str[k] = ' ';
        new_str[k + 1] = '\0';
      }
      s21_strcat(str, new_str);
    }
    s21_strcat(str, numb_buff);
  }
}

char *s21_strcat(char *dest, const char *src) {
  s21_size_t size = s21_strlen(dest);
  int i = 0;
  for (; *(src + i) != '\0'; i++) {
    *(dest + size + i) = *(src + i);
  }
  *(dest + size + i) = '\0';
  return dest;
}
