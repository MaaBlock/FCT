template <typename T>
class Stack : public RefCounted {
public:
	Stack(const size_t max) {
		m_max = max;
	}
	void create() {
		m_data = new T[m_max];
		m_top = m_data;
	}
	void push(T data) {
		if (m_top >= m_data + m_max) {
			//ToDo:error
			std::cout << "Stack overflow" << std::endl;
		}
		*m_top++ = data;
	}
	T pull() {
		if (m_top <= m_data) {
			//ToDo: error
			std::cout << "Stack underflow" << std::endl;
		}
		return *--m_top;
	}
	~Stack() {
		delete[] m_data;
	}
	size_t size() {
		return m_top - m_data;
	}
private:
	const size_t m_max;
	T* m_data;
	T* m_top;
};