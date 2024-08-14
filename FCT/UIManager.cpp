#include "hander.h"
namespace FCT {

	Window* g_window;
	UIManager::UIManager()
	{
		REF_CLASS_BEGIN();
	}
	UIManager::~UIManager()
	{
		destroy();
	}
	void UIManager::DrawControlShape(Node<UIControlBase*>* node, void* param) {
		UIControlBase* control = node->getData();
		UIManager* uiManager = (UIManager*)param;
		control->m_mutex->lock();
		if (control->m_texture) {
			uiManager->getCreateContext()->setTexture(control->m_texture);
		}
		if (control->getShape()) {
			uiManager->m_context->draw(
				control->getShape(), control->getx(), control->gety());
		}
		control->m_mutex->unlock();
		return;
	}
	void UIManager::updata()
	{
		contextMutex->lock();
#ifdef GRAPH_DEBUG
		IDXGraphicsAnalysis* pGraphicsAnalysis;
		HRESULT getAnalysis = DXGIGetDebugInterface1(0, __uuidof(pGraphicsAnalysis), reinterpret_cast<void**>(&pGraphicsAnalysis));
		pGraphicsAnalysis->BeginCapture();
#endif // GRAPH_DEBUG
		
		m_context->clear(0, 0, 0, 1.0f);
		m_controlTree->traversal(DrawControlShape, this);
		m_context->writeIn(m_window->getBuffer());
		m_window->flush();

#ifdef GRAPH_DEBUG
		pGraphicsAnalysis->EndCapture();
#endif // GRAPH_DEBUG
		contextMutex->unlock();
	}
	void UIManager::create(Window* window)
	{
		contextMutex = CreateMutex();
		contextMutex->create();
		m_context = FCT_NEW(Directx11_Context);
		m_context->create();
		InitShapeModule(m_context);
		m_uiBuffer = m_context->createImage();
		m_uiBuffer->setSize(window->getwidth(), window->getheight());
		m_uiBuffer->create();
		m_context->setTarget(m_uiBuffer);
		m_window = window;
		m_input = m_window->getInput();
		RectangleGeometry* rect = FCT_NEW(RectangleGeometry);
		rect->w = m_window->getwidth();
		rect->h = m_window->getheight();
		m_root = FCT_NEW(UIRoot,m_window->getwidth()
		, m_window->getheight());
		m_root->setCenter(0, 0);
		m_root->setInputShape(rect);
		m_root->createRenderer(Directx11_UIGraphicsRendererChoose);
		m_root->bind(this);
		m_controlTree = FCT_NEW(Tree<UIControlBase*>, m_root);
		m_inputTranslate = FCT_NEW(SoftRenderer_UIInputTranlate, window, m_controlTree);
		m_callback = FCT_NEW(UICallBack, m_inputTranslate, this);
		m_inputTranslate->updata();
		//树应该再callback之前创建完
		m_window->getInput()->registerInputCallBack(m_callback);
		rect->release();
	}
	void UIManager::addControl(UIControlBase* control)
	{
		control->addRef();
		control->m_mutex->create();
		control->m_mutex->addRef();
		control->m_UIManager = this;
		//if (control->getControlType() == control_type_graphics) {
		//	((UIGraphics*)control)->bind(this);
		//}
		m_controlTree->addChild(control);
		m_inputTranslate->updata();
	}
	void UIManager::removeControl(UIControlBase* control)
	{
		m_controlTree->removeChild(control);
		control->release();
		//TODO:添加检查是否成功remove再release
	}
	void UIManager::destroy()
	{
		removeAll();
		m_window->getInput()->registerInputCallBack(NULL);
		FCT_RELEASE(m_inputTranslate);
		FCT_RELEASE(m_callback);
		FCT_RELEASE(m_controlTree);
		FCT_RELEASE(m_root);
		FCT_RELEASE(m_context);
		FCT_RELEASE(m_uiBuffer);
	}

	void UIManager::flushRoot()
	{
		contextMutex->lock();
		m_root->flush();
		contextMutex->unlock();
	}

	void UIManager::removeAll()
	{
		m_controlTree->removeChildIf(tree_remove_release_if_func, NULL);
	}

	Window* UIManager::getWindow()
	{
		return m_window;
	}


	nctest_result_t UICallBack::onNCTest(int x, int y)
	{
		//剔除边框 -1~size
		if (x < 0) {
			return nctest_border;
		}
		if (y < 0) {
			return nctest_border;
		}
		if (x >= m_manager->getWindow()->getwidth()) {
			return nctest_border;
		}
		if (y >= m_manager->getWindow()->getheight()) {
			return nctest_border;
		}
		if (m_translate->getControl(x, y)->getData()->getControlType() == control_type_caption) {
			return nctest_caption;
		}
		return nctest_client;
	}

	void UICallBack::onPaint()
	{
		m_manager->updata();
	}

	void UICallBack::onMouseLButtonDown(int x, int y)
	{
		m_translate->updataFocus(x, y);
	}

	void UICallBack::onMouseLButtonUp(int x, int y)
	{
	}

	void UICallBack::onMouseRButtonDown(int x, int y)
	{
		m_translate->updataFocus(x, y);
	}

