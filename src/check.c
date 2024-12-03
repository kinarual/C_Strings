#include "check.h"

#include <string.h>

#include "s21_string.h"
#include "stdlib.h"

// //strcspn
START_TEST(test_s21_strcspn) {
  char *str1 = "I hate everything about you, Why do I love you?";
  char *str2 = ",y-f";
  ck_assert_int_eq(s21_strcspn(str1, str2), strcspn(str1, str2));

  char *str3 = "I hate everything about you, Why do I love you?";
  char *str4 = "-";
  ck_assert_int_eq(s21_strcspn(str3, str4), strcspn(str3, str4));

  char *str5 = "I hate everything about you, Why do I love you?";
  char *str6 = "?";
  ck_assert_int_eq(s21_strcspn(str5, str6), strcspn(str5, str6));

  char *str7 = "...I hate everYthing about you /Why do I love you?";
  char *str8 = "/";
  ck_assert_int_eq(s21_strcspn(str7, str8), strcspn(str7, str8));
}
END_TEST

// strstr
START_TEST(test_s21_strstr) {
  char *str1 = "\0";
  char *str2 = "hate";
  ck_assert_ptr_eq(s21_strstr(str1, str2), strstr(str1, str2));

  char *str3 = "I hate everything about you, Why do I love you?";
  char *str4 = "ate";
  ck_assert_ptr_eq(s21_strstr(str3, str4), strstr(str3, str4));

  char *str5 = "I hate everything about you, Why do I love you?";
  char *str6 = " ";
  ck_assert_ptr_eq(s21_strstr(str5, str6), strstr(str5, str6));

  char *str7 = "...I hate everYthing about you /Why do I love you?";
  char *str8 = "/";
  ck_assert_ptr_eq(s21_strstr(str7, str8), strstr(str7, str8));

  char *str9 = "...I hate everYthing about you /Why do I love you?";
  char *str10 = "Skillet";
  ck_assert_ptr_eq(s21_strstr(str9, str10), strstr(str9, str10));
}
END_TEST

// strtok
START_TEST(test_s21_strtok) {
  char var_1[12] = "ni.i.ii.hao";
  char var_2[12] = "ho..ambooam.";
  char var_3[12] = ".long";
  char var_4[12] = "\0";
  char var_5[12] = "nefrrrrtttt";
  char var_6[12] = "hoabooam";
  char var_1_s21[12] = "ni.i.ii.hao";
  char var_2_s21[12] = "ho..ambooam.";
  char var_3_s21[12] = ".long";
  char var_4_s21[12] = "\0";
  char var_5_s21[12] = "nefrrrrtttt";
  char var_6_s21[12] = "hoabooam";
  for (int i = 0; i < 5; i++) {
    ck_assert_str_eq(strtok(var_1, "."), s21_strtok(var_1_s21, "."));
  }
  for (int i = 0; i < 5; i++) {
    ck_assert_str_eq(strtok(var_2, "."), s21_strtok(var_2_s21, "."));
  }
  for (int i = 0; i < 5; i++) {
    ck_assert_str_eq(strtok(var_3, "."), s21_strtok(var_3_s21, "."));
  }
  for (int i = 0; i < 5; i++) {
    ck_assert_msg(strtok(var_4, ".") == s21_strtok(var_4_s21, "."),
                  "strtok_null_test");
  }
  for (int i = 0; i < 5; i++) {
    ck_assert_str_eq(strtok(var_5, "rt"), s21_strtok(var_5_s21, "rt"));
  }
  for (int i = 0; i < 5; i++) {
    ck_assert_str_eq(strtok(var_6, "am"), s21_strtok(var_6_s21, "am"));
  }

  char arr1[100] = "I must confess that ...I feel like a monster";
  char *parr1 = arr1;
  char arr2[100] = "I must confess that ...I feel like a monster";
  char *parr2 = arr2;
  s21_strtok(parr1, " .");
  strtok(parr2, " .");
  ck_assert_str_eq(parr1, parr2);
  parr1 = s21_strtok(NULL, " .");
  parr2 = strtok(NULL, " .");
  ck_assert_str_eq(parr1, parr2);
  parr1 = s21_strtok(NULL, " .");
  parr2 = strtok(NULL, " .");
  ck_assert_str_eq(parr1, parr2);
}

// memchr
START_TEST(test_s21_memchr) {
  ck_assert_pstr_eq(memchr("", 'w', 10),
                    s21_memchr("", 'w', 10));  // return null

  ck_assert_pstr_eq(
      memchr("Hello world", 'w', 0),
      s21_memchr("Hello world", 'w', 0));  // n == 0 -> return null
  ck_assert_pstr_eq(
      memchr("Hello world", 'w', -50),
      s21_memchr("Hello world", 'w', -50));  // n < 0 -> return world
  ck_assert_pstr_eq(memchr("Hello world", 'w', 10),
                    s21_memchr("Hello world", 'w', 10));  // -> return world
  ck_assert_pstr_eq(
      memchr("Hello world", 'w', 12345678),
      s21_memchr("Hello world", 'w', 12345678));  // -> return world
  ck_assert_pstr_eq(memchr("Hello world", 0, 10),
                    s21_memchr("Hello world", 0, 10));  // -> return null
  ck_assert_pstr_eq(memchr("Привет мир", 'a', 10),
                    s21_memchr("Привет мир", 'a', 10));  // -> return null
  ck_assert_pstr_eq(memchr("She says, \"We've gotta hold on to what we've got "
                           "It doesn't "  // return 've gotta hold on to what
                                          // we've got It doesn't make a
                                          // difference if we make it or not"
                           "make a difference if we make it or not\"",
                           39, 44),
                    s21_memchr("She says, \"We've gotta hold on to what we've "
                               "got It doesn't "
                               "make a difference if we make it or not\"",
                               39, 44));
}
END_TEST

// memcmp
START_TEST(test_s21_memcmp) {
  ck_assert_int_eq(memcmp("", "h", 6), s21_memcmp("", "h",
                                                  6));  // return -104

  ck_assert_int_eq(memcmp("Hello", "Hello", 6),  // return 0
                   s21_memcmp("Hello", "Hello", 6));

  ck_assert_int_eq(memcmp("Hello", "Hello", 0),  // n == 0 -> return 0
                   s21_memcmp("Hello", "Hello", 0));

  char str1[] = "helLo";
  char str2[] = "hello";
  ck_assert_int_eq(memcmp(str1, str2, 6),
                   s21_memcmp(str1, str2, 6));  // return -32
  ck_assert_int_eq(memcmp(str1, str2, 2),
                   s21_memcmp(str1, str2, 2));  // return 0

  char str3[] = "hel";
  char str4[] = "hello";
  ck_assert_int_eq(memcmp(str3, str4, 6),
                   s21_memcmp(str3, str4, 6));  // return -108

  char str7[] = "hel^Lo";
  char str8[] = "he^llo";
  ck_assert_int_eq(memcmp(str7, str8, 6),
                   s21_memcmp(str7, str8, 6));  // return 14
  ck_assert_int_eq(memcmp(str7, str8, 2),
                   s21_memcmp(str7, str8, 2));  // return 0

  char str9[] = "Woah, we're halfway there. Woah-oh, livin' on a prayer.";
  char str10[] = "Woah, we're halfway there. Woah-oh, livin' on a Prayer.";
  ck_assert_int_eq(memcmp(str9, str10, 50),
                   s21_memcmp(str9, str10, 50));  // return 32
  ck_assert_int_eq(memcmp(str9, str10, -25),
                   s21_memcmp(str9, str10, -25));  // return 32
}
END_TEST

// // memcpy
START_TEST(test_s21_memcpy) {
  char src[] = "GoodbyeEtrttrtr";
  char dest_o[] = "Suns";
  char dest_s[] = "Suns";
  ck_assert_pstr_eq(memcpy(dest_o, src, 2),
                    s21_memcpy(dest_s, src, 2));  // return Gons

  char src1[] = "Good";
  char dest1_o[] = "Sunshine";
  char dest1_s[] = "Sunshine";
  ck_assert_pstr_eq(memcpy(dest1_o, src1, 4),
                    s21_memcpy(dest1_s, src1, 4));  // return Goodhine

  char src3[] = "Good";
  char dest3_o[] = "Sunshine";
  char dest3_s[] = "Sunshine";
  ck_assert_pstr_eq(memcpy(dest3_o, src3, 0),
                    s21_memcpy(dest3_s, src3, 0));  // return original dest

  char src4[] = "Good";
  char dest4_o[] = "";
  char dest4_s[] = "";
  ck_assert_pstr_eq(memcpy(dest4_o, src4, 0),
                    s21_memcpy(dest4_s, src4, 0));  // return original dest

  char src5[] = "Good";
  char dest5_o[1024] = "";
  char dest5_s[1024] = "";
  ck_assert_pstr_eq(memcpy(dest5_o, src5, 4),
                    s21_memcpy(dest5_s, src5, 4));  // return Good

  char src6[1024] = "MUSCLE_\0MUSEUM";
  char dest6_o[1024] = "";
  char dest6_s[1024] = "";
  ck_assert_pstr_eq(memcpy(dest6_o, src6, 7),
                    s21_memcpy(dest6_s, src6, 7));  // return "MUSCLE "

  char src7[1024] = "MUSCLE_\0MUSEUM";
  char dest7_o[1024] = "";
  char dest7_s[1024] = "";
  ck_assert_pstr_eq(memcpy(dest7_o, src7 + 5, 10),
                    s21_memcpy(dest7_s, src7 + 5, 10));  // return "E_"

  char src8[1024] = "MUSCLE_MUSE\0UM";
  char dest8_o[1024] = "ORANG_E";
  char dest8_s[1024] = "ORANG_E";
  ck_assert_pstr_eq(memcpy(dest8_o + 5, src8 + 7, 11),
                    s21_memcpy(dest8_s + 5, src8 + 7, 11));  // return "MUSE"
}
END_TEST

