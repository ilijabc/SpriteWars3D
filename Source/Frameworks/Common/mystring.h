#ifndef MYSTRING_H
#define MYSTRING_H

#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>


char *str_skipws(char *);
char *str_skipnws(char *);
char *str_getword(char *src, char *dst);
char *str_getword(char *src, char *dst, char sep);
char *str_getword2(char *src, char *dst, char sep1, char sep2);

void _Sbegin(const char *);
void _Send();
int _S(const char *);

inline int str_eq(const char *s1, const char *s2) { return strcmp(s1, s2) == 0; }
inline char *str_nextwrd(char *s) { return str_skipws(str_skipnws(s)); }
inline char *str_getline(char *src, char *dst) { return str_getword(src, dst, '\n'); }

void str_filename(char *s_out, const char* s_in, int n);
void str_filepath(char *s_out, const char* s_in, int n);

char *str_n2rn(char* s_out, const char* s_in);
void str_tolower(char *s_out, const char* s_in);
void str_toupper(char *s_out, const char* s_in);

const char *str_copytill(char *s_out, const char *s_in, const char t_chr);

char* str_readfile(const char *filename);

int str_cmplist(const char *str, const char **str_list, int list_size = 0);

#endif // MYSTRING_H
