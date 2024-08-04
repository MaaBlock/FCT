enum control_t {
	control_type_unname = 0,
	control_type_base = 1,
	control_type_caption = 2,
	control_type_graphics = 3,
	control_type_sys_edit = 3
};
extern Window* g_window;
class UIControlBase : public RefCounted {
public:
	virtual ~UIControlBase() {
		if (m_inputShape) {
			m_inputShape->release();
		}
	}
	virtual control_t getControlType() {
		return control_type_base;
	}
	virtual Geometry* getInputShape() {
		return m_inputShape;
	}
	virtual void setInputShape(Geometry* inputShape) {
		if (m_inputShape) {
			m_inputShape->release();
		}
		m_inputShape = inputShape;
		m_inputShape->addRef();
	}
	virtual void setCenter(int cx, int cy) {
		m_cx = cx;
		m_cy = cy;
	}

	virtual int getx() {
		return m_cx;
	}
	virtual int gety() {
		return m_cy;
	}
protected:
	Geometry* m_inputShape = NULL;
	int m_cx, m_cy;//center x,center y
private:

};
class UICaption : public UIControlBase {
public:
	control_t getControlType() {
		return control_type_caption;
	}
private:
};
class UIGraphics : public UIControlBase {
public:
	control_t getControlType() {
		return control_type_graphics;
	}
	void setBuffer(Image* buffer) {
		m_buffer = buffer;
	}
protected:
	Image* m_buffer;
};
class UIRoot : public UIGraphics {
public:

private:

};
class UICallBack;
class UIInputTranslate : public RefCounted {
public:
	virtual void updata() = 0;
	virtual Node<UIControlBase*>* getControl(int x, int y) = 0;
protected:
	Window* m_window;
	Tree<UIControlBase*>* m_tree;
};
class UIManager : public RefCounted
{
public:
	UIManager();
	void updata();
	void create(Window* window);
	void destroy();
private:
	Window* m_window;
	Input* m_input;
	Tree<UIControlBase*>* m_controlTree;
	UICallBack* m_callback;
	UIRoot* m_root;
	UIInputTranslate* m_inputTranslate;
	Context* m_context;
	Image* m_uiBuffer;
};
class SoftRenderer_UIInputTranlate : public UIInputTranslate {
public:
	SoftRenderer_UIInputTranlate(Window* wnd, Tree<UIControlBase*>* tree);
	void updata();
	Node<UIControlBase*>* getControl(int x, int y);
private:
	Node<UIControlBase*>** m_control;
};
class UICallBack : public InputCallBack {
public:
	UICallBack(UIInputTranslate* translate, UIManager* manager) : m_translate(translate), m_manager(manager){

	}
	nctest_result_t onNCTest(int x, int y);
	void onPaint();
private:
	UIManager* m_manager;
	UIInputTranslate* m_translate;
};

