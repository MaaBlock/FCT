#ifdef _WIN32

class Thread {
public:
    Thread(void(*function)(void*), void* arg) {
        m_handle = CreateThread(
            NULL,                   // default security attributes
            0,                      // use default stack size  
            ThreadFunction,         // thread function name
            new ThreadData{ function, arg }, // argument to thread function 
            0,                      // use default creation flags 
            &m_threadId);           // returns the thread identifier 
    }

    ~Thread() {
        if (m_handle) {
            CloseHandle(m_handle);
        }
    }

    void join() {
        if (m_handle) {
            WaitForSingleObject(m_handle, INFINITE);
        }
    }

private:
    struct ThreadData {
        void(*function)(void*);
        void* arg;
    };

    static DWORD WINAPI ThreadFunction(LPVOID lpParam) {
        ThreadData* data = static_cast<ThreadData*>(lpParam);
        data->function(data->arg);
        delete data;
        return 0;
    }

    HANDLE m_handle;
    DWORD m_threadId;
};

#endif