#ifndef __OPENGLSAMPLE_FILELOADER_H__
#define __OPENGLSAMPLE_FILELOADER_H__

#include<stdio.h>

class FileLoader
{
public:
	FileLoader();
	FileLoader(const char* szFileName);
	~FileLoader();

	bool Load(const char* szFileName);
	bool IsLoaded() const;

	int				GetLength() const;
	const char*		GetData() const;

private:
	void Release();

private:
	FILE	*m_File;
	char	*m_pBuffer;
	int		m_iBufferSize;
	bool	m_bLoaded;
};


#endif