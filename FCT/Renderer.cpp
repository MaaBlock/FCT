#include "hander.h"

namespace FCT {
    void Renderer::RendererThread(void* arg)
    {
        Renderer* renderer = static_cast<Renderer*>(arg);
        while (renderer->m_running.value()) {
            Command command;
            if (renderer->m_commandQueue.dequeue(command)) {
                command.func(renderer->m_context, command.arg);
            }
            if (renderer->m_flushRequested.value()) {
                renderer->m_flushMutex->lock();
                renderer->m_flushRequested = false;
                renderer->m_flushCondition->notifyAll();
                renderer->m_flushMutex->unlock();
            }
        }
    }

    Renderer::Renderer() : m_context(nullptr), m_commandQueue(1024), m_running(true), m_flushRequested(false)
    {
        m_flushMutex = CreateMutex();
        m_flushMutex->create();
        m_flushCondition = CreateConditionVariable();
        m_renderThread = new Thread(RendererThread, this);
    }

    Renderer::~Renderer()
    {
        m_running = false;
        m_renderThread->join();
        delete m_renderThread;
        delete m_flushMutex;
        delete m_flushCondition;
    }

    void Renderer::addCommand(void(*command)(Context*, void*), void* arg)
    {
        Command cmd = { command, arg };
        while (!m_commandQueue.enqueue(cmd)) {
            Sleep(1);
        }
    }

    void Renderer::flush()
    {
        m_flushMutex->lock();
        m_flushRequested = true;
        while (m_flushRequested.value()) {
            m_flushCondition->wait(m_flushMutex);
        }
        m_flushMutex->unlock();
    }
}