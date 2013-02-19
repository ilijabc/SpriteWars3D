#ifndef FILEOBJECT_H
#define FILEOBJECT_H


#include "String.h"

#include <stdio.h>


const int FO_READ = 0;
const int FO_WRITE = 1;


class FileObject
{
public:
	FileObject(const String& file_name, int mode);
	virtual ~FileObject();

	bool readLine(String& line);

    long read(void *out, long length);
    long read(void *out, long start, long length);
	void seek(long pos, int mode);
    long getSize() const;

	inline bool isOpened() const { return m_File != NULL; }
    inline const String& getFileName() const { return m_FileName; }

    FILE* getFP() { return m_File; }

private:
	FILE* m_File;
	String m_FileName;
};



#endif // FILEOBJECT_H
