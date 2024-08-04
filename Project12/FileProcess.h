class File : public RefCounted {
public:
	virtual ~File() {}
	virtual void open(const char* filename, const char* str) = 0;
	virtual void close() = 0;
	virtual bool isOpen() = 0;
	virtual const char* getFileStream() = 0;
};
#undef CreateFile
#ifdef WIN32
#define CreateFile Win32_CreateFile
#endif // WIN32