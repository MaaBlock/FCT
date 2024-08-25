#ifdef _WIN32
template <typename T>
class LockFreeQueue : public RefCounted {
public:
    LockFreeQueue(size_t capacity)
        : m_capacity(capacity), m_buffer(new T[capacity]), m_head(m_buffer), m_tail(m_buffer) {}
    ~LockFreeQueue() {
        delete[] m_buffer;
    }
    bool enqueue(T value) {
        T* nextTail = m_tail.value() + 1;
        if (nextTail == m_buffer + m_capacity) {
            nextTail = m_buffer;
        }
        if (nextTail == m_head.value()) {
            return false;
        }
        *m_tail.value() = value;
        m_tail = nextTail;
        return true;
    }
    bool dequeue(T& result) {
        if (m_head.value() == m_tail.value()) {
            return false;
        }
        result = *m_head.value();
        m_head = m_head.value() + 1;
        if (m_head.value() == m_buffer + m_capacity) {
            m_head = m_buffer;
        }
        return true;
    }
    bool peek(T& result) const {
        if (m_head.value() == m_tail.value()) {
            return false;
        }
        result = *m_head.value();
        return true;
    }
private:
    size_t m_capacity;
    T* m_buffer;
    Atomic<T*> m_head;
    Atomic<T*> m_tail;
};
#endif