#include"FileLoader.h"

FileLoader::FileLoader()
:m_File(0)
, m_pBuffer(0)
, m_iBufferSize(0)
{

}

FileLoader::FileLoader(const char* szFileName)
:m_File(0)
, m_pBuffer(0)
, m_iBufferSize(0)
{
	Load(szFileName);
}

FileLoader::~FileLoader()
{
	Release();
}

void FileLoader::Release()
{
	if (m_pBuffer)
	{
		delete[] m_pBuffer;
		m_pBuffer = 0;
	}

	m_iBufferSize = 0;
	m_bLoaded = false;
}

bool FileLoader::Load(const char* szFileName)
{
	Release();

	m_File = fopen(szFileName, "rb");
	if (0 == m_File)
		return false;

	fseek(m_File, 0, SEEK_END);
	m_iBufferSize = ftell(m_File);
	fseek(m_File, 0, SEEK_SET);

	m_pBuffer = new char[m_iBufferSize + 16];
	if (0 == m_pBuffer)
	{
		fclose(m_File);
		return false;
	}

	fread(m_pBuffer, 1, m_iBufferSize, m_File);
	m_pBuffer[m_iBufferSize] = '\0';
	m_pBuffer[m_iBufferSize + 1] = '\0';

	fclose(m_File);

	m_bLoaded = true;
	
	return true;
}

bool FileLoader::IsLoaded() const
{
	return m_bLoaded;
}

int FileLoader::GetLength() const
{
	return m_iBufferSize;
}

const char* FileLoader::GetData() const
{
	return m_pBuffer;
}