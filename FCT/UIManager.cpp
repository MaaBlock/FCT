#include "hander.h"

namespace FCT {

	Window* g_window;
	UIManager::UIManager()
	{
		REF_CLASS_BEGIN();
	}
	Circle* g_circle;
	Text* g_text;
	void UIManager::DrawControlShape(Node<UIControlBase*>* node, void* param) {
		UIControlBase* control = node->getData();
		UIManager* uiManager = (UIManager*)param;
		if (control->getShape()) {
			uiManager->m_context->draw(
				control->getShape(), control->getx(), control->gety());
		}
		return;
	}
	void UIManager::updata()
	{
#ifdef GRAPH_DEBUG
		IDXGraphicsAnalysis* pGraphicsAnalysis;
		HRESULT getAnalysis = DXGIGetDebugInterface1(0, __uuidof(pGraphicsAnalysis), reinterpret_cast<void**>(&pGraphicsAnalysis));
		pGraphicsAnalysis->BeginCapture();
#endif // GRAPH_DEBUG
		//m_context->clear(0, 0, 1, 1.0f);
		//m_context->draw(g_text, 50, 50);
		//
		m_controlTree->traversal(DrawControlShape, this);
		m_context->writeIn(m_window->getBuffer());
		m_window->flush();
#ifdef GRAPH_DEBUG
		pGraphicsAnalysis->EndCapture();
#endif // GRAPH_DEBUG
	}
	void UIManager::create(Window* window)
	{
		m_context = new Directx11_Context;
		m_context->create();
		m_uiBuffer = m_context->createImage(window->getwidth(), window->getheight());
		m_context->setTarget(m_uiBuffer);
		m_window = window;
		m_input = m_window->getInput();
		RectangleGeometry* rect = new RectangleGeometry;
		rect->w = m_window->getwidth();
		rect->h = m_window->getheight();
		m_root = new UIRoot;
		m_root->setCenter(0, 0);
		m_root->setInputShape(rect);
		m_controlTree = new Tree<UIControlBase*>(m_root);
		m_inputTranslate = new SoftRenderer_UIInputTranlate(window, m_controlTree);
		m_callback = new UICallBack(m_inputTranslate,this);
		m_inputTranslate->updata();
		//树应该再callback之前创建完
		m_window->getInput()->registerInputCallBack(m_callback);
	}
	void UIManager::addControl(UIControlBase* control)
	{
		m_controlTree->addChild(control);
		m_inputTranslate->updata();
	}
	void UIManager::destroy()
	{

	}

	nctest_result_t UICallBack::onNCTest(int x, int y)
	{
		if (m_translate->getControl(x, y)->getData()->getControlType() == control_type_caption) {
			return nctest_caption;
		}
		return nctest_clent;
	}

	void UICallBack::onPaint()
	{
		m_manager->updata();
	}

	SoftRenderer_UIInputTranlate::SoftRenderer_UIInputTranlate(Window* wnd, Tree<UIControlBase*>* tree)
	{
		REF_CLASS_BEGIN();
		m_window = wnd;
		m_tree = tree;
		m_tree->addRef();
		int nLong = m_window->getwidth() * m_window->getheight();
		m_control = new Node<UIControlBase*>*[nLong];
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

	void UIGraphics::createRenderer(UIGraphicsRendererChoose choose)
	{	
		switch (choose)
		{
		case FCT::Directx11_UIGraphicsRendererChoose:
			m_context = new Directx11_Context;
			break;
		case 0:
		default:
#ifdef _WIN32
			m_context = new Directx11_Context;
#endif // _WIN32
			break;
		}
		m_image = m_context->createImage(m_width, m_height);
		m_buffer = m_context->createImage(m_width, m_height);
		m_context->setTarget(m_buffer);
	}

	Context* UIGraphics::getContext()
	{
		return m_context;
	}

	void UIGraphics::flush()
	{
	}

}
