class Win32_ConditionVariable : public ConditionVariable {
public:
    Win32_ConditionVariable() {
        m_event = CreateEvent(NULL, TRUE, FALSE, NULL);
    }
    ~Win32_ConditionVariable() {
        CloseHandle(m_event);
    }
    void wait(Mutex* mutex) {
        Win32_Mutex* win32Mutex = static_cast<Win32_Mutex*>(mutex);
        win32Mutex->unlock();
        WaitForSingleObject(m_event, INFINITE);
        win32Mutex->lock();
    }
    void notifyOne() {
        SetEvent(m_event);
    }
    void notifyAll() {
        SetEvent(m_event);
    }
private:
    HANDLE m_event;
};

inline ConditionVariable* Win32_CreateConditionVariable() {
    return FCT_NEW(Win32_ConditionVariable);
}