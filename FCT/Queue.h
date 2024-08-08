

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