// sprintf without format
START_TEST(test_sprintf_empty) {
  char str_e1[512];
  char str_e2[512];
  ck_assert_int_eq(s21_sprintf(str_e1, "abc"), sprintf(str_e2, "abc"));
  ck_assert_str_eq(str_e1, str_e2);

  char str_e3[512];
  char str_e4[512];
  ck_assert_int_eq(s21_sprintf(str_e3, "\n\n"), sprintf(str_e4, "\n\n"));
  ck_assert_str_eq(str_e3, str_e4);

  char str_e5[1024];
  char str_e6[1024];
  ck_assert_int_eq(s21_sprintf(str_e5, s21_NULL),
                   s21_sprintf(str_e6, s21_NULL));
  ck_assert_str_eq(str_e5, str_e6);
}
END_TEST

// sprintf with %%
START_TEST(test_sprintf_percent) {
  char str_p1[512];
  char str_p2[512];
  ck_assert_int_eq(s21_sprintf(str_p1, "Loading ... 99%%"),
                   sprintf(str_p2, "Loading ... 99%%"));
  ck_assert_str_eq(str_p1, str_p2);

  char str_p3[512];
  char str_p4[512];
  ck_assert_int_eq(s21_sprintf(str_p3, "-7.0%%"), sprintf(str_p4, "-7.0%%"));
  ck_assert_str_eq(str_p3, str_p4);
}
END_TEST

// sprintf with %c
START_TEST(test_s21_sprintf_c) {
  char str1_1[1024];
  char str1_2[1024];
  char *format1 = "%c";
  ck_assert_int_eq(s21_sprintf(str1_1, format1, 'c'),
                   sprintf(str1_2, format1, 'c'));
  ck_assert_str_eq(str1_1, str1_2);

  char str2_1[1024];
  char str2_2[1024];
  char *format2 = "%c";
  ck_assert_int_eq(s21_sprintf(str2_1, format2, 99),
                   sprintf(str2_2, format2, 99));
  ck_assert_str_eq(str2_1, str2_2);

  char str3_1[1024];
  char str3_2[1024];
  char *format3 = "%-c";
  ck_assert_int_eq(s21_sprintf(str3_1, format3, 'F'),
                   sprintf(str3_2, format3, 'F'));
  ck_assert_str_eq(str3_1, str3_2);

  char str4_1[1024];
  char str4_2[1024];
  char *format4 = "%-3c";
  ck_assert_int_eq(s21_sprintf(str4_1, format4, 'F'),
                   sprintf(str4_2, format4, 'F'));
  ck_assert_str_eq(str4_1, str4_2);

  char str5_1[1024];
  char str5_2[1024];
  char *format5 = "%-5.0c";
  ck_assert_int_eq(s21_sprintf(str5_1, format5, 'F'),
                   sprintf(str5_2, format5, 'F'));
  ck_assert_str_eq(str5_1, str5_2);

  char str6_1[1024];
  char str6_2[1024];
  char *format6 = "%5.2c";
  ck_assert_int_eq(s21_sprintf(str6_1, format6, 'F'),
                   sprintf(str6_2, format6, 'F'));
  ck_assert_str_eq(str6_1, str6_2);

  char str7_1[1024];
  char str7_2[1024];
  char *format7 = "%3c";
  ck_assert_int_eq(s21_sprintf(str7_1, format7, 'F'),
                   sprintf(str7_2, format7, 'F'));
  ck_assert_str_eq(str7_1, str7_2);

  char str8_1[1024];
  char str8_2[1024];
  char *format8 = "%.5c";
  ck_assert_int_eq(s21_sprintf(str8_1, format8, 'v'),
                   sprintf(str8_2, format8, 'v'));
  ck_assert_str_eq(str8_1, str8_2);

  char str9_1[1024];
  char str9_2[1024];
  char *format9 = "%-20.8c%c%c%c%c Try me! NIHAO";
  ck_assert_int_eq(s21_sprintf(str9_1, format9, 'h', 'e', 'l', 'l', 'o'),
                   sprintf(str9_2, format9, 'h', 'e', 'l', 'l', 'o'));
  ck_assert_str_eq(str9_1, str9_2);

  char str9_3[1024];
  char str9_4[1024];
  ck_assert_int_eq(
      s21_sprintf(str9_3, "%3c%-11c%10c%-2c%c", '\t', '\n', '0', 'F', 'f'),
      sprintf(str9_4, "%3c%-11c%10c%-2c%c", '\t', '\n', '0', 'F', 'f'));
  ck_assert_str_eq(str9_3, str9_4);

  // char str9_5[1024];
  // char str9_6[1024];
  // ck_assert_int_eq(s21_sprintf(s21_NULL, "%3c", 'c'),
  //                  s21_sprintf(NULL, "%3c", 'c'));
  // ck_assert_str_eq(str9_5, str9_6);

  // char str9_7[1024];
  // char str9_8[1024];
  // ck_assert_int_eq(s21_sprintf(str9_7, s21_NULL),
  //                  s21_sprintf(str9_8, s21_NULL));
  // ck_assert_str_eq(str9_7, str9_8);

  char str9_9[1024];
  char str9_10[1024];
  char *format9_star = "%-*.*c%c%c%c%c Try me! NIHAO";
  ck_assert_int_eq(
      s21_sprintf(str9_9, format9_star, 10, 2, 'h', 'e', 'l', 'l', 'o'),
      sprintf(str9_10, format9_star, 10, 2, 'h', 'e', 'l', 'l', 'o'));
  ck_assert_str_eq(str9_9, str9_10);
}
END_TEST

// sprintf with %s
START_TEST(test_s21_sprintf_s) {
  char str10_1[1024];
  char str10_2[1024];
  char *format10 = "%3s";
  ck_assert_int_eq(s21_sprintf(str10_1, format10, "Hello from the other side"),
                   sprintf(str10_2, format10, "Hello from the other side"));
  ck_assert_str_eq(str10_1, str10_2);

  char str11_1[1024];
  char str11_2[1024];
  char *format11 = "%28.2s";
  ck_assert_int_eq(s21_sprintf(str11_1, format11, "Hello from the other side"),
                   sprintf(str11_2, format11, "Hello from the other side"));
  ck_assert_str_eq(str11_1, str11_2);

  char str12_1[1024];
  char str12_2[1024];
  char *format12 = "%28.0s";
  ck_assert_int_eq(s21_sprintf(str12_1, format12, "Hello from the other side"),
                   sprintf(str12_2, format12, "Hello from the other side"));
  ck_assert_str_eq(str12_1, str12_2);

  char str13_1[1024];
  char str13_2[1024];
  char *format13 = "%26s";
  ck_assert_int_eq(s21_sprintf(str13_1, format13, "Hello from the other side"),
                   sprintf(str13_2, format13, "Hello from the other side"));
  ck_assert_str_eq(str13_1, str13_2);

  char str14_1[1024];
  char str14_2[1024];
  char *format14 = "%25s";
  ck_assert_int_eq(s21_sprintf(str14_1, format14, "Hello from the other side"),
                   sprintf(str14_2, format14, "Hello from the other side"));
  ck_assert_str_eq(str14_1, str14_2);

  char str15_1[1024];
  char str15_2[1024];
  char *format15 = "%-3s";
  ck_assert_int_eq(s21_sprintf(str15_1, format15, "Hello from the other side"),
                   sprintf(str15_2, format15, "Hello from the other side"));
  ck_assert_str_eq(str15_1, str15_2);

  char str16_1[1024];
  char str16_2[1024];
  char *format16 = "%-28.2s";
  ck_assert_int_eq(s21_sprintf(str16_1, format16, "Hello from the other side"),
                   sprintf(str16_2, format16, "Hello from the other side"));
  ck_assert_str_eq(str16_1, str16_2);

  char str17_1[1024];
  char str17_2[1024];
  char *format17 = "%-28.0s";
  ck_assert_int_eq(s21_sprintf(str17_1, format17, "Hello from the other side"),
                   sprintf(str17_2, format17, "Hello from the other side"));
  ck_assert_str_eq(str17_1, str17_2);

  char str18_1[1024];
  char str18_2[1024];
  char *format18 = "%-26s";
  ck_assert_int_eq(s21_sprintf(str18_1, format18, "Hello from the other side"),
                   sprintf(str18_2, format18, "Hello from the other side"));
  ck_assert_str_eq(str18_1, str18_2);

  char str19_1[1024];
  char str19_2[1024];
  char *format19 = "%-25s";
  ck_assert_int_eq(s21_sprintf(str19_1, format19, "Hello from the other side"),
                   sprintf(str19_2, format19, "Hello from the other side"));
  ck_assert_str_eq(str19_1, str19_2);

  char str20_1[1024];
  char str20_2[1024];
  char *format20 = "%-31.33s";
  ck_assert_int_eq(s21_sprintf(str20_1, format20, "Hello from the other side"),
                   sprintf(str20_2, format20, "Hello from the other side"));
  ck_assert_str_eq(str20_1, str20_2);

  char str21_1[1024];
  char str21_2[1024];
  char *format21 = "%-28.5s";
  ck_assert_int_eq(s21_sprintf(str21_1, format21, "Hello from the other side"),
                   sprintf(str21_2, format21, "Hello from the other side"));
  ck_assert_str_eq(str21_1, str21_2);

  char str22_1[1024];
  char str22_2[1024];
  char *format22 = "%-10s";
  ck_assert_int_eq(s21_sprintf(str22_1, format22, "\n\t\n\t\n"),
                   sprintf(str22_2, format22, "\n\t\n\t\n"));
  ck_assert_str_eq(str22_1, str22_2);

  char str23_1[1024];
  char str23_2[1024];
  char *format23 = "%s";
  ck_assert_int_eq(s21_sprintf(str23_1, format23, s21_NULL),
                   sprintf(str23_2, format23, NULL));
  ck_assert_str_eq(str23_1, str23_2);
}
END_TEST

