
Window* Win32_D3D11_CreateWindow();

class Win32_D3D11_Window : public Window {
public:

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	static void WndThread(Win32_D3D11_Window* wnd);
	static void Init();
	window_info_t create(uint32_t style); 
	Win32_D3D11_Window();
	~Win32_D3D11_Window();
	void destroy();
	void size(int w, int h);
	void show();
	void name(const wchar_t* name);
	void flush();
	bool isRunning();
	Color* getBuffer();
	int getx();
	int gety();
	int getwidth();
	int getheight();
	Input* getInput();
	//ToDo:
	bool isFocus();
	bool isMinimize();
	bool isForeground();
protected:
	Image* m_bufferImage = NULL;
	Color* m_buffer = NULL;
	bool m_bufferMaped = false;
private:
	Win32_Input* m_input;
	HWND m_wnd;
	HANDLE m_thread;
	const wchar_t* m_name = L"Unnamed";
	int m_width = CW_USEDEFAULT;
	int m_height = CW_USEDEFAULT;
	int m_x = CW_USEDEFAULT;
	int m_y = CW_USEDEFAULT;
	uint32_t m_nMaxWidth = 0;
	uint32_t m_nMaxHeight = 0;
	uint32_t m_nMinWidth = 0;
	uint32_t m_nMinHeight = 0;
	uint32_t m_style = 0;
	bool m_created = false;
	bool m_runing = false;
	ID3D11SamplerState* m_samplerState;
	ID3D11Device* m_device;
	ID3D11DeviceContext* m_context;
	ID3D11Texture2D* m_bufferTexture;
	ID3D11ShaderResourceView* m_bufferTextureView;
	IDXGISwapChain* m_swapChain;
	ID3D11RenderTargetView* m_renderTargetView;
	ID3D11Texture2D* m_depthStencilBuffer;
	ID3D11DepthStencilView* m_depthStencilView;
	ID3D11InputLayout* m_inputLayout;
	D3D_FEATURE_LEVEL m_featureLevel;
	ID3D11VertexShader* m_vertexShader;
	ID3D11PixelShader* m_pixelShader;
	ID3D11Buffer* m_vertexBuffer;
};