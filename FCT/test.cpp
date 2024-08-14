#include "hander.h"
using namespace FCT;


namespace FCT {
	class NewCharShape : public Shape {
	public:

		void create(Context* context, stbtt_fontinfo* fontInfo, wchar_t ch);
	private:
		Shape** m_shapes;
		size_t m_shapeNum;

	};
	class NewFont : public RefCounted {
	public:
		NewFont(Context* context);
		void create(const char* fileNameOrPath);
		NewCharShape* getShape(wchar_t ch);
		void createShape(wchar_t ch);
		void createShape(const wchar_t* text);
		void createShape(wchar_t theFirstChar, wchar_t theEndChar);
	private:
		Context* m_context;
		std::map<wchar_t, NewCharShape*> m_charShapes;
		stbtt_fontinfo* m_fontInfo;
		File* m_fontFile;
	};
	NewFont* CreateNewFont(Context* context);
}
int main(){
	Init();
#ifdef GRAPH_DEBUG
	IDXGraphicsAnalysis* pGraphicsAnalysis;
	HRESULT getAnalysis = DXGIGetDebugInterface1(0, __uuidof(pGraphicsAnalysis), reinterpret_cast<void**>(&pGraphicsAnalysis));
	pGraphicsAnalysis->BeginCapture();
#endif // GRAPH_DEBUG

	Window* wnd = CreateWindow();
	wnd->size(1000, 750);
	wnd->create();
	UIManager* ui = new UIManager;

	CircleGeometry* circle_geometry = new CircleGeometry;
	circle_geometry->r = 50;
	//test
	UICaption* caption = new UICaption;
	caption->setCenter(950, 50);
	caption->setInputShape(circle_geometry);
	circle_geometry->release();
	ui->create(wnd);
	Circle* circle = new Circle();
	circle->setColor({ 1,0,0,1 });
	circle->setR(50);
	circle->create(ui->getCreateContext());
	caption->setDrawShape(circle);
	ui->addControl(caption);
	caption->release();
	circle->release();
	NewFont* font = CreateNewFont(ui->getRootContext());
	font->create("SimSun-01.ttf");
	NewCharShape* shape = font->getShape(L'你');
	Context* reotContext = ui->getRootContext();
	wnd->show();
	// ...这部分管线命令都将被捕获到
#ifdef GRAPH_DEBUG
	pGraphicsAnalysis->EndCapture();
#endif // GRAPH_DEBUG
	while (wnd->isRunning()) {
#ifdef GRAPH_DEBUG	
		pGraphicsAnalysis->BeginCapture();
#endif // GRAPH_DEBUG
		//_output_object_nums(std::cout);
		//reotContext->draw(shape,50,50);
		//ui->flushRoot();
#ifdef GRAPH_DEBUG
		pGraphicsAnalysis->EndCapture();
#endif // GRAPH_DEBUG
		Sleep(1);
	}
	ui->release();
	wnd->release();
	_output_object(std::cout);
	return 0;
}

