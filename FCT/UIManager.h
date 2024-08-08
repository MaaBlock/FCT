enum control_t {
	control_type_unname = 0,
	control_type_base = 1,
	control_type_caption = 2,
	control_type_graphics = 3,
	control_type_sys_edit = 3
};
extern Window* g_window;
class  UIControlBase : public RefCounted {
public:
	UIControlBase() {
		m_mutex = CreateMutex();
	}
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
	virtual void setDrawShape(Shape* shape) {
		if (m_shape) {
			m_shape->release();
		}
		m_shape = shape;
		m_shape->addRef();
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
	virtual void setShape(Shape* shape) {
		m_mutex->lock();
		if (m_shape) {
			m_shape->release();
		}
		m_shape = shape;
		m_shape->addRef();
		m_mutex->unlock();
	}
	virtual Shape* getShape() {
		return m_shape;
	}
	virtual void setImage(Image* image) {
		m_mutex->lock();
		if (m_image) {
			m_image->release();
		}
		m_image = image;	
		m_mutex->unlock();
	}
	virtual Image* getImage() {
		return m_image;
	}
	friend class UIManager;
protected:
	Mutex* m_mutex;
	Shape* m_shape;
	Image* m_image;
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
enum UIGraphicsRendererChoose {
	Directx11_UIGraphicsRendererChoose = 1,
};
class UIGraphics : public UIControlBase {
public:
	//前缓冲由UIManager创建
	//后缓存由用户选取的renderer创建
	//ToDo:实现不同渲染器将后缓存画在前缓存上
	control_t getControlType() {
		return control_type_graphics;
	}
	void createRenderer(UIGraphicsRendererChoose choose);
	Context* getContext();
	void size(int w, int h);
	void move(int x, int y);
	void flush();

	//add的时候会UIManager会调用，不需要自己动手
	void bind(UIManager*);

protected:
	UIManager* m_manager;
	void setShape(Shape* shape) {
		UIControlBase::setShape(shape);
	}
	int m_width;
	int m_height;
	Context* m_context;
	Image* m_buffer;
};
class UIRoot : public UIGraphics {
public:
	UIRoot(int w,int h) {
		size(w, h);
	}
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
	static void DrawControlShape(Node<UIControlBase*>* node, void* param);
	void updata();
	void create(Window* window);
	void addControl(UIControlBase* control);
	void removeControl(UIControlBase* control);//移除一个Conrol
	void deleteControl(UIControlBase* control);//直接delete一个control，
		//与remove相比，删除一个将会从控件树移开并且直接释放Control对应的内存
	void destroy();
	Mutex* contextMutex;
	inline Context* getContext() {
		return m_context;
	}
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

