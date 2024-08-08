#include "hander.h"
namespace FCT {
	void Win32_File::open(const char* filename, const char* str)
	{
		DWORD acess = NULL;
		for (const char* p = str; *p != '\0'; p++) {
			if (*p == 'w') {
				acess = GENERIC_WRITE;
				continue;
			}
			if (*p == 'r') {
				acess = GENERIC_READ;
				continue;
			}
		}
		m_file = CreateFileA(filename, acess, FILE_SHARE_READ,
			NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		if (m_file) {
			DWORD fileSize = GetFileSize(m_file, NULL);
			if (fileSize > 0) {
				void* buffer = malloc(fileSize);
				DWORD readSize;
				ReadFile(m_file, buffer, fileSize, &readSize, NULL);
				if (readSize == fileSize) {
					m_data = static_cast<char*>(buffer);
					m_size = fileSize;
				}
				else {
					free(buffer);
				}
			}
			else {
				m_data = nullptr;
				m_size = 0;
			}
			return;
		}
		std::cout << "not open the file,检查是否存在该文件." << std::endl;
		return;
	}

	void Win32_File::close()
	{
	}

	bool Win32_File::isOpen()
	{
		return m_file;
	}

	const char* Win32_File::getFileStream()
	{
		return m_data;
	}

	File* Win32_CreateFile()
	{
		return FCT_NEW( Win32_File);
	}
}

