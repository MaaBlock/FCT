
template <typename T>
class Node : public RefCounted {
public:
	Node(T data, int level) : m_data(data), m_level(level) {
		m_parent = NULL;
		m_firstChild = NULL;
		m_lastChild = NULL;
		m_nextSibling = NULL;
		m_prevSibling = NULL;
		m_firstChild = NULL;
		m_lastChild = NULL;
	}
	void setData(T data) {
		m_data = data;
	}
	void addChild(Node* child) {
		child->m_parent = this;
		if (m_firstChild == NULL) {
			m_firstChild = child;
			m_lastChild = child;
		}
		else {
			child->m_prevSibling = m_lastChild;
			m_lastChild->m_nextSibling = child;
			m_lastChild = child;
		}
		child->m_level = m_level + 1;
	}
	void addChild(T t) {
		addChild(FCT_NEW (Node<T>,t, m_level + 1));
	}
	void removeChild(Node* child) {
		if (child == m_firstChild) {
			m_firstChild = child->m_nextSibling;
			if (m_firstChild != NULL) {
				m_firstChild->m_prevSibling = NULL;
			}
			child->m_nextSibling = NULL;
		}
		else if (child == m_lastChild) {
			m_lastChild = child->m_prevSibling;
			if (m_lastChild != NULL) {
				m_lastChild->m_nextSibling = NULL;
			}
			child->m_prevSibling = NULL;
		}
		child->m_nextSibling = NULL;
		child->m_prevSibling = NULL;
		child->m_parent = NULL;
		child->release();
		child = NULL;
	}
	void removeChild(T t) {
		Node<T>* child = findChild(t);
		if (child != NULL) {
			removeChild(child);
		}
		return;
	}
	Node<T>* findChild(T t) {
		Node<T>* current = m_firstChild;
		while (current != NULL) {
			if (current->m_data == t) {
				return current;
			}
			current = current->m_nextSibling;
		}
		return NULL;
	}
	T getData() {
		return m_data;
	}
	int getLevel() {
		return m_level;
	}
	void traversal(void (*func)(Node<T>* node,void* param),void* param) { //ǰ�����
		func(this, param); 
		if (m_firstChild != NULL) {
			m_firstChild->traversal(func, param);
		}
		if (m_nextSibling != NULL) {
			m_nextSibling->traversal(func, param);
		}
	}
public:
	T m_data;
	Node* m_parent;
	//friend class Tree;  
	Node* m_nextSibling;
	Node* m_prevSibling;
	Node* m_firstChild;
	Node* m_lastChild;
	int m_level;
}; 


template <typename T>
class Tree : public Node<T> {
public:
	Tree(T data) : Node<T>(data, 0) {}
private:

};