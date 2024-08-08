class Win32_Mutex : public Mutex {
public:
	Win32_Mutex() {

	}
	~Win32_Mutex() {
		destory();
	}
	void create() {
		if (m_mutex) {
			destory();
		}
		m_mutex = CreateMutexA(NULL, FALSE, NULL);
	}
	void destory() {
		if (m_mutex) {
			CloseHandle(m_mutex);
			m_mutex = NULL;
		}
	}
private:
	HANDLE m_mutex;
};