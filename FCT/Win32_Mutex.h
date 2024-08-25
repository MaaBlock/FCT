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
	void lock() {
		WaitForSingleObject(m_mutex, INFINITE);
	}
	void unlock() {
		ReleaseMutex(m_mutex);
	}
	void destory() {
		if (m_mutex) {
			CloseHandle(m_mutex);
			m_mutex = NULL;
		}
	}
	HANDLE getHandle() {
		return m_mutex;
	}
private:
	HANDLE m_mutex;
};
inline Mutex* Win32_CreateMutex() {
	return FCT_NEW(Win32_Mutex);
}