// sprintf with %d
START_TEST(test_s21_sprintf_d) {
  char str1[128] = "";
  char str2[128] = "";
  char *format = "%hd";

  ck_assert_int_eq(s21_sprintf(str1, format, 6), sprintf(str2, format, 6));

  ck_assert_str_eq(str1, str2);

  char str3[128] = "";
  char str4[128] = "";
  char *format1 = "%------------5d";
  ck_assert_int_eq(s21_sprintf(str3, format1, -2), sprintf(str4, format1, -2));

  ck_assert_str_eq(str3, str4);

  char str5[128] = "";
  char str6[128] = "";
  char *format2 = "%-5i";

  ck_assert_int_eq(s21_sprintf(str5, format2, 31), sprintf(str6, format2, 31));

  ck_assert_str_eq(str5, str6);

  char str7[128] = "";
  char str8[128] = "";
  char *format3 = "%+12d";
  ck_assert_int_eq(s21_sprintf(str7, format3, 31), sprintf(str8, format3, 31));

  ck_assert_str_eq(str7, str8);

  char str9[128] = "";
  char str10[128] = "";
  char *format4 = "%.d";
  ck_assert_int_eq(s21_sprintf(str9, format4, 31), sprintf(str10, format4, 31));

  ck_assert_str_eq(str9, str10);

  char str11[128] = "";
  char str12[128] = "";
  char *format5 = "%05d";
  ck_assert_int_eq(s21_sprintf(str11, format5, 31),
                   sprintf(str12, format5, 31));

  ck_assert_str_eq(str11, str12);

  char str13[128] = "";
  char str14[128] = "";
  char *format6 = "%0.*ld";

  ck_assert_int_eq(s21_sprintf(str13, format6, 5, 8768797658888),
                   sprintf(str14, format6, 5, 8768797658888));

  ck_assert_str_eq(str13, str14);

  char str15[128] = "";
  char str16[128] = "";
  char *format7 = "% -+#d";

  ck_assert_int_eq(s21_sprintf(str15, format7, -31),
                   sprintf(str16, format7, -31));

  ck_assert_str_eq(str15, str16);

  char str17[128] = "";
  char str18[128] = "";
  char *format8 = "%-5d";

  ck_assert_int_eq(s21_sprintf(str17, format8, 31),
                   sprintf(str18, format8, 31));

  ck_assert_str_eq(str17, str18);

  char str19[128] = "";
  char str20[128] = "";
  char *format9 = "% d";

  ck_assert_int_eq(s21_sprintf(str19, format9, 31),
                   sprintf(str20, format9, 31));

  ck_assert_str_eq(str19, str20);

  char str21[128] = "";
  char str22[128] = "";
  char *format10 = "%-d";
  ck_assert_int_eq(s21_sprintf(str21, format10, 31),
                   sprintf(str22, format10, 31));

  ck_assert_str_eq(str21, str22);
}
END_TEST

// sprintf with %u
START_TEST(test_s21_sprintf_u) {
  char str1[128] = "";
  char str2[128] = "";
  char *format = "%u";

  ck_assert_int_eq(s21_sprintf(str1, format, 6), sprintf(str2, format, 6));

  ck_assert_str_eq(str1, str2);

  char str3[128] = "";
  char str4[128] = "";
  char *format1 = "%6u";
  ck_assert_int_eq(s21_sprintf(str3, format1, 31), sprintf(str4, format1, 31));

  ck_assert_str_eq(str3, str4);

  char str5[128] = "";
  char str6[128] = "";
  char *format2 = "%-5u";

  ck_assert_int_eq(s21_sprintf(str5, format2, 31), sprintf(str6, format2, 31));

  ck_assert_str_eq(str5, str6);

  char str7[128] = "";
  char str8[128] = "";
  char *format3 = "%-13u";
  ck_assert_int_eq(s21_sprintf(str7, format3, 31), sprintf(str8, format3, 31));

  ck_assert_str_eq(str7, str8);

  char str9[128] = "";
  char str10[128] = "";
  char *format4 = "%0.u";
  ck_assert_int_eq(s21_sprintf(str9, format4, 31), sprintf(str10, format4, 31));

  ck_assert_str_eq(str9, str10);

  char str11[128] = "";
  char str12[128] = "";
  char *format5 = "%.0u";
  ck_assert_int_eq(s21_sprintf(str11, format5, 31),
                   sprintf(str12, format5, 31));

  ck_assert_str_eq(str11, str12);

  char str13[128] = "";
  char str14[128] = "";
  char *format6 = "%0.*lu";

  ck_assert_int_eq(s21_sprintf(str13, format6, 5, 87687976588),
                   sprintf(str14, format6, 5, 87687976588));

  ck_assert_str_eq(str13, str14);

  char str15[128] = "";
  char str16[128] = "";
  char *format7 = "% u";

  ck_assert_int_eq(s21_sprintf(str15, format7, 31),
                   sprintf(str16, format7, 31));

  ck_assert_str_eq(str15, str16);

  char str17[128] = "";
  char str18[128] = "";
  char *format8 = "%hu";

  ck_assert_int_eq(s21_sprintf(str17, format8, 6), sprintf(str18, format8, 6));

  ck_assert_str_eq(str17, str18);

  char str19[128] = "";
  char str20[128] = "";
  char *format9 = "+%u";

  ck_assert_int_eq(s21_sprintf(str19, format9, 6), sprintf(str20, format9, 6));

  ck_assert_str_eq(str19, str20);

  char str21[128] = "";
  char str22[128] = "";
  char *format10 = "%05u";
  ck_assert_int_eq(s21_sprintf(str21, format10, 31),
                   sprintf(str22, format10, 31));

  ck_assert_str_eq(str21, str22);
}
END_TEST

