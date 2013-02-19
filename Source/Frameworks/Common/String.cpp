#include "String.h"

#include <stdarg.h>
#include <stdio.h>


String::String()
{
	data = NULL;
	length = 0;
	allocate(255);
	updateLength();
}

String::String(int size)
{
	data = NULL;
	length = 0;
	allocate(size);
	updateLength();
}

String::String(const char *ss)
{
	data = NULL;
	length = 0;
	allocate(strlen(ss));
	strcpy(data, ss);
	updateLength();
}


String::String(const String& ss)
{
	data = NULL;
	length = 0;
	allocate(ss.getLength());
	strcpy(data, ss.c_str());
	updateLength();
}


String::~String()
{
	delete [] data;
}


String String::printf(const char *format, ...)
{
	char data[256] = "";
	va_list ap;
	va_start(ap, format);
		vsprintf(data, format, ap);
	va_end(ap);
	return String(data);
}

//
//memory
//

void String::allocate(int size)
{
	if (getLength() < size)
	{
		delete [] data;
	}
	data = new char [size + 1];
	data[0] = '\0';
	length = 0;
}

void String::reallocate(int size)
{
	if (getLength() < size)
	{
		char* new_data = new char [size + 1];
		int new_len = (size < length) ? size : length;
		for (int i = 0; i < new_len; i++)
		{
			new_data[i] = data[i];
		}
		new_data[new_len] = '\0';
		delete [] data;
		data = new_data;
		length = new_len;
	}
}


void String::append(const char c)
{
	reallocate(getLength() + 1);
	data[getLength()] = c;
	data[getLength() + 1] = '\0';
	updateLength();
}

void String::append(const char* ss)
{
	int n = strlen(ss);
	reallocate(getLength() + n);
	for (int i = 0; i < n; i++)
	{
		data[getLength() + i] = ss[i];
	}
	data[getLength() + n] = '\0';
	updateLength();
}

void String::clear()
{
	data[0] = '\0';
	length = 0;
}

void String::erase(int size)
{
	if (size > getLength())
		return;
	data[getLength() - size] = '\0';
	updateLength();
}


//
// set
//

String& String::operator = (const String& str)
{
	reallocate(str.getLength());
	strcpy(data, str.data);
	updateLength();
	return *this;
}


//
//concatenation
//

String& String::operator += (const char c)
{
	append(c);
	return *this;
}

String& String::operator += (const char* ss)
{
	append(ss);
	return *this;
}

String& String::operator += (const int i)
{
	char ss[16];
	sprintf(ss, "%d", i);
	append(ss);
	return *this;
}

String& String::operator += (const float f)
{
	char ss[64];
	sprintf(ss, "%f", f);
	append(ss);
	return *this;
}

String& String::operator += (const String& str)
{
	append(str.c_str());
	return *this;
}

String String::operator + (const String& str)
{
    String s(*this);
    s += str;
    return s;
}

//
//comperation
//

bool String::operator == (const String& str) const
{
	return (strcmp(data, str.data) == 0);
}

bool String::operator == (const char* ss) const
{
	return (strcmp(data, ss) == 0);
}


bool String::operator != (const String& str) const
{
	return (strcmp(data, str.data) != 0);
}

bool String::operator != (const char* ss) const
{
	return (strcmp(data, ss) != 0);
}


//
//conversion
//

String String::getSubString(int start, int len) const
{
	if (start >= getLength())
		return String();
	if (len <= 0)
		len = getLength() - start;
	String str(len);
	for (int i = start; i < start + len; i++)
	{
		str += data[i];
	}
	return str;
}

// cont_sep - da li se separatori ponavljaju
String String::getWord(int index, char sep, bool cont_sep) const
{
	String word;
	bool wait_word = true;
	int word_i = cont_sep ? -1 : 0;
	const char* c = data;
	while (*c)
	{
		if (*c == sep)
		{
            if (!cont_sep)
                word_i++;
			if (word_i == index)
			{
                break;
			}
			wait_word = true;
		}
		else
		{
			if (wait_word && cont_sep)
			{
				word_i++;
				wait_word = false;
			}
			if (word_i == index)
			{
				word += *c;
			}
		}
		c++;
	}
	return word;
}


int String::getWordCount() const
{
	bool wait_space = false;
	int word_i = 0;
	const char* c = data;
	while (*c)
	{
		if (*c == 32)
		{
			if (wait_space)
			{
				word_i++;
				wait_space = false;
			}
		}
		else
		{
			if (wait_space == false)
			{
				wait_space = true;
			}
		}
	}
	return word_i;
}


int String::findFirst(char c) const
{
	for (int i = 0; i < length; i++)
	{
		if (data[i] == c)
			return i;
	}
	return -1;
}


int String::findLast(char c) const
{
	for (int i = length - 1; i >= 0; i--)
	{
		if (data[i] == c)
			return i;
	}
	return -1;
}

void String::trim(char st)
{
    char* lp = data;
    while (*lp && *lp == st)
        lp++;
    char* rp = &data[length+1];
    while (rp != lp && *rp == st)
        rp--;
    char* oc = data;
    char* pc = lp;
    while (pc != rp)
    {
        *oc = *pc;
        pc++;
        oc++;
    }
    oc = 0;
    updateLength();
}




