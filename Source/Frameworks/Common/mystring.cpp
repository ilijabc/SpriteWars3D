#include "mystring.h"

char *str_skipws(char *src)
{
    char *pc;
    for (pc = src; *pc && *pc <= 32; ++pc);
    return pc;
}

char *str_skipnws(char *src)
{
    char *pc;
    for (pc = src; *pc > 32; ++pc);
    return pc;
}

char *str_getword(char *src, char *dst)
{
    char *pc;
    for (pc = src; *pc <= 32; ++pc)
        if (!*pc) return NULL;
    char *oc;
    for (oc = dst; *pc > 32; ++pc, ++oc)
        *oc = *pc;
    *oc = 0;
    return pc;
}

char *str_getword(char *src, char *dst, char sep)
{
    char *pc = src;
    if (*pc == sep)
        ++pc;
    if (!*pc)
        return NULL;
    char *oc;
    for (oc = dst; *pc && *pc != sep; ++pc, ++oc)
        *oc = *pc;
    *oc = 0;
    return pc;
}

char *str_getword2(char *src, char *dst, char sep1, char sep2)
{
    char *pc;
    for (pc = src; *pc != sep1; ++pc)
    {
        if (!*pc)
            return NULL;
    }
    ++pc;
    char *oc;
    for (oc = dst; *pc && *pc != sep2; ++pc, ++oc)
        *oc = *pc;
    *oc = 0;
    return pc;
}


static const char* glob_S = NULL;

void _Sbegin(const char *s)
{
    glob_S = s;
}

void _Send()
{
    glob_S = NULL;
}

int _S(const char *s)
{
    if (!glob_S) return 0;
    return strcmp(s, glob_S) == 0;
}


void str_filename(char *s_out, const char* s_in, int n)
{
    const char *s1 = strrchr(s_in, '\\');
    const char *s2 = strrchr(s_in, '/');
    const char *ss = (s1 > s2) ? s1 : s2;
    strncpy(s_out, ss+1, n);
}

void str_filepath(char *s_out, const char* s_in, int n)
{
    const char *s1 = strrchr(s_in, '\\');
    const char *s2 = strrchr(s_in, '/');
    const char *ss = (s1 > s2) ? s1 : s2;
    if (!ss) return;
    int nn = ss - s_in;
    strncpy(s_out, s_in, (nn < n) ? nn : n);
    s_out[nn] = 0;
}

void str_relpath(char *s_out, const char* s_in, int n)
{
    const char *s1 = strrchr(s_in, '\\');
    const char *s2 = strrchr(s_in, '/');
    const char *ss = (s1 > s2) ? s1 : s2;
    if (!ss) return;
    int nn = ss - s_in;
    strncpy(s_out, s_in, (nn < n) ? nn : n);
    s_out[nn] = 0;
}


char *str_n2rn(char* s_out, const char* s_in)
{
    //analyze
    const char *pc;
    int n_cnt = 0;
    for (pc = s_in; *pc; ++pc)
    {
        if (*pc == '\n')
            ++n_cnt;
    }
    //allocate
    int nn = strlen(s_in);
    //char *s_out = malloc(nn + n_cnt + 1);
    //replace
    int i;
    char *cc = s_out;
    for (i = 0; i < nn; ++i)
    {
        if (s_in[i] == '\n')
        {
            *cc = '\r';
            ++cc;
            *cc = '\n';
            ++cc;
        }
        else
        {
            *cc = s_in[i];
            ++cc;
        }
    }
    *cc = 0;
    return s_out;
}

void str_tolower(char* s_out, const char* s_in)
{
    const char *pc;
    char *cc;
    for (pc = s_in, cc = s_out; *pc; ++pc, ++cc)
    {
        *cc = tolower(*pc);
    }
}

void str_toupper(char* s_out, const char* s_in)
{
    const char *pc;
    char *cc;
    for (pc = s_in, cc = s_out; *pc; ++pc, ++cc)
    {
        *cc = tolower(*pc);
    }
}

const char *str_copytill(char *s_out, const char *s_in, const char t_chr)
{
    const char *psrc;
    char *pdst;
    for (psrc = s_in, pdst = s_out; *psrc && *psrc != t_chr; ++psrc, ++pdst)
        *pdst = *psrc;
    *pdst = 0;
    return psrc;
}

char* str_readfile(const char *filename)
{
	FILE *fp;
	char *content = NULL;
	int count=0;
	if (filename != NULL)
    {
		fp = fopen(filename,"rt");
		if (fp != NULL)
		{
			fseek(fp, 0, SEEK_END);
			count = ftell(fp);
			rewind(fp);
			if (count > 0)
			{
				content = (char*)malloc(sizeof(char) * (count+1));
				count = fread(content, sizeof(char), count, fp);
				content[count] = '\0';
			}
			fclose(fp);
		}
	}
	return content;
}

int str_cmplist(const char *str, const char **str_list, int list_size)
{
    int i = 0;
    for (const char *sp = str_list[0]; sp; sp = str_list[++i])
    {
        if (strcmp(str, sp)==0)
            return i;
        if (list_size > 0 && i == list_size - 1)
            break;
    }
    return -1;
}

