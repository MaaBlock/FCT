

template<typename T>
class Queue : public RefCounted {
public:
	Queue() {}
	Queue(int nSize) {
		m_size = nSize;
		m_buffer = FCT_NEWS(T,nSize);
		m_head = m_buffer;
		m_tail = m_buffer;
	}
	~Queue() {
		FCT_DELETES (m_buffer);
	}
	void push(T data) {
		*m_tail = data;
		m_tail++;
		if (m_tail == m_buffer + m_size) {
			m_tail = m_buffer;
		}
	}
	T pop() {
		T data = *m_head;
		m_head++;
		if (m_head == m_buffer + m_size) {
			m_head = m_buffer;
		}
		return data;
	}
private:
	T* m_head;
	T* m_tail;
	T* m_buffer;
	int m_size;
}; 

template<typename T,typename Lock>
class Queue : public RefCounted {
public:	
	Queue() {}
	Queue(int nSize, Lock& lock) : m_lock(lock), m_capacity(nSize) {
		m_buffer = FCT_NEWS(T, nSize); 
		m_head = m_buffer;
		m_tail = m_buffer;
	}
	~Queue() {
		FCT_DELETES(m_buffer);
	}
	void push(T data) {
		m_lock.lock();
		if (isFull()) {
			m_lock.unlock();
			throw std::runtime_error("Queue is full");
		}
		*m_tail = data;
		m_tail++;
		if (m_tail == m_buffer + m_capacity) {
			m_tail = m_buffer;
		}
		m_lock.unlock();
	}
	T pop() {
		m_lock.lock();
		if (isEmpty()) {
			m_lock.unlock();
			throw std::runtime_error("Queue is empty");
		}
		T data = *m_head;
		m_head++;
		if (m_head == m_buffer + m_capacity) {
			m_head = m_buffer;
		}
		m_lock.unlock();
		return data;
	}
	bool isEmpty() {
		return m_head == m_tail;
	}
	bool isFull() {
		return (m_tail + 1) % m_capacity == m_head; 
	}
private:
	Lock m_lock;
	T* m_buffer;
	T* m_head;
	T* m_tail;
	const int m_capacity;
};