	void UICallBack::onMouseRButtonUp(int x, int y)
	{
	}

	void UICallBack::onMouseMove(int x, int y)
	{
	}

	void UICallBack::onMouseWheel(int x, int y, int delta)
	{
	}

	void UICallBack::onChar(wchar_t ch)
	{
		if (m_translate->getOnFocus()) {
			m_translate->getOnFocus()->m_data->onChar(ch);
			return;
		}
		return;
	}

	void UICallBack::onKeyDown(int key)
	{
	}

	void UICallBack::onKeyUp(int key)
	{
	}

	SoftRenderer_UIInputTranlate::SoftRenderer_UIInputTranlate(Window* wnd, Tree<UIControlBase*>* tree)
	{
		m_window = wnd;
		m_tree = tree;
		m_tree->addRef();
		int nLong = m_window->getwidth() * m_window->getheight();
		m_control = FCT_NEWS(Node<UIControlBase*>*, nLong);
		for (int i = 0; i < nLong; i++) {
			m_control[i] = tree;
		}
	}

	struct ui_translate_drawpoint_param {
		Window* wnd;
		Node<UIControlBase*>** translate;
		Node<UIControlBase*>* control;
		Color color;
	};
	void ui_translate_drawpoint(void* _param, int x, int y) {
		ui_translate_drawpoint_param* param = (ui_translate_drawpoint_param*)_param;
		Window* wnd = param->wnd;
		if (x >= 0 && y >= 0 &&
			x < wnd->getwidth() && y < wnd->getheight()) {
			//wnd->getBuffer()[x + y * wnd->getwidth()] = param->color;
			param->translate[x + y * wnd->getwidth()] = param->control;
		}
	}
	void ui_translate_updata(Node<UIControlBase*>* node, void* _param) {
		ui_translate_drawpoint_param* param = (ui_translate_drawpoint_param*)_param;
		param->control = node;
		Window* wnd = param->wnd;
		if (node->m_data->getInputShape()) {
			if (node->m_data->getControlType() == control_type_caption) {
				param->color = { 1,0,0,1 };
			}
			else {
				param->color = { 0,0,1,1 };
			}
			node->m_data->getInputShape()->traversal(ui_translate_drawpoint, param,
				node->m_data->getx(), node->m_data->gety());
		}
	}
	void SoftRenderer_UIInputTranlate::updata()
	{
		ui_translate_drawpoint_param param;
		param.wnd = m_window;
		param.translate = m_control;
		m_tree->traversal(ui_translate_updata, &param);
		m_window->flush();

	}

	Node<UIControlBase*>* SoftRenderer_UIInputTranlate::getControl(int x, int y)
	{
		return m_control[y * m_window->getwidth() + x];
	}

	Node<UIControlBase*>* SoftRenderer_UIInputTranlate::getOnFocus()
	{
		return m_onFocusControl;
	}

	int SoftRenderer_UIInputTranlate::updataFocus(int x, int y)
	{
		if (x < 0 || y < 0) {
			m_onFocusControl = NULL;
			return 0;
		}
		if (x > m_window->getwidth() || y > m_window->getheight()) {
			m_onFocusControl = NULL;
			return 0;
		}
		Node<UIControlBase*>* control = m_control[y * m_window->getwidth() + x];
		m_onFocusControl = control;
		return 0;
	}

	void UIGraphics::createRenderer(UIGraphicsRendererChoose choose)
	{
		switch (choose)
		{
		case FCT::Directx11_UIGraphicsRendererChoose:
			m_context = FCT_NEW(Directx11_Context);
			m_context->create();
			break;
		case 0:
		default:
#ifdef _WIN32
			m_context = FCT_NEW(Directx11_Context);
			m_context->create();
#endif // _WIN32
			break;
		}
	}

	Context* UIGraphics::getContext()
	{
		return m_context;
	}

	void UIGraphics::size(int w, int h)
	{
		if (m_manager) {
			return;
		}
		m_width = w;
		m_height = h;
	}


	void UIGraphics::move(int x, int y)
	{
		m_mutex->lock();
		m_cx = x;
		m_cy = y;
		m_mutex->unlock();
	}

	void UIGraphics::flush()
	{
		m_mutex->lock();
		DrawDirectx11ImageToDirectx11TextureSameSize(m_manager->getCreateContext(), m_buffer, m_texture);
		m_manager->getCreateContext()->flush();
		m_mutex->unlock();
	}
	void UIGraphics::bind(UIManager* manager)
	{
		m_manager = manager;

		m_texture = m_manager->getCreateContext()->createTexture();
		m_texture->setSize(m_width, m_height);
		m_texture->create();
		m_buffer = m_context->createImage();
		m_buffer->setSize(m_width, m_height);
		m_buffer->create();
		size(m_width, m_height);
		m_context->setTarget(m_buffer);
		m_context->clear(0, 0, 0, 1.0f);
		m_context->flush();
		flush();	
		if (!m_shape) {
			Rectangle* shape = FCT_NEW(Rectangle);
			shape->setRect(m_width, m_height);
			shape->setTexcoord(0, 0, 1, 1);
			shape->setColor({ 1,1,1,1 });
			shape->create(m_manager->getCreateContext());
			m_shape = shape;
		}
	}
}
