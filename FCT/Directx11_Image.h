class Directx11_Image : public Image {
public:
	Directx11_Image(ID3D11Device* device,int w,int h);
	int getWidth();
	int getHeight();
	ID3D11Texture2D* getTexture();
	ID3D11DepthStencilView* getDepthStencilView();
	ID3D11DepthStencilView** getDepthStencilViewPtr();
	ID3D11RenderTargetView* getRenderTargetView();
	ID3D11RenderTargetView** getRenderTargetViewPtr();
	ID3D11ShaderResourceView* getShaderResourceView();
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