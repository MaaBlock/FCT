#include "hander.h"
using namespace FCT;
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
	circle->release();
	Font* font = FCT_NEW(Font);
	font->create("NSimSun-02.ttf");
	Edit* edit = FCT_NEW(Edit);
	edit->setFont(font);
	edit->pos(0, 0);
	edit->size(800, 400);
	edit->setColor({ 0,0,0,1 }, { 1,1,1,1 });
	edit->setText(L"Hello,World!");
	edit->create();
	ui->addControl(edit);
	edit->updata();
	edit->flush();
	wnd->show();
	// ...这部分管线命令都将被捕获到
#ifdef GRAPH_DEBUG
	pGraphicsAnalysis->EndCapture();
#endif // GRAPH_DEBUG
	while (wnd->isRunning()) {
		Sleep(1);
	}
	ui->release();
	wnd->release();
	_output_object(std::cout);
	return 0;
}

