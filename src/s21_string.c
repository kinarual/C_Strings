#include "s21_string.h"

s21_size_t s21_strcspn(const char *str1, const char *str2) {
  s21_size_t answer = 0;
  s21_size_t str1_len = s21_strlen(str1);
  s21_size_t str2_len = s21_strlen(str2);
  int flag = 1;
  int temp[256] = {};
  for (s21_size_t i = 0; i < str2_len; i++) {
    temp[(int)str2[i]] = 1;
  }
  for (s21_size_t i = 0; i < str1_len && flag; i++) {
    if (temp[(int)str1[i]] == 1) {
      answer = i;
      flag = 0;
    }
  }
  if (flag) answer = str1_len;
  return answer;
}

s21_size_t s21_strspn(const char *str1, const char *str2) {
  s21_size_t answer = 0;
  s21_size_t str1_len = s21_strlen(str1);
  s21_size_t str2_len = s21_strlen(str2);
  int temp[256] = {0};
  for (s21_size_t i = 0; i < str2_len; i++) {
    temp[(int)str2[i]] = 1;
  }
  for (s21_size_t i = 0; i < str1_len; i++) {
    if (temp[(int)str1[i]] != 1) {
      answer = i;
      break;
    }
  }
  return answer;
}

char *s21_strstr(const char *haystack, const char *needle) {
  char *answer = s21_NULL;
  s21_size_t haystack_len = s21_strlen(haystack);
  s21_size_t needle_len = s21_strlen(needle);
  for (s21_size_t i = 0; i < haystack_len; i++) {
    int flag = 1;
    for (s21_size_t j = 0; j < needle_len; j++) {
      if (haystack[i + j] != needle[j]) {
        flag = 0;
        break;
      }
    }
    if (flag == 1) {
      answer = (char *)haystack + i;
      break;
    }
  }
  return answer;
}

char *s21_strtok(char *str, const char *delim) {
  int flag = 1;
  static char *old;
  char *newStr = s21_NULL;

  if (!str) str = old;

  str += s21_strspn(str, delim);
  if (!*str) {
    old = str;
    flag = 0;
  }
  if (flag) {
    newStr = str;
    str = s21_strpbrk(str, delim);
    if (str) {
      *str = '\0';
      old = str + 1;
    } else {
      old = newStr + s21_strlen(newStr);
    }
  }
  return newStr;
}

s21_size_t s21_strlen(const char *str) {
  char *ptr = (char *)str;
  s21_size_t answer = 0;
  if (ptr) {
    while (*ptr != '\0') {
      ptr++;
      answer++;
    }
  }
  return answer;
}

char *s21_strpbrk(const char *str1, const char *str2) {
  char *result = s21_NULL;
  int flag = 0;
  while (*str1 != '\0' && flag == 0) {
    for (int j = 0; str2[j] != '\0'; j++) {
      if (*str1 == str2[j]) {
        flag = 1;
        result = (char *)str1;
      }
    }

    str1++;
  }
  return result;
}

void *s21_memchr(const void *str, int c, s21_size_t n) {
  //   /*НЕШТАТНЫЕ СИТУАЦИИ и КРАЕВЫЕ КЕЙСЫ
  //    1) некорректный указатель: *str == NULL. Вывод в терминале -
  //    segmentation fault. В тестах не реализовывается
  //    2) n = 0. Результат = 0, то результат работы функции - NULL (0x0)
  //    3) если n < 0 - стандартная функция выводит результат - функция может
  //    искать символ за пределами блока памяти.
  char *res = s21_NULL;
  if (str != s21_NULL) {
    char *p = (char *)str;
    for (s21_size_t i = 0; i < n && i < s21_strlen(p) && (res == s21_NULL);
         i++) {
      res = (p[i] == c) ? &p[i] : s21_NULL;
    }
  }
  return (void *)res;
}

int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
  //   /*НЕШТАТНЫЕ СИТУАЦИИ и КРАЕВЫЕ КЕЙСЫ
  //   1) некорректный указатель: *str1 или *str2 == NULL. Вывод в терминале -
  //   segmentation fault. В тестах не реализовывается.
  //   2) n = 0. Результат = 0, ничего не сравнивается
  //   3) если n < 0 - стандартная функция выводит результат - сравнивает с
  //   первого байта и идет до того, пока не найдет нулевой байт.
  // */
  int res = 0;
  if (str1 != s21_NULL && str2 != s21_NULL) {
    const char *p1 = (char *)str1;
    const char *p2 = (char *)str2;
    for (s21_size_t i = 0; i < n && res == 0; i++) {
      if (p1[i] - p2[i] != 0) res = (p1[i] - p2[i]);
    }
  }
  return res;
}

