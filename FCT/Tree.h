
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
	//void removeChild(Node* child) {
	//	if (child == m_firstChild) {
	//		m_firstChild = child->m_nextSibling;
	//		if (m_firstChild != NULL) {
	//			m_firstChild->m_prevSibling = NULL;
	//		}
	//		child->m_nextSibling = NULL;
	//	}
	//	else if (child == m_lastChild) {
	//		m_lastChild = child->m_prevSibling;
	//		if (m_lastChild != NULL) {
	//			m_lastChild->m_nextSibling = NULL;
	//		}
	//		child->m_prevSibling = NULL;
	//	}
	//	else {
	//		child->m_prevSibling->m_nextSibling = child->m_nextSibling;
	//		child->m_nextSibling->m_prevSibling = child->m_prevSibling;
	//	}
	//	child->m_nextSibling = NULL;
	//	child->m_prevSibling = NULL;
	//	child->m_parent = NULL;
	//	child->release();
	//	child = NULL;
	//}
	static void setParent(Node<T>* node, void* param) {
		node->m_parent = (Node<T>*)param;
	}
	void removeChild(Node* child) {
		if (child->m_firstChild) {
			child->m_prevSibling = child->m_firstChild;
			child->m_firstChild->m_prevSibling = child->m_prevSibling;
			child->m_prevSibling->m_nextSibling = child->m_firstChild;
			traversalLevel(child->m_firstChild, setParent, child->m_parent, traversal_level_direction_next);
		}
		if (child->m_lastChild) {
			child->m_nextSibling = child->m_lastChild;
			child->m_lastChild->m_nextSibling = child->m_nextSibling;
			child->m_nextSibling->m_prevSibling = child->m_lastChild;
		}
		child->m_firstChild = NULL;
		child->m_lastChild = NULL;
		child->release();
	}
	void removeIf(bool (*remove)(Node<T>* node, void* param),void* param) { 

		//if (remove(this, param)) {
		//	if (m_parent != NULL) {
		//		((Node<T>*)m_parent)->removeChild(this);
		//	}
		//	release();
		//}
		//else {
		Node<T>* current = m_firstChild;
		while (current != NULL) {
			current->removeIf(remove, param);
			current = current->m_nextSibling;
		}
		if (remove(this,param)) {
			removeChild(this);
		}
	}

	
	void removeChildIf(bool (*remove)(Node<T>* node, void* param), void* param) {
		Node<T>* current = m_firstChild;
		Node<T>* temp = NULL;
		while (current != NULL) {
			temp = current->m_nextSibling;
			current->removeIf(remove, param);
			current = temp;
		}
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
	enum traversal_level_direction_t {
		traversal_level_direction_next = 0x1,
		traversal_level_direction_pre = 0x2,
	};
	void traversalLevel(Node<T>* node, void (*func)(Node<T>* node, void* param), void* param, int direction = 1 | 2) {
		func(node, param);
		if (direction & traversal_level_direction_next && node->m_nextSibling != NULL) {
			node->m_nextSibling->traversalLevel(node->m_nextSibling, func, param, traversal_level_direction_next);
		}
		if (direction & traversal_level_direction_pre && node->m_prevSibling != NULL) {
			node->m_prevSibling->traversalLevel(node->m_prevSibling, func, param, traversal_level_direction_pre);
		}
	}
	void traversal(void (*func)(Node<T>* node,void* param),void* param) { //Ç°Ðò±éÀú
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
bool tree_remove_release_if_func(Node<T>* node, void* param) {
	node->m_data->release();
	return true;
}

template <typename T>
class Tree : public Node<T> {
public:
	Tree(T data) : Node<T>(data, 0) {}
private:

};