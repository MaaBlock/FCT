
class Renderer : public RefCounted
{
public:
    static void RendererThread(void* arg);
    Renderer();
    ~Renderer();
    Context* getContext() { return m_context; }
    void addCommand(void(*command)(Context*, void*), void* arg);
    void flush();
private:
    Context* m_context;
    struct Command {
        void(*func)(Context*, void*);
        void* arg;
    };
    LockFreeQueue<Command> m_commandQueue;
    Atomic<bool> m_running;
    Thread* m_renderThread;
    Mutex* m_flushMutex;
    ConditionVariable* m_flushCondition;
    Atomic<bool> m_flushRequested;
};