// sprintf with %f
START_TEST(test_s21_sprintf_f) {
  char str1[128] = "";
  char str2[128] = "";
  char *format = "%-lf";
  ck_assert_int_eq(s21_sprintf(str1, format, -12.36),
                   sprintf(str2, format, -12.36));

  ck_assert_str_eq(str1, str2);

  char str3[128] = "";
  char str4[128] = "";
  char *format1 = "% 0lf";

  ck_assert_float_eq(s21_sprintf(str3, format1, 12.36),
                     sprintf(str4, format1, 12.36));

  ck_assert_str_eq(str3, str4);

  char str5[128] = "";
  char str6[128] = "";
  char *format2 = "%+lf";
  ck_assert_float_eq(s21_sprintf(str5, format2, 2.36),
                     sprintf(str6, format2, 2.36));

  ck_assert_str_eq(str5, str6);

  char str7[128] = "";
  char str8[128] = "";
  char *format3 = "%#lf";
  ck_assert_float_eq(s21_sprintf(str7, format3, 2.36),
                     sprintf(str8, format3, 2.36));

  ck_assert_str_eq(str7, str8);

  char str11[128] = "";
  char str12[128] = "";
  char *format5 = "%5lf";

  ck_assert_float_eq(s21_sprintf(str11, format5, 7253757.1431341),
                     sprintf(str12, format5, 7253757.1431341));

  ck_assert_str_eq(str11, str12);

  char str9[128] = "";
  char str10[128] = "";
  char *format4 = "%.6lf";
  ck_assert_int_eq(s21_sprintf(str9, format4, 13.31),
                   sprintf(str10, format4, 13.31));
  ck_assert_str_eq(str9, str10);

  char str13[128] = "";
  char str14[128] = "";
  char *format6 = "%f";
  ck_assert_int_eq(s21_sprintf(str13, format6, 0), sprintf(str14, format6, 0));
  ck_assert_str_eq(str13, str14);

  char str15[128] = "";
  char str16[128] = "";
  char *format7 = "%.lf %Lf %f %lf %Lf";
  double val1 = 0;
  long double val2 = 3515315.153151;
  float val3 = 5.5;
  double val4 = 9851.51351;
  long double val5 = 1234567891.65432;
  ck_assert_int_eq(s21_sprintf(str15, format7, val1, val2, val3, val4, val5),
                   sprintf(str16, format7, val1, val2, val3, val4, val5));
  ck_assert_str_eq(str15, str16);

  char str17[128] = "";
  char str18[128] = "";
  char *format8 = "%*.*f";
  double val6 = 123.456;
  ck_assert_int_eq(s21_sprintf(str17, format8, 15, 2, val6),
                   sprintf(str18, format8, 15, 2, val6));
  ck_assert_str_eq(str17, str18);
}
END_TEST

// sprintf with several %
START_TEST(test_s21_sprintf_sev) {
  char str1[512] = "";
  char str2[512] = "";
  char *format = "%5.2s %5d %c %3u %12i %12.4f";
  ck_assert_int_eq(
      s21_sprintf(str1, format, "Hello", 12, 97, 14, 41513, 451.1234),
      sprintf(str2, format, "Hello", 12, 97, 14, 41513, 451.1234));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_s21_strlen) {
  char str[] = "hello world!";
  char str1[] = " ";
  char str2[] = "\0";
  char str3[] = "\0NULL123";
  char str4[] = "";

  ck_assert_int_eq(strlen(str), s21_strlen(str));
  ck_assert_int_eq(strlen(str1), s21_strlen(str1));
  ck_assert_int_eq(strlen(str2), s21_strlen(str2));
  ck_assert_int_eq(strlen(str3), s21_strlen(str3));
  ck_assert_int_eq(strlen(str4), s21_strlen(str4));
  ck_assert_uint_eq(strlen(str4), s21_strlen(str4));
  ck_assert(strcmp(str, "hello world!") == 0);
}
END_TEST

START_TEST(test_s21_strpbrk) {
  char str1[20] = "hello world!1230";
  char str2[20] = "rw";
  char str3[20] = "033";
  char str4[20] = "\n\00";
  char str5[20] = "88";
  char str6[20] = " ";

  ck_assert_ptr_eq(strpbrk(str1, str2), s21_strpbrk(str1, str2));
  ck_assert_ptr_eq(strpbrk(str1, str3), s21_strpbrk(str1, str3));
  ck_assert_ptr_eq(strpbrk(str1, str4), s21_strpbrk(str1, str4));
  ck_assert_ptr_eq(strpbrk(str1, str5), s21_strpbrk(str1, str5));
  ck_assert_ptr_eq(strpbrk(str1, str6), s21_strpbrk(str1, str6));
}
END_TEST

START_TEST(test_s21_strerror_1) {
  ck_assert_pstr_eq(s21_strerror(0), strerror(0));
  ck_assert_pstr_eq(s21_strerror(-1), strerror(-1));
  ck_assert_pstr_eq(s21_strerror(-2), strerror(-2));
  ck_assert_pstr_eq(s21_strerror(-18), strerror(-18));
  ck_assert_pstr_eq(s21_strerror(-75), strerror(-75));
}
END_TEST

START_TEST(test_s21_memset) {
  char str[25] = "Hello world!";
  ck_assert_pstr_eq(s21_memset(str, 'x', 5), memset(str, 'x', 5));
  char str1[25] = "\nHello world!";
  ck_assert_pstr_eq(s21_memset(str1, 'x', 5), memset(str1, 'x', 5));
  char str2[25] = "\0Hello world!";
  ck_assert_pstr_eq(s21_memset(str2, 'x', 5), memset(str2, 'x', 5));
  char str3[25] = "\nHello world!";
  ck_assert_pstr_eq(s21_memset(str3, 'x', 5), memset(str3, 'x', 5));
  char str4[25] = "";
  ck_assert_pstr_eq(s21_memset(str4, 'x', 5), memset(str4, 'x', 5));
  char str5[25] = "Hello world!";
  ck_assert_pstr_eq(s21_memset(str5, 25, 5), memset(str5, 25, 5));
  char str6[25] = "Hello world!";
  ck_assert_pstr_eq(s21_memset(str6, 100, 5), memset(str6, 100, 5));
}
END_TEST

START_TEST(test_s21_strncat) {
  char str1[50] = "Hello world!";
  char str2[50] = "XXXXXXXx";
  char str3[25] = "LLL";
  char str4[25] = "UUUU";
  ck_assert_str_eq(strncat(str1, str2, 5), s21_strncat(str1, str2, 5));
  ck_assert_str_eq(strncat(str1, str2, 10), s21_strncat(str1, str2, 10));
  ck_assert_ptr_eq(strncat(str1, str2, 19), s21_strncat(str1, str2, 19));
  ck_assert_ptr_eq(strncat(str3, str4, 1), s21_strncat(str3, str4, 1));
}
END_TEST

START_TEST(test_s21_strncmp) {
  char str1[] = "Hello world!";
  char str2[] = "Hello world!";
  char str3[] = "hello world!";
  char str4[] = "helpo wol!";
  char str5[] = "";
  char str6[] = "\0";
  char str7[] = "Hello world!Hello world!";
  ck_assert_int_eq(s21_strncmp(str1, str2, 10), strncmp(str1, str2, 10));
  ck_assert_int_eq(s21_strncmp(str1, str3, 10), strncmp(str1, str3, 10));
  ck_assert_int_eq(s21_strncmp(str1, str4, 10), strncmp(str1, str4, 10));
  ck_assert_int_eq(s21_strncmp(str1, str5, 10), strncmp(str1, str5, 10));
  ck_assert_int_eq(s21_strncmp(str1, str2, 10), strncmp(str1, str2, 10));
  ck_assert_int_eq(s21_strncmp(str1, str6, 10), strncmp(str1, str6, 10));
  ck_assert_int_eq(s21_strncmp(str1, str7, 10), strncmp(str1, str7, 10));
  ck_assert_int_eq(s21_strncmp(str7, str1, 10), strncmp(str7, str1, 10));
  ck_assert_int_eq(s21_strncmp(str5, str2, 10), strncmp(str5, str2, 10));
}

START_TEST(test_s21_strncpy) {
  char str1[100] = "libcheck.github.io/check/";
  char str2[100] = "Linux, macOS, Windows";
  ck_assert_ptr_eq(strncpy(str1, str2, 5), s21_strncpy(str1, str2, 5));
  char str3[100] = "Linux, ";
  char str4[100] = "github.\0";
  ck_assert_ptr_eq(strncpy(str3, str4, 3), s21_strncpy(str3, str4, 3));
  char str5[100] = "\tgithub.";
  char str6[100] = "\tgithub.";
  ck_assert_ptr_eq(strncpy(str5, str6, 8), s21_strncpy(str5, str6, 8));
}

END_TEST

START_TEST(test_s21_strrchr) {
  char str1[100] = "";
  char str2 = 'O';
  ck_assert_ptr_eq(strrchr(str1, str2), s21_strrchr(str1, str2));
  char str3[100] = "run boy run";
  char str4 = 'R';
  ck_assert_ptr_eq(strrchr(str3, str4), s21_strrchr(str3, str4));
  char str5[100] = "I JUST WANNA SHINE TOGETHER ON zE MIAMY BEACH";
  char str6 = 'z';
  ck_assert_str_eq(strrchr(str5, str6), s21_strrchr(str5, str6));
  char str7[100] = "go a go b go c go d";
  char str8 = 'l';
  ck_assert_ptr_eq(strrchr(str7, str8), s21_strrchr(str7, str8));
  char str9[100] = "RatioOmagadYouAreSoPerfectoMomemto!!";
  char str10 = ' ';
  ck_assert_ptr_eq(strrchr(str9, str10), s21_strrchr(str9, str10));
}
END_TEST

