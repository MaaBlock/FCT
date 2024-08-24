#include "hander.h"
namespace FCT {
	class CoreContext {
	public:
		static CoreContext* getInstance();
		void setWindow(Window* window);
		void setEngine(Engine* engine);
		void Init();
	private:
		static CoreContext* Instance;
		Window* m_window;
	};	
	inline static CoreContext* getContext() {
		return CoreContext::getInstance();
	}
	CoreContext* CoreContext::getInstance()
	{
		if (Instance == NULL) {
			Instance = new CoreContext();
		}
		return Instance;
	}
	void CoreContext::setWindow(Window* window)
	{
		m_window = window;
	}
	void CoreContext::Init()
	{
		FCT::Init();
	}
	
}



/*
goal:
InputState* g_inputState = new InputState();
void Input(Event* env){
	updateInputState(g_inputState, env);
}
void Renderer(){
     
}
int main(){
	CoreContext* context = FCT::getContext();
	Window* window = new Window();
	window->setPos(100, 100);
	window->setSize(800, 600);
	window->create();
	Renderer* renderer = new Renderer(window);
	Image* image = GetImageFromMemory(memory);
	Renderer* renderer = new Renderer(image);
	UIManger* ui = new UIManger(window);
	Button("你好",[]{
		std::cout << "Button Clicked!" << std::endl;
	}).add;
	Graphics* grpah = new Graphics;
	grpah
	window->show();
	while(window->isRun()){
		Sleep(1);
	}
	context.quit();
}

线程:
主线程 -不干活
窗口线程 -接受输入消息,处理ui
渲染线程 -可选 生成渲染数据
一个Renderer一个提交线程 -进行实际绘图
窗口给予一个Renderer
UI绑定该Renderer
根UI更新（Graphics）:
	1.
	渲染线程:
		提交命令给根uiRenderer
	根Renderer，窗口Renderer：

		等待
	2.
	渲染线程:
		Flush();
		WaitForUpdataFrame()
	根Renderer:
		renderToImage
	窗口:
		假设此时有输入，更新了子控件按钮
		提交按钮更新Renderer
		Flush();
		WaitForUpdataFrame()
		此时窗口根控件并未更新，不冲突
	窗口Renderer:
		等待
	3.
	渲染线程：
		通知窗口线程我更新了UI
	窗口线程:
		接受命令
		生成绘图指令
		对所有Graphics的子UI进行更新
		Flush();
		WaitForUpdataFrame();
	窗口Renderer:
		接受到Flush()
		进行绘图
		提交并更新窗口
上述
	渲染线程仅交互Graphics控件的Renderer的线程以及窗口线程
	而窗口线程仅交互窗口Renderer
渲染:
	提供WaitForUpdataFrame();
	来进行渲染线程等待提交线程绘图完毕

局部更新:
	父窗口更新
	子窗口均要更新
	子窗口更新
输入状态:
	控件可以注册输入状态
	提供事件转输入状态
	xml描述控件
	控件激活通过改变状态
声明式ui:
	UE Slate
	先实现渲染
	再实现ui
*/