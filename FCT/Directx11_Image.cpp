#include "hander.h"
namespace FCT {
	Directx11_Image::Directx11_Image(ID3D11Device* device,int w,int h)
	{
		REF_CLASS_BEGIN();
		m_sampleDesc.Count = 2;
		m_sampleDesc.Quality = DXGI_STANDARD_MULTISAMPLE_QUALITY_PATTERN;
		m_width = w;
		m_height = h;
		m_device = device;
		D3D11_TEXTURE2D_DESC desc;
		desc.SampleDesc = m_sampleDesc;
		desc.Width = w;
		desc.Height = h;
		desc.MipLevels = 1;
		desc.ArraySize = 1;
		desc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET;
		desc.CPUAccessFlags = 0;
		desc.MiscFlags = 0;
		D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
		srvDesc.Format = desc.Format;
		srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2DMS;
		srvDesc.Texture2D.MostDetailedMip = 0;
		srvDesc.Texture2D.MipLevels = desc.MipLevels;
		D3D11_RENDER_TARGET_VIEW_DESC renderTargetData;
		renderTargetData.Format = desc.Format;
		renderTargetData.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2DMS;
		renderTargetData.Texture2D.MipSlice = 0;
		D3D11_TEXTURE2D_DESC depthStencilData;
		depthStencilData.Width = w;
		depthStencilData.Height = h;
		depthStencilData.MipLevels = 1;
		depthStencilData.ArraySize = 1;
		depthStencilData.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		depthStencilData.SampleDesc = m_sampleDesc;
		depthStencilData.Usage = D3D11_USAGE_DEFAULT;
		depthStencilData.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		depthStencilData.CPUAccessFlags = 0;
		depthStencilData.MiscFlags = 0;

		device->CreateTexture2D(&desc, NULL, &m_texture);
		device->CreateTexture2D(&depthStencilData, NULL, &m_depth);
		device->CreateShaderResourceView(m_texture, &srvDesc, &m_srv);
		device->CreateDepthStencilView(m_depth, NULL, &m_dsv);
		device->CreateRenderTargetView(m_texture, &renderTargetData, &m_rtv);
	}
	int Directx11_Image::getWidth()
	{
		return m_width;
	}
	int Directx11_Image::getHeight()
	{
		return m_height;
	}
	ID3D11Texture2D* Directx11_Image::getTexture()
	{
		return m_texture;
	}
	ID3D11DepthStencilView* Directx11_Image::getDepthStencilView()
	{
		return m_dsv;
	}
	ID3D11DepthStencilView** Directx11_Image::getDepthStencilViewPtr()
	{
		return &m_dsv;
	}
	ID3D11RenderTargetView* Directx11_Image::getRenderTargetView()
	{
		return m_rtv;
	}

	ID3D11RenderTargetView** Directx11_Image::getRenderTargetViewPtr()
	{
		return &m_rtv;
	}
	ID3D11ShaderResourceView* Directx11_Image::getShaderResourceView()
	{
		return m_srv;
	}
	void Directx11_Image::createTarget()
	{

	}
	DXGI_SAMPLE_DESC Directx11_Image::getSampleDesc()
	{
		return m_sampleDesc;
	}
}
