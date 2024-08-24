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
	Button("���",[]{
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

�߳�:
���߳� -���ɻ�
�����߳� -����������Ϣ,����ui
��Ⱦ�߳� -��ѡ ������Ⱦ����
һ��Rendererһ���ύ�߳� -����ʵ�ʻ�ͼ
���ڸ���һ��Renderer
UI�󶨸�Renderer
��UI���£�Graphics��:
	1.
	��Ⱦ�߳�:
		�ύ�������uiRenderer
	��Renderer������Renderer��

		�ȴ�
	2.
	��Ⱦ�߳�:
		Flush();
		WaitForUpdataFrame()
	��Renderer:
		renderToImage
	����:
		�����ʱ�����룬�������ӿؼ���ť
		�ύ��ť����Renderer
		Flush();
		WaitForUpdataFrame()
		��ʱ���ڸ��ؼ���δ���£�����ͻ
	����Renderer:
		�ȴ�
	3.
	��Ⱦ�̣߳�
		֪ͨ�����߳��Ҹ�����UI
	�����߳�:
		��������
		���ɻ�ͼָ��
		������Graphics����UI���и���
		Flush();
		WaitForUpdataFrame();
	����Renderer:
		���ܵ�Flush()
		���л�ͼ
		�ύ�����´���
����
	��Ⱦ�߳̽�����Graphics�ؼ���Renderer���߳��Լ������߳�
	�������߳̽���������Renderer
��Ⱦ:
	�ṩWaitForUpdataFrame();
	��������Ⱦ�̵߳ȴ��ύ�̻߳�ͼ���

�ֲ�����:
	�����ڸ���
	�Ӵ��ھ�Ҫ����
	�Ӵ��ڸ���
����״̬:
	�ؼ�����ע������״̬
	�ṩ�¼�ת����״̬
	xml�����ؼ�
	�ؼ�����ͨ���ı�״̬
����ʽui:
	UE Slate
	��ʵ����Ⱦ
	��ʵ��ui
*/