class Win32_File : public File {
public:
	void open(const char* filename, const char* str);
	void close();
	bool isOpen();
	const char* getFileStream();
private:
	HANDLE m_file;
	char* m_data;
	size_t m_size;
};
File* Win32_CreateFile();