void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
  /*НЕШТАТНЫЕ СИТУАЦИИ и КРАЕВЫЕ КЕЙСЫ
  1) некорректные указатели: *str1 или *str2 == NULL. Вывод в терминале -
  segmentation fault. В тестах не реализовывается.
  2) если n > src || n > dest при компиляции с флагами выдает ошибку. Пример:
  writing 10 bytes into a region of size 5 overflows the destination. В тестах
  не реализовывается - выдаст ошибку (пример: '__builtin___memcpy_chk' writing 5
  bytes into a region of size 1 overflows the destination).
   */
  if (src != s21_NULL && dest != s21_NULL) {
    const char *p_src = (char *)src;
    char *p_dest = (char *)dest;
    for (s21_size_t i = 0; i < n; i++) {
      p_dest[i] = p_src[i];
    }
  }
  return dest;
}

char *s21_strerror(int errnum) {
  char *errors[] = ERR_MSGS;
  char *ptr;
  if (errnum >= 0 && errnum <= 133) {
    ptr = errors[errnum];
  } else {
    static char tmp[50];
    s21_sprintf(tmp, "%s %d", UE_MSG, errnum);
    ptr = tmp;
  }
  return ptr;
}

void *s21_memset(void *str, int c, s21_size_t n) {
  if (s21_strlen(str) >= n && str != s21_NULL) {
    char *buff = str;
    while (n > 0) {
      *buff = (char)c;
      buff++;
      n--;
    }
  }
  return str;
}

char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  char *tmp = dest;
  while (*tmp) {
    tmp++;
  }
  while (n-- && *src) {
    *(tmp++) = *(src++);
  }
  *tmp = 0;
  return dest;
}

int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
  int result = 0;
  for (s21_size_t i = 0; i < n && result == 0; i++) {
    if ((*(str1 + i) < *(str2 + i)) || (*(str1 + i) > *(str2 + i)))
      result = (*(str1 + i) - *(str2 + i));
    else if (*(str1 + i) == *(str2 + i))
      result = 0;
  }

  // if (result < 0)
  //   result = -1;
  // else if (result > 0)
  //   result = 1;

  return result;
}

char *s21_strchr(const char *str, int c) {
  char *result = s21_NULL;
  char *ptr = (char *)str;
  while (*ptr != '\0') {
    if (*ptr == c) {
      result = ptr;
      break;
    }
    ptr++;
  }
  if (*ptr == c) {
    result = ptr;
  }
  return result;
}

char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
  for (s21_size_t i = 0; i < n; i++) {
    *(dest + i) = *(src + i);
  }
  return dest;
}

char *s21_strrchr(const char *str, int c) {
  char *result = s21_NULL;
  char *ptr = (char *)str;
  while (*ptr != '\0') {
    if (*ptr == c) {
      result = ptr;
    }
    ptr++;
  }
  if (*ptr == c) {
    result = ptr;
  }
  return result;
}

void *s21_to_upper(const char *str) {
  char *new_str = (char *)calloc(s21_strlen(str) + 1, sizeof(char));
  int j = 0;
  for (long long unsigned int i = 0; i < s21_strlen(str); i++) {
    if (str[i] > 96 && str[i] < 123) {
      new_str[j] = str[i] - 32;
      j++;
    } else {
      new_str[j] = str[i];
      j++;
    }
  }
  return (void *)new_str;
}

void *s21_to_lower(const char *str) {
  char *new_str = (char *)calloc(s21_strlen(str) + 1, sizeof(char));
  int j = 0;
  for (long long unsigned int i = 0; i < s21_strlen(str); i++) {
    if (str[i] > 64 && str[i] < 91) {
      new_str[j] = str[i] + 32;
      j++;
    } else {
      new_str[j] = str[i];
      j++;
    }
  }
  return (void *)new_str;
}

void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
  char *new_str = s21_NULL;
  s21_size_t src_l = src ? s21_strlen(src) : 0;
  s21_size_t str_l = str ? s21_strlen(str) : 0;
  s21_size_t full_l = src_l + str_l;
  if (start_index <= src_l && src && str) {
    new_str = calloc(full_l + 2, sizeof(char));
    s21_size_t i = 0;
    int j = 0;
    int l = 0;
    for (; i < full_l;) {
      if (i == start_index && *(str + j) != '\0') {
        while (*(str + j) != '\0') {
          new_str[i++] = str[j++];
        }
      } else {
        new_str[i++] = src[l++];
      }
    }
  }
  return new_str;
}

void *s21_trim(const char *src, const char *trim_chars) {
  if (src == s21_NULL) return s21_NULL;
  char *new_str = s21_NULL;
  new_str = for_trim(src, trim_chars);
  char *res = s21_NULL;
  res = for_trim(new_str, trim_chars);
  free(new_str);
  return (void *)res;
}

void *for_trim(const char *src, const char *trim_chars) {
  char *new_str = (char *)calloc(s21_strlen(src) + 1, sizeof(char));
  int i = s21_strlen(src) - 1, j = 0;
  int n = 0;
  while (i > -1) {
    for (int k = 0; k < (int)s21_strlen(trim_chars); k++) {
      if (src[i] == trim_chars[k]) {
        i--;
        n = 1;
        break;
        ;
      } else {
        n = 0;
      }
    }
    if (n == 0) break;
  }
  for (; i >= 0; i--) {
    new_str[j] = src[i];
    j++;
  }
  return (void *)new_str;
}
