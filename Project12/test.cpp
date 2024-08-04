#include "hander.h"
#include <iostream>
using namespace FCT;
int main(){
	Init();
#ifdef GRAPH_DEBUG
	IDXGraphicsAnalysis* pGraphicsAnalysis;
	HRESULT getAnalysis = DXGIGetDebugInterface1(0, __uuidof(pGraphicsAnalysis), reinterpret_cast<void**>(&pGraphicsAnalysis));
	pGraphicsAnalysis->BeginCapture();
#endif // GRAPH_DEBUG

	Window* wnd = CreateWindow();
	wnd->size(800, 600);
	wnd->create();
	UIManager* ui = new UIManager;
	wnd->show();
	ui->create(wnd);
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
	return 0;
}

