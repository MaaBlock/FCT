#include "hander.h"

namespace FCT {
    class Renderer : public RefCounted
    {
    public:
        static void RendererThread(void* arg);
        Renderer();
        ~Renderer();
        Context* getContext() { return m_context; }
        void addCommand(void(*command)(Context*));

    private:
        Context* m_context;
        LockFreeQueue<void(*)(Context*)> commandQueue;
        Atomic<bool> running;
        Thread* renderThread;
    };
    void Renderer::RendererThread(void* arg)
    {
        Renderer* renderer = static_cast<Renderer*>(arg);
        while (renderer->running.value()) {
            void(*command)(Context*);
            if (renderer->commandQueue.dequeue(command)) {
                command(renderer->m_context);
            }
        }
    }
    Renderer::Renderer() : m_context(nullptr), commandQueue(1024), running(true)
    {
        renderThread = new Thread(RendererThread, this);
    }
    Renderer::~Renderer()
    {
        running = false;
        renderThread->join();
        delete renderThread;
    }
    void Renderer::addCommand(void(*command)(Context*))
    {
        while (!commandQueue.enqueue(command)) {
			Sleep(1); 
        }
    }
}