
class Directx11_Image : public Image {
public:
	Directx11_Image(ID3D11Device* device);
	int msaaEnable(bool enable = true, unsigned count = 2);
	void setSize(unsigned width, unsigned height);
	int create();
	int createWithoutView();
	int getWidth();
	int getHeight();
	ID3D11Texture2D* getTexture();
	ID3D11DepthStencilView* getDepthStencilView();
	ID3D11DepthStencilView** getDepthStencilViewPtr();
	ID3D11RenderTargetView* getRenderTargetView();
	ID3D11RenderTargetView** getRenderTargetViewPtr();
	ID3D11ShaderResourceView* getShaderResourceView();
	ID3D11ShaderResourceView** getShaderResourceViewPtr();
	void createTarget();
	DXGI_SAMPLE_DESC getSampleDesc();
private:
	int m_width;
	int m_height;
	ID3D11Device* m_device;
	ID3D11Texture2D* m_texture;
	ID3D11Texture2D* m_depth;
	ID3D11RenderTargetView* m_rtv;
	ID3D11ShaderResourceView* m_srv;
	ID3D11DepthStencilView* m_dsv;
	DXGI_SAMPLE_DESC m_sampleDesc;
};