/*
	by Ilija
*/


#include "FileObject.h"



FileObject::FileObject(const String& file_name, int mode)
{
	m_File = fopen(file_name.c_str(), (mode == FO_WRITE) ? "w" : "r");
	m_FileName = file_name;
}


FileObject::~FileObject()
{
	if (m_File)
		fclose(m_File);
}


/******************************************
USAGE:
	String line;
	FileObject f("zzz.txt", FO_READ);
	while (f.readLine(line))
	{
		...
	}
*******************************************/
bool FileObject::readLine(String& line)
{
	if (!m_File)
		return false;

	if (feof(m_File))
		return false;

	line = "";

	while (!feof(m_File))
	{
		char c = fgetc(m_File);
		if (c == '\n')
			return true;
		else if (c != '\r')
			line += c;
	}

	return true;
}

long FileObject::read(void *out, long length)
{
    if (m_File)
        return fread(out, 1, length, m_File);
    return 0;
}

long FileObject::read(void *out, long start, long length)
{
    if (m_File)
    {
        fseek(m_File, start, SEEK_SET);
        return fread(out, 1, length, m_File);
    }
    return 0;
}

void FileObject::seek(long pos, int mode)
{
    if (m_File)
        fseek(m_File, pos, mode);
}

long FileObject::getSize() const
{
    if (!m_File)
        return 0;
    long cur_pos = ftell(m_File);
    fseek(m_File, 0, SEEK_END);
    long val = ftell(m_File);
    fseek(m_File, cur_pos, SEEK_SET);
    return val;
}