START_TEST(test_s21_to_lower) {
  char *res1_1 = s21_NULL;
  res1_1 = s21_to_lower("DianaDmitrievna G");
  char *res1_2 = "dianadmitrievna g";
  char *res2_1 = s21_NULL;
  res2_1 = s21_to_lower("PETUNIA13579 p24680g");
  char *res2_2 = "petunia13579 p24680g";
  char *res3_1 = s21_NULL;
  res3_1 = s21_to_lower("");
  char *res3_2 = "";
  char *res4_1 = s21_NULL;
  res4_1 = s21_to_lower(" Petunia@ $ ^ & * DmItRiEvNa");
  char *res4_2 = " petunia@ $ ^ & * dmitrievna";
  char *res5_1 = s21_NULL;
  res5_1 = s21_to_lower(" ()****) #@       ");
  char *res5_2 = " ()****) #@       ";

  ck_assert_str_eq(res1_1, res1_2);
  ck_assert_str_eq(res2_1, res2_2);
  ck_assert_str_eq(res3_1, res3_2);
  ck_assert_str_eq(res4_1, res4_2);
  ck_assert_str_eq(res5_1, res5_2);

  if (res1_1) free(res1_1);
  if (res2_1) free(res2_1);
  if (res3_1) free(res3_1);
  if (res4_1) free(res4_1);
  if (res5_1) free(res5_1);
}
END_TEST

START_TEST(test_s21_to_upper) {
  char *res1_1 = s21_NULL;
  res1_1 = s21_to_upper("DianaDmitrievna G");
  char *res1_2 = "DIANADMITRIEVNA G";
  char *res2_1 = s21_NULL;
  res2_1 = s21_to_upper("PETUNIA13579 p24680g");
  char *res2_2 = "PETUNIA13579 P24680G";
  char *res3_1 = s21_NULL;
  res3_1 = s21_to_upper("");
  char *res3_2 = "";
  char *res4_1 = s21_NULL;
  res4_1 = s21_to_upper(" Petunia@ $ ^ & * DmItRiEvNa");
  char *res4_2 = " PETUNIA@ $ ^ & * DMITRIEVNA";
  char *res5_1 = s21_NULL;
  res5_1 = s21_to_upper(" ()****) #@       ");
  char *res5_2 = " ()****) #@       ";

  ck_assert_str_eq(res1_1, res1_2);
  ck_assert_str_eq(res2_1, res2_2);
  ck_assert_str_eq(res3_1, res3_2);
  ck_assert_str_eq(res4_1, res4_2);
  ck_assert_str_eq(res5_1, res5_2);

  if (res1_1) free(res1_1);
  if (res2_1) free(res2_1);
  if (res3_1) free(res3_1);
  if (res4_1) free(res4_1);
  if (res5_1) free(res5_1);
}
END_TEST

START_TEST(test_s21_insert) {
  char src[] = "Hello,  !";
  char *res1_1 = s21_NULL;
  res1_1 = s21_insert(src, "world", 7);
  char *res1_2 = "Hello, world !";
  char *res2_1 = s21_NULL;
  res2_1 = s21_insert(src, "world", 10);
  char *res2_2 = s21_NULL;
  char *res3_1 = s21_NULL;
  res3_1 = s21_insert(src, "AI ", 0);
  char *res3_2 = "AI Hello,  !";
  char *res4_1 = s21_NULL;
  res4_1 = s21_insert("", " ", 0);
  char *res4_2 = " ";
  char *res5_1 = s21_NULL;
  res5_1 = s21_insert("", " ", 1);
  char *res5_2 = s21_NULL;

  ck_assert_pstr_eq(res1_1, res1_2);
  ck_assert_pstr_eq(res2_1, res2_2);
  ck_assert_pstr_eq(res3_1, res3_2);
  ck_assert_pstr_eq(res4_1, res4_2);
  ck_assert_pstr_eq(res5_1, res5_2);

  free(res1_1);
  free(res2_1);
  free(res3_1);
  free(res4_1);
  free(res5_1);
}
END_TEST

START_TEST(test_s21_trim) {
  char *res1_1 = s21_NULL;
  res1_1 = s21_trim(" DianaDmitrievna G  ", " ");
  char *res1_2 = "DianaDmitrievna G";
  char *res2_1 = s21_NULL;
  res2_1 = s21_trim("PETUNIA13579 p24680g", "Pg");
  char *res2_2 = "ETUNIA13579 p24680";
  char *res3_1 = s21_NULL;
  res3_1 = s21_trim("", "12345");
  char *res3_2 = "";
  char *res4_1 = s21_NULL;
  res4_1 = s21_trim(" Petunia@ $ ^ & * DmItRiEvNa", " Pea");
  char *res4_2 = "tunia@ $ ^ & * DmItRiEvN";
  char *res5_1 = s21_NULL;
  res5_1 = s21_trim("#@# ()****) #@       ", "#@ ");
  char *res5_2 = "()****)";

  ck_assert_str_eq(res1_1, res1_2);
  ck_assert_str_eq(res2_1, res2_2);
  ck_assert_str_eq(res3_1, res3_2);
  ck_assert_str_eq(res4_1, res4_2);
  ck_assert_str_eq(res5_1, res5_2);

  if (res1_1) free(res1_1);
  if (res2_1) free(res2_1);
  if (res3_1) free(res3_1);
  if (res4_1) free(res4_1);
  if (res5_1) free(res5_1);
}
END_TEST

START_TEST(test_s21_sscanf) {
  int a = 0;
  int b = 0;
  ck_assert_int_eq(s21_sscanf("123", "%d", &a), sscanf("123", "%d", &b));
  ck_assert_int_eq(a, b);

  short sa = 0;
  short sb = 0;
  ck_assert_int_eq(s21_sscanf("123456", "%hd", &sa),
                   sscanf("123456", "%hd", &sb));
  ck_assert_int_eq(sa, sb);

  ck_assert_int_eq(s21_sscanf("98765", "%3d", &a), sscanf("98765", "%3d", &b));
  ck_assert_int_eq(a, b);

  ck_assert_int_eq(s21_sscanf("98765", "%3hd%d", &sa, &a),
                   sscanf("98765", "%3hd%d", &sb, &b));
  ck_assert_int_eq(sa, sb);
  ck_assert_int_eq(a, b);

  int c = 0;
  int d = 0;
  ck_assert_int_eq(s21_sscanf("111%111", "%d%%%d", &a, &b),
                   sscanf("111%111", "%d%%%d", &c, &d));
  ck_assert_int_eq(a, c);
  ck_assert_int_eq(b, d);

  ck_assert_int_eq(s21_sscanf("222%222", "%d %d", &a, &b),
                   sscanf("222%222", "%d %d", &c, &d));
  ck_assert_int_eq(a, c);
  ck_assert_int_eq(b, d);

  ck_assert_int_eq(s21_sscanf("333abcde333", "%dabcde%d", &a, &b),
                   sscanf("333abcde333", "%dabcde%d", &c, &d));
  ck_assert_int_eq(a, c);
  ck_assert_int_eq(b, d);

  ck_assert_int_eq(s21_sscanf("44", "%1d %1d", &a, &b),
                   sscanf("44", "%1d %1d", &c, &d));
  ck_assert_int_eq(a, c);
  ck_assert_int_eq(b, d);

  ck_assert_int_eq(s21_sscanf("4 4", "%d%d", &a, &b),
                   sscanf("4 4", "%d%d", &c, &d));
  ck_assert_int_eq(a, c);
  ck_assert_int_eq(b, d);

  ck_assert_int_eq(s21_sscanf(" ", "%%"), sscanf(" ", "%%"));

  // пустая строка
  ck_assert_int_eq(s21_sscanf("", "%d", &a), sscanf("", "%d", &b));
  ck_assert_int_eq(a, b);

  // строки с пробелами
  ck_assert_int_eq(s21_sscanf(" ", "%d", &a), sscanf(" ", "%d", &b));
  ck_assert_int_eq(a, b);

  // пустая форматная строка с флагом -Werror sscanf не работает
  // ck_assert_int_eq(s21_sscanf("123", "", &a), sscanf("123", "", &b));
  ck_assert_int_eq(s21_sscanf("123", ""), 0);
  ck_assert_int_eq(s21_sscanf("123", "a"), sscanf("123", "a"));

  // скип числа
  ck_assert_int_eq(s21_sscanf("123123", "%*3d%d", &a),
                   sscanf("123123", "%*3d%d", &b));
  ck_assert_int_eq(a, b);

  // несуществующий формат
  ck_assert_int_eq(s21_sscanf("123", "%a", &a), -1);
  ck_assert_int_eq(a, b);
}
END_TEST

