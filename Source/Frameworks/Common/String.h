#ifndef STRING_H
#define STRING_H


#include <string.h>
#include <stdlib.h>


class String
{
	public:
		String();
		String(int size);
		String(const char *ss);
		String(const String& str);
		virtual ~String();

		static String printf(const char *format, ...);

		//memory
		void allocate(int size);
		void reallocate(int size);

		void append(const char c);
		void append(const char* ss);
		void clear();
		void erase(int size);

		String& operator --()				{ erase(1); return *this; }
		String& operator -=(const int i)	{ erase(i); return *this; }

		//set
		String& operator = (const String& str);

		//concatenation
		String& operator += (const char c);
		String& operator += (const char* ss);
		String& operator += (const int i);
		String& operator += (const float f);
		String& operator += (const String& str);
        String operator + (const String& str);

		//comperation
		bool operator == (const String& str) const;
		bool operator == (const char* ss) const;

		bool operator != (const String& str) const;
		bool operator != (const char* ss) const;

		//geters
		inline char* c_str() const { return data; }
		inline int getLength() const { return length; }

		char operator [] (int index) const { return data[index]; }

		//conversion
		String getSubString(int start, int len = 0) const;
		String getWord(int index, char sep = ' ', bool cont_sep = true) const;
		int getWordCount() const;

		int findFirst(char c) const;
		int findLast(char c) const;

		inline char getChar(int index) const { return data[index]; }
		inline void setChar(int index, char c) { data[index] = c; }
		inline int getIntValue() const { return atoi(data); }
		inline float getFloatValue() const { return atof(data); }

        void trim(char st = ' ');

	protected:

		inline void updateLength() { length = strlen(data); }

		char*	data;
		int		length;
};

#endif // STRING_H
