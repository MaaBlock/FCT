class ConditionVariable : public RefCounted {
public:
    virtual ~ConditionVariable() {}
    virtual void wait(Mutex* mutex) = 0;
    virtual void notifyOne() = 0;
    virtual void notifyAll() = 0;
};
#ifdef _WIN32
#define CreateConditionVariable() Win32_CreateConditionVariable()
#elif defined(__ANDROID__)
#define CreateConditionVariable() Android_CreateConditionVariable()
#else
#error "Unsupported platform"
#endif