START_TEST(test_parse_int) {
  short sa = 0, sb = 0, sc = 0, sd = 0;
  int a = 0, b = 0;
  long la = 0, lb = 0, lc = 0, ld = 0;

  ck_assert_int_eq(s21_sscanf("123456123", "%6hd%hd", &sa, &sb),
                   sscanf("123456123", "%6hd%hd", &sc, &sd));
  ck_assert_int_eq(sa, sc);
  ck_assert_int_eq(sb, sd);

  ck_assert_int_eq(s21_sscanf("12345678901", "%d", &a),
                   sscanf("12345678901", "%d", &b));
  ck_assert_int_eq(a, b);

  ck_assert_int_eq(s21_sscanf("-12345678901", "%d", &a),
                   sscanf("-12345678901", "%d", &b));
  ck_assert_int_eq(a, b);

  ck_assert_int_eq(s21_sscanf("-12345678901", "%ld", &la),
                   sscanf("-12345678901", "%ld", &lb));
  ck_assert_int_eq(la, lb);

  // переполнение longlong
  ck_assert_int_eq(s21_sscanf("12345678901234567890", "%ld", &la),
                   sscanf("12345678901234567890", "%ld", &lb));
  ck_assert_int_eq(la, lb);

  ck_assert_int_eq(s21_sscanf("-12345678901234567890", "%ld", &la),
                   sscanf("-12345678901234567890", "%ld", &lb));
  ck_assert_int_eq(la, lb);

  // переполнение на целый круг
  lb = 0;
  ck_assert_int_eq(s21_sscanf("19223372036854775807", "%ld%ld", &la, &lb),
                   sscanf("19223372036854775807", "%ld%ld", &lc, &ld));
  ck_assert_int_eq(la, lc);
  ck_assert_int_eq(lb, ld);

  // понижение разряда при переполнении
  ck_assert_int_eq(s21_sscanf("12345678901234567890", "%d", &a),
                   sscanf("12345678901234567890", "%d", &b));
  ck_assert_int_eq(a, b);

  ck_assert_int_eq(s21_sscanf("-12345678901234567890", "%d", &a),
                   sscanf("-12345678901234567890", "%d", &b));
  ck_assert_int_eq(a, b);

  // long long
  long long lla = 0, llb = 0, llc = 0, lld = 0;
  ck_assert_int_eq(s21_sscanf("123456789012345", "%lld", &lla),
                   sscanf("123456789012345", "%lld", &llb));
  ck_assert_int_eq(lla, llb);

  ck_assert_int_eq(
      s21_sscanf("-123456789012345678901", "%21lld%lld", &lla, &llb),
      sscanf("-123456789012345678901", "%21lld%lld", &llc, &lld));
  ck_assert_int_eq(lla, llc);
  ck_assert_int_eq(llb, lld);

  ck_assert_int_eq(s21_sscanf("987654321", "%lld", &lla),
                   sscanf("987654321", "%lld", &llb));  // Ld - long long
  // Ахах это УБ
  ck_assert_int_eq(lla, llb);

  // нет числа совсем
  ck_assert_int_eq(s21_sscanf("abc", "%d", &a), sscanf("abc", "%d", &b));
  ck_assert_int_eq(a, b);

  // отрицательное ничего
  ck_assert_int_eq(s21_sscanf("-abc", "%d", &a), sscanf("-abc", "%d", &b));
  ck_assert_int_eq(a, b);

  // слишком широкий спецификатор
  ck_assert_int_eq(s21_sscanf("123", "%5d", &a), sscanf("123", "%5d", &b));
  ck_assert_int_eq(a, b);

  // with +
  ck_assert_int_eq(s21_sscanf("++321", "%d", &a), sscanf("++321", "%d", &b));
  ck_assert_int_eq(a, b);

  ck_assert_int_eq(s21_sscanf("+321", "%d", &a), sscanf("+321", "%d", &b));
  ck_assert_int_eq(a, b);

  ck_assert_int_eq(s21_sscanf("+98765", "%*5d%d", &a),
                   sscanf("+98765", "%*5d%d", &b));
  ck_assert_int_eq(a, b);
}
END_TEST

START_TEST(test_parse_uint) {
  unsigned int a = 0, b = 0;
  unsigned long la = 0, lb = 0;
  unsigned long long lla = 0, llb = 0;

  ck_assert_int_eq(s21_sscanf("1234567890", "%u", &a),
                   sscanf("1234567890", "%u", &b));
  ck_assert_int_eq(a, b);

  ck_assert_int_eq(s21_sscanf("12345678901", "%u", &a),
                   sscanf("12345678901", "%u", &b));
  ck_assert_int_eq(a, b);

  // переполнение
  ck_assert_int_eq(s21_sscanf("123456789012345678901", "%llu", &lla),
                   sscanf("123456789012345678901", "%llu", &llb));
  ck_assert_int_eq(la, lb);

  ck_assert_int_eq(s21_sscanf("12345678901234567890123", "%22llu", &lla),
                   sscanf("12345678901234567890123", "%22llu", &llb));
  ck_assert_int_eq(la, lb);

  unsigned short sa = 0, sb = 0;
  ck_assert_int_eq(s21_sscanf("1234567890", "%5hu%lu", &sa, &la),
                   sscanf("1234567890", "%5hu%lu", &sb, &lb));
  ck_assert_int_eq(sa, sb);
  ck_assert_int_eq(la, lb);

  // слишком широкий спецификатор
  ck_assert_int_eq(s21_sscanf("123", "%5u", &a), sscanf("123", "%5u", &b));
  ck_assert_int_eq(a, b);

  // -
  ck_assert_int_eq(s21_sscanf("-123", "%u", &a), sscanf("-123", "%u", &b));
  ck_assert_int_eq(a, b);

  // +
  ck_assert_int_eq(s21_sscanf("+123", "%u", &a), sscanf("+123", "%u", &b));
  ck_assert_int_eq(a, b);

  ck_assert_int_eq(s21_sscanf("+123", "%*2u%u", &a),
                   sscanf("+123", "%*2u%u", &b));
  ck_assert_int_eq(a, b);
}
END_TEST

START_TEST(test_parse_hex) {
  unsigned int a = 0, b = 0;
  // 0x
  ck_assert_int_eq(s21_sscanf("0x1234567890", "%x", &a),
                   sscanf("0x1234567890", "%x", &b));
  ck_assert_int_eq(a, b);

  // 0X
  ck_assert_int_eq(s21_sscanf("0X1234567890", "%x", &a),
                   sscanf("0X1234567890", "%x", &b));
  ck_assert_int_eq(a, b);

  // a - f
  ck_assert_int_eq(s21_sscanf("0x1abcdef", "%X", &a),
                   sscanf("0x1abcdef", "%X", &b));
  ck_assert_int_eq(a, b);

  // A - F
  ck_assert_int_eq(s21_sscanf("0X1ACDEF", "%X", &a),
                   sscanf("0X1ACDEF", "%X", &b));
  ck_assert_int_eq(a, b);

  // switch case
  ck_assert_int_eq(s21_sscanf("0x1aBcDeF", "%x", &a),
                   sscanf("0x1AbCdEf", "%x", &b));
  ck_assert_int_eq(a, b);

  // half prefix
  ck_assert_int_eq(s21_sscanf("01aBcDeF", "%x", &a),
                   sscanf("01AbCdEf", "%x", &b));
  ck_assert_int_eq(a, b);

  ck_assert_int_eq(s21_sscanf("01aBcDeF", "%X", &a),
                   sscanf("01AbCdEf", "%X", &b));
  ck_assert_int_eq(a, b);

  // bad prefix
  ck_assert_int_eq(s21_sscanf("x1aBcDeF", "%x", &a),
                   sscanf("x1AbCdEf", "%x", &b));
  ck_assert_int_eq(a, b);
  ck_assert_int_eq(s21_sscanf("X1aBcDeF", "%X", &a),
                   sscanf("X1AbCdEf", "%X", &b));
  ck_assert_int_eq(a, b);

  // -
  ck_assert_int_eq(s21_sscanf("-0x1aBcDeF", "%x", &a),
                   sscanf("-0x1AbCdEf", "%x", &b));
  ck_assert_int_eq(a, b);

  // +
  ck_assert_int_eq(s21_sscanf("++0x1aBcDeF", "%x", &a),
                   sscanf("++0x1AbCdEf", "%x", &b));
  ck_assert_int_eq(a, b);

  ck_assert_int_eq(s21_sscanf("+0x1aBcDeF", "%x", &a),
                   sscanf("+0x1AbCdEf", "%x", &b));
  ck_assert_int_eq(a, b);
}
END_TEST

START_TEST(test_parse_oct) {
  unsigned int a = 0, b = 0;
  // prefix
  ck_assert_int_eq(s21_sscanf("01234567", "%o", &a),
                   sscanf("01234567", "%o", &b));
  ck_assert_int_eq(a, b);
  // no prefix
  ck_assert_int_eq(s21_sscanf("21234567", "%o", &a),
                   sscanf("21234567", "%o", &b));
  ck_assert_int_eq(a, b);

  // -
  ck_assert_int_eq(s21_sscanf("-01234567", "%o", &a),
                   sscanf("-01234567", "%o", &b));
  ck_assert_int_eq(a, b);

  // bad prefix
  ck_assert_int_eq(s21_sscanf("0-1234567", "%o", &a),
                   sscanf("0-1234567", "%o", &b));

  // +
  a = 0, b = 0;
  ck_assert_int_eq(s21_sscanf("++01234567", "%o", &a),
                   sscanf("++01234567", "%o", &b));  // уб бан
  ck_assert_int_eq(a, b);

  ck_assert_int_eq(s21_sscanf("+01234567", "%o", &a),
                   sscanf("+01234567", "%o", &b));
  ck_assert_int_eq(a, b);
}
END_TEST

START_TEST(test_parse_i_uint) {
  unsigned int a = 0, b = 0;
  // no prefix
  ck_assert_int_eq(s21_sscanf("1234567890", "%i", &a),
                   sscanf("1234567890", "%i", &b));
  ck_assert_int_eq(a, b);

  // oct prefix
  ck_assert_int_eq(s21_sscanf("01234567", "%i", &a),
                   sscanf("01234567", "%i", &b));
  ck_assert_int_eq(a, b);

  // hex prefix
  ck_assert_int_eq(s21_sscanf("0x1234567890", "%i", &a),
                   sscanf("0x1234567890", "%i", &b));
  ck_assert_int_eq(a, b);

  // -
  ck_assert_int_eq(s21_sscanf("-1234567890", "%i", &a),
                   sscanf("-1234567890", "%i", &b));
  ck_assert_int_eq(a, b);

  // -0 prefix
  ck_assert_int_eq(s21_sscanf("-01234567", "%i", &a),
                   sscanf("-01234567", "%i", &b));
  ck_assert_int_eq(a, b);

  // -0x prefix
  ck_assert_int_eq(s21_sscanf("-0x1234567890", "%i", &a),
                   sscanf("-0x1234567890", "%i", &b));
  ck_assert_int_eq(a, b);

  // wierd -- prefix
  ck_assert_int_eq(s21_sscanf("--1234567890", "%i", &a),
                   sscanf("--1234567890", "%i", &b));
  ck_assert_int_eq(a, b);

  // wierd -0- prefix
  ck_assert_int_eq(s21_sscanf("-0-1234567890", "%i", &a),
                   sscanf("-0-1234567890", "%i", &b));
  ck_assert_int_eq(a, b);

  // wierd -0x- prefix
  ck_assert_int_eq(s21_sscanf("-0x-ab34567890", "%i", &a),
                   sscanf("-0x-ab34567890", "%i", &b));
  ck_assert_int_eq(a, b);

  // hex without prefix
  ck_assert_int_eq(s21_sscanf("123abcdef", "%i", &a),
                   sscanf("123abcdef", "%i", &b));
  ck_assert_int_eq(a, b);

  // hex without prefix starting with letter
  ck_assert_int_eq(s21_sscanf("a123abcdef", "%i", &a),
                   sscanf("a123abcdef", "%i", &b));
  ck_assert_int_eq(a, b);

  // hex with + prefix
  ck_assert_int_eq(s21_sscanf("+0xfaf", "%i", &a), sscanf("+0xfaf", "%i", &b));
  ck_assert_int_eq(a, b);
}
END_TEST

START_TEST(test_parse_ptr) {
  void *a = NULL, *b = NULL;
  ck_assert_int_eq(s21_sscanf("0x1234567890", "%p", &a),
                   sscanf("0x1234567890", "%p", &b));
  ck_assert_ptr_eq(a, b);

  ck_assert_int_eq(s21_sscanf("0xabc", "%p", &a), sscanf("0xabc", "%p", &b));
  ck_assert_ptr_eq(a, b);

  // no prefix
  ck_assert_int_eq(s21_sscanf("1234567890", "%p", &a),
                   sscanf("1234567890", "%p", &b));
  ck_assert_ptr_eq(a, b);

  // -
  ck_assert_int_eq(s21_sscanf("-1234567890", "%p", &a),
                   sscanf("-1234567890", "%p", &b));
  ck_assert_ptr_eq(a, b);
}
END_TEST

START_TEST(test_parse_string) {
  char buf1[100] = {0}, buf2[100] = {0};
  // %c
  ck_assert_int_eq(s21_sscanf("123", "%c", buf1), sscanf("123", "%c", buf2));
  ck_assert_int_eq(buf1[0], buf2[0]);

  // %s
  ck_assert_int_eq(s21_sscanf("1234567890", "%s", buf1),
                   sscanf("1234567890", "%s", buf2));
  ck_assert_str_eq(buf1, buf2);

  // %c with len
  // %c shouldnt add null terminator
  ck_assert_int_eq(s21_sscanf("qwertyuiop", "%9c", buf1),
                   sscanf("qwertyuiop", "%9c", buf2));
  ck_assert_str_eq(buf1, buf2);

  // %s with len
  ck_assert_int_eq(s21_sscanf("abcdefghk", "%5s", buf1),
                   sscanf("abcdefghk", "%5s", buf2));
  ck_assert_str_eq(buf1, buf2);

  // %c with len
  ck_assert_int_eq(s21_sscanf("qwe", "%2c", buf1), sscanf("qwe", "%2c", buf2));
  ck_assert_str_eq(buf1, buf2);

  // empty string
  ck_assert_int_eq(s21_sscanf("", "%s", buf1), sscanf("", "%s", buf2));
  ck_assert_str_eq(buf1, buf2);

  // two strings with space
  char buf3[100] = {0}, buf4[100] = {0};
  ck_assert_int_eq(s21_sscanf("123 456", "%s %s", buf1, buf3),
                   sscanf("123 456", "%s %s", buf2, buf4));
  ck_assert_str_eq(buf1, buf2);
  ck_assert_str_eq(buf3, buf4);
}
END_TEST

START_TEST(test_scan_n) {
  char buf1[100] = {0}, buf2[100] = {0};
  int a = 0, b = 0;
  ck_assert_int_eq(s21_sscanf("1234567890", "%5s%n", buf1, &a),
                   sscanf("1234567890", "%5s%n", buf2, &b));
  ck_assert_int_eq(a, b);

  // empty string
  ck_assert_int_eq(s21_sscanf("", "%s%n", buf1, &a),
                   sscanf("", "%s%n", buf2, &b));
  ck_assert_int_eq(a, b);

  int i = 0, j = 0;  // опять уб
  ck_assert_int_eq(s21_sscanf("123456", "%*3d%d%n", &i, &a),
                   sscanf("123456", "%*3d%d%n", &j, &b));
  ck_assert_int_eq(a, b);
}
END_TEST

long double ldabs(long double x) { return x < 0 ? -x : x; }

bool float_eq(float a, float b) { return fabs(a - b) < 0.00001; }
bool double_eq(double a, double b) { return fabs(a - b) < 0.00001; }
bool ldouble_eq(long double a, long double b) { return ldabs(a - b) < 0.00001; }

START_TEST(test_scan_float) {
  float a = 0, b = 0;
  double da = 0, db = 0;
  long double lda = 0, ldb = 0;
  ck_assert_int_eq(s21_sscanf("123.456", "%f", &a),
                   sscanf("123.456", "%f", &b));
  ck_assert(float_eq(a, b));

  ck_assert_int_eq(s21_sscanf("123.456", "%lf", &da),
                   sscanf("123.456", "%lf", &db));
  ck_assert(double_eq(da, db));

  ck_assert_int_eq(s21_sscanf("123.456", "%Lf", &lda),
                   sscanf("123.456", "%Lf", &ldb));
  ck_assert(ldouble_eq(lda, ldb));

  ck_assert_int_eq(s21_sscanf("123.456", "%hf", &a),
                   sscanf("123.456", "%f", &b));
  ck_assert(float_eq(a, b));

  // nan
  ck_assert_int_eq(s21_sscanf("nan", "%e", &a), sscanf("nan", "%e", &b));
  ck_assert(isnan(a));
  ck_assert(isnan(b));

  // inf +inf -inf
  ck_assert_int_eq(s21_sscanf("iNf", "%g", &a), sscanf("iNf", "%g", &b));
  ck_assert(isinf(a));
  ck_assert(isinf(b));

  ck_assert_int_eq(s21_sscanf("+inf", "%G", &a), sscanf("+inf", "%G", &b));
  ck_assert(isinf(a));
  ck_assert(isinf(b));

  ck_assert_int_eq(s21_sscanf("-inf", "%E", &a), sscanf("-inf", "%E", &b));
  ck_assert(isinf(a));
  ck_assert(isinf(b));

  // scientific
  ck_assert_int_eq(s21_sscanf("1.23e-4", "%e", &a),
                   sscanf("1.23e-4", "%e", &b));
  ck_assert(float_eq(a, b));

  ck_assert_int_eq(s21_sscanf("1.23e4", "%e", &a), sscanf("1.23e4", "%e", &b));
  ck_assert(float_eq(a, b));

  // empty string
  ck_assert_int_eq(s21_sscanf("", "%f", &a), sscanf("", "%f", &b));
  ck_assert(float_eq(a, b));

  // empty negative string
  ck_assert_int_eq(s21_sscanf("-", "%f", &a), sscanf("-", "%f", &b));
  ck_assert(float_eq(a, b));

  // with width
  ck_assert_int_eq(s21_sscanf("123.456", "%6f", &a),
                   sscanf("123.456", "%6f", &b));
  ck_assert(float_eq(a, b));

  // scientific with width
  ck_assert_int_eq(s21_sscanf("1.23E10", "%6E", &a),
                   sscanf("1.23E10", "%6E", &b));
  ck_assert(float_eq(a, b));

  // only .
  ck_assert_int_eq(s21_sscanf(".", "%f", &a), sscanf(".", "%f", &b));
  ck_assert(float_eq(a, b));

  // not digits
  ck_assert_int_eq(s21_sscanf("abc", "%f", &a), sscanf("abc", "%f", &b));
  ck_assert(float_eq(a, b));

  // dot at the end
  ck_assert_int_eq(s21_sscanf("123.", "%f", &a), sscanf("123.", "%f", &b));
  ck_assert(float_eq(a, b));

  // dot at the beginning
  ck_assert_int_eq(s21_sscanf(".123", "%f", &a), sscanf(".123", "%f", &b));
  ck_assert(float_eq(a, b));

  // letters after dot
  ck_assert_int_eq(s21_sscanf("123.abc", "%f", &a),
                   sscanf("123.abc", "%f", &b));
  ck_assert(float_eq(a, b));

  // no dot
  ck_assert_int_eq(s21_sscanf("222", "%f", &a), sscanf("222", "%f", &b));
  ck_assert(float_eq(a, b));

  // letters
  ck_assert_int_eq(s21_sscanf("abc", "%f", &a), sscanf("abc", "%f", &b));
  ck_assert(float_eq(a, b));
}
END_TEST

int main() {
  int err = 0;
  Suite *s = suite_create("main");
  SRunner *runner = srunner_create(s);

  // strcspn
  TCase *s21_strcspn = tcase_create("s21_strcspn");
  suite_add_tcase(s, s21_strcspn);
  tcase_add_test(s21_strcspn, test_s21_strcspn);

  // strstr
  TCase *s21_strstr = tcase_create("s21_strstr");
  suite_add_tcase(s, s21_strstr);
  tcase_add_test(s21_strstr, test_s21_strstr);

  // strtok
  TCase *s21_strtok = tcase_create("s21_strtok");
  suite_add_tcase(s, s21_strtok);
  tcase_add_test(s21_strtok, test_s21_strtok);
  // memchr
  TCase *s21_memchr = tcase_create("s21_memchr");
  suite_add_tcase(s, s21_memchr);
  tcase_add_test(s21_memchr, test_s21_memchr);

  // // memcmp
  TCase *s21_memcmp = tcase_create("s21_memcmp");
  suite_add_tcase(s, s21_memcmp);
  tcase_add_test(s21_memcmp, test_s21_memcmp);

  // // memcpy
  TCase *s21_memcpy = tcase_create("s21_memcpy");
  suite_add_tcase(s, s21_memcpy);
  tcase_add_test(s21_memcpy, test_s21_memcpy);

  // strlen
  TCase *s21_strlen = tcase_create("s21_strlen");
  suite_add_tcase(s, s21_strlen);
  tcase_add_test(s21_strlen, test_s21_strlen);

  // sprintf_empty_format
  TCase *s21_sprintf_empty = tcase_create("s21_sprintf_empty");
  suite_add_tcase(s, s21_sprintf_empty);
  tcase_add_test(s21_sprintf_empty, test_sprintf_empty);

  // sprintf_percent
  TCase *s21_sprintf_percent = tcase_create("s21_sprintf_percent");
  suite_add_tcase(s, s21_sprintf_percent);
  tcase_add_test(s21_sprintf_percent, test_sprintf_percent);

  // sprintf_d
  TCase *s21_sprintf_d = tcase_create("s21_sprintf_d");
  suite_add_tcase(s, s21_sprintf_d);
  tcase_add_test(s21_sprintf_d, test_s21_sprintf_d);

  // sprintf_u
  TCase *s21_sprintf_u = tcase_create("s21_sprintf_u");
  suite_add_tcase(s, s21_sprintf_u);
  tcase_add_test(s21_sprintf_u, test_s21_sprintf_u);

  // sprintf_c
  TCase *s21_sprintf_c = tcase_create("s21_sprintf_c");
  suite_add_tcase(s, s21_sprintf_c);
  tcase_add_test(s21_sprintf_c, test_s21_sprintf_c);

  // sprintf_s
  TCase *s21_sprintf_s = tcase_create("s21_sprintf_s");
  suite_add_tcase(s, s21_sprintf_s);
  tcase_add_test(s21_sprintf_s, test_s21_sprintf_s);

  // sprintf_f
  TCase *s21_sprintf_f = tcase_create("s21_sprintf_f");
  suite_add_tcase(s, s21_sprintf_f);
  tcase_add_test(s21_sprintf_f, test_s21_sprintf_f);

  // sprintf_sev
  TCase *s21_sprintf_sev = tcase_create("s21_sprintf_sev");
  suite_add_tcase(s, s21_sprintf_sev);
  tcase_add_test(s21_sprintf_sev, test_s21_sprintf_sev);

  TCase *s21_strpbrk = tcase_create("s21_strpbrk");
  suite_add_tcase(s, s21_strpbrk);
  tcase_add_test(s21_strpbrk, test_s21_strpbrk);

  TCase *s21_strerror_1 = tcase_create("s21_strerror_1");
  suite_add_tcase(s, s21_strerror_1);
  tcase_add_test(s21_strerror_1, test_s21_strerror_1);

  TCase *s21_memset = tcase_create("s21_memset");
  suite_add_tcase(s, s21_memset);
  tcase_add_test(s21_memset, test_s21_memset);

  TCase *s21_strncat = tcase_create("s21_strncat");
  suite_add_tcase(s, s21_strncat);
  tcase_add_test(s21_strncat, test_s21_strncat);

  TCase *s21_strncmp = tcase_create("s21_strncmp");
  suite_add_tcase(s, s21_strncmp);
  tcase_add_test(s21_strncmp, test_s21_strncmp);

  TCase *s21_strncpy = tcase_create("s21_strncpy");
  suite_add_tcase(s, s21_strncpy);
  tcase_add_test(s21_strncpy, test_s21_strncpy);

  TCase *s21_strrchr = tcase_create("s21_strrchr");
  suite_add_tcase(s, s21_strrchr);
  tcase_add_test(s21_strrchr, test_s21_strrchr);

  TCase *s21_to_lower = tcase_create("s21_to_lower");
  suite_add_tcase(s, s21_to_lower);
  tcase_add_test(s21_to_lower, test_s21_to_lower);

  TCase *s21_to_upper = tcase_create("s21_to_upper");
  suite_add_tcase(s, s21_to_upper);
  tcase_add_test(s21_to_upper, test_s21_to_upper);

  TCase *s21_insert = tcase_create("s21_insert");
  suite_add_tcase(s, s21_insert);
  tcase_add_test(s21_insert, test_s21_insert);

  TCase *s21_trim = tcase_create("s21_trim");
  suite_add_tcase(s, s21_trim);
  tcase_add_test(s21_trim, test_s21_trim);

  TCase *s21_sscanf = tcase_create("s21_sscanf");
  suite_add_tcase(s, s21_sscanf);
  tcase_add_test(s21_sscanf, test_s21_sscanf);

  TCase *parse_int = tcase_create("parse_int");
  suite_add_tcase(s, parse_int);
  tcase_add_test(parse_int, test_parse_int);

  TCase *parse_uint = tcase_create("parse_uint");
  suite_add_tcase(s, parse_uint);
  tcase_add_test(parse_uint, test_parse_uint);

  TCase *parse_hex = tcase_create("parse_hex");
  suite_add_tcase(s, parse_hex);
  tcase_add_test(parse_hex, test_parse_hex);

  TCase *parse_oct = tcase_create("parse_oct");
  suite_add_tcase(s, parse_oct);
  tcase_add_test(parse_oct, test_parse_oct);

  TCase *parse_i_uint = tcase_create("parse_i_uint");
  suite_add_tcase(s, parse_i_uint);
  tcase_add_test(parse_i_uint, test_parse_i_uint);

  TCase *parse_ptr = tcase_create("parse_ptr");
  suite_add_tcase(s, parse_ptr);
  tcase_add_test(parse_ptr, test_parse_ptr);

  TCase *parse_string = tcase_create("parse_string");
  suite_add_tcase(s, parse_string);
  tcase_add_test(parse_string, test_parse_string);

  TCase *scan_n = tcase_create("scan_n");
  suite_add_tcase(s, scan_n);
  tcase_add_test(scan_n, test_scan_n);

  TCase *scan_float = tcase_create("scan_float");
  suite_add_tcase(s, scan_float);
  tcase_add_test(scan_float, test_scan_float);

  srunner_run_all(runner, CK_NORMAL);
  err = srunner_ntests_failed(runner);
  srunner_free(runner);
  return err != 0;
}