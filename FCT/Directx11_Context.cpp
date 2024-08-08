#include "hander.h"
namespace FCT {
	ID3DBlob* Directx11_Context::VertexShader2dCompiled = NULL;
	ID3DBlob* Directx11_Context::PixelShader2dCompiled = NULL;
	void Directx11_Context::Init()
	{
		VertexShader2dCompiled = compileVertexShader(
			"cbuffer TargetSize : register(b0)"
			"{"
			"float2 WindowSize;"
			"float2 ShapePos;"
			"}"
			"Texture2DMS<float4, 2>  texcoord : register(t0);"
			"struct VSOut"
			"{"
			"float4 pos : SV_Position;"
			"float4 color : Color;"
			"float2 tex : Texcoord;"
			"};"
			"VSOut main(float4 color : Color,float2 pos : Position,float2 tex : Texcoord)"
			"{"
			"	VSOut ret;"
			"	ret.pos = float4((pos.x + ShapePos.x) / WindowSize.x * 2 - 1,-((pos.y + ShapePos.y) / WindowSize.y * 2) +1  ,0,1.0f);"
			"	ret.color = color;"
			"	ret.tex = tex;"
			"	return ret;"
			"}"
		);
		PixelShader2dCompiled = compilePixelShader(
			"Texture2DMS<float4, 2> texcoord : register(t0);"
			"SamplerState g_sampler : register(s0);"
			"float4 main(float4 pos : SV_Position,float4 color : Color,float2 tex : Texcoord ) : SV_Target"
			"{"
			"   if (tex.x < 0){"
			"       return color;"
			"	}"
			"   return texcoord.Load(tex, g_sampler); "
			"}");
	}
	Directx11_Context::Directx11_Context()
	{
		REF_CLASS_BEGIN();
		m_device = NULL;
		m_context = NULL;
		m_target = NULL;
		m_rasterizerState = NULL;
		m_geometryShader = NULL;
		createResouce = FCT_NEW(Directx11_CreateContextFactory);

	}
	void Directx11_Context::clear(float r, float g, float b, float a)
	{
		float color[4] = { r,g,b,a };
		m_context->ClearRenderTargetView(((Directx11_Image*)m_target)->getRenderTargetView(), color);
		m_context->ClearDepthStencilView(((Directx11_Image*)m_target)->getDepthStencilView(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	}
	ID3DBlob* Directx11_Context::compileVertexShader(const char* VertexShaderCode)
	{
		ID3DBlob* ErrorMessage = NULL;
		ID3DBlob* VertexShaderCompiled = NULL;
		D3DCompile(VertexShaderCode, strlen(VertexShaderCode)
			, NULL, NULL, D3D_COMPILE_STANDARD_FILE_INCLUDE,
			"main", "vs_5_0", D3DCOMPILE_DEBUG, 0, &VertexShaderCompiled, &ErrorMessage);
		if (ErrorMessage) {
			std::cout << (char*)ErrorMessage->GetBufferPointer() << std::endl;
			//TODO:error
			ErrorMessage->Release();
		}
		return VertexShaderCompiled;
	}
	ID3DBlob* Directx11_Context::compilePixelShader(const char* PixelShaderCode)
	{
		ID3DBlob* PixelShaderCompiled = NULL;
		ID3DBlob* ErrorMessage = NULL;
		D3DCompile(PixelShaderCode, strlen(PixelShaderCode),
			NULL, NULL, D3D_COMPILE_STANDARD_FILE_INCLUDE,
			"main", "ps_5_0", D3DCOMPILE_DEBUG, 0, &PixelShaderCompiled, &ErrorMessage);
		if (ErrorMessage) {
			std::cout << (char*)ErrorMessage->GetBufferPointer();
			//Todo error
			ErrorMessage->Release();
		}
		return PixelShaderCompiled;
	}
	void Directx11_Context::create()
	{
		m_depthStencilState = NULL;
		D3D_FEATURE_LEVEL featureLevels[] = {
			D3D_FEATURE_LEVEL_11_1,
			D3D_FEATURE_LEVEL_11_0, };
		D3D11CreateDevice(NULL,
			D3D_DRIVER_TYPE_HARDWARE,
			0,
			D3D11_CREATE_DEVICE_DEBUG,
			featureLevels
			, 2,
			D3D11_SDK_VERSION,
			&m_device,
			NULL,
			&m_context);
		m_device->CreateVertexShader(VertexShader2dCompiled->GetBufferPointer(), VertexShader2dCompiled->GetBufferSize(),
			NULL, &m_vertexShader2d);
		m_device->CreatePixelShader(PixelShader2dCompiled->GetBufferPointer(), PixelShader2dCompiled->GetBufferSize(),
			NULL, &m_pixelShader2d);
		D3D11_INPUT_ELEMENT_DESC layout2d[] =
		{
			{ "Position", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
			{ "Color", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 8, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "Texcoord", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		};
		UINT numElements = ARRAYSIZE(layout2d);
		m_device->CreateInputLayout(layout2d, numElements,
			VertexShader2dCompiled->GetBufferPointer(), VertexShader2dCompiled->GetBufferSize(), &m_input2dLayout);
		D3D11_BUFFER_DESC cbd;
		ZeroMemory(&cbd, sizeof(cbd));
		cbd.Usage = D3D11_USAGE_DYNAMIC;
		cbd.ByteWidth = sizeof(directx11_constbuffer2d);
		cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE ;
		m_device->CreateBuffer(&cbd, nullptr, &m_constBuffer2d);
		m_nullBlendState = FCT_NEW(Directx11_BlendState);
		m_nullBlendState->create(m_device);
		m_nullSamplerState = FCT_NEW(Directx11_SamplerState);
	}
	Image* Directx11_Context::createImage(int w,int h)
	{
		return FCT_NEW(Directx11_Image,m_device,w,h);
	}
	void Directx11_Context::setTarget(Image* img)
	{
		if (m_target) {
			m_target->release();
		}
		m_target = img;
		m_context->OMSetRenderTargets(1, ((Directx11_Image*)m_target)->getRenderTargetViewPtr()
			, ((Directx11_Image*)m_target)->getDepthStencilView());
		D3D11_MAPPED_SUBRESOURCE data;
		m_context->Map(m_constBuffer2d, 0, D3D11_MAP_WRITE_DISCARD, 0, &data);
		((directx11_constbuffer2d*)data.pData)->targetsize = { (float)m_target->getWidth(),(float)m_target->getHeight() };
		m_context->Unmap(m_constBuffer2d, 0);

		D3D11_VIEWPORT vp;
		vp.Width = (float)m_target->getWidth();
		vp.Height = (float)m_target->getHeight();
		vp.MinDepth = 0.0f;
		vp.MaxDepth = 1.0f;
		vp.TopLeftX = 0;
		vp.TopLeftY = 0;
		m_context->RSSetViewports(1, &vp);
		m_target->addRef();
	}
	void Directx11_Context::draw(Shape* shape, float x, float y)
	{
		D3D11_MAPPED_SUBRESOURCE data;
		directx11_constbuffer2d buffer;
		buffer.shapepos = { x + shape->getOffsetX(),y + shape->getOffsetY()};
		buffer.targetsize = { (float)m_target->getWidth(),(float)m_target->getHeight() };
		m_context->Map(m_constBuffer2d, 0, D3D11_MAP_WRITE_DISCARD, 0, &data);
		memcpy(data.pData, &buffer, sizeof(directx11_constbuffer2d));
		m_context->Unmap(m_constBuffer2d, 0);
		m_context->IASetInputLayout(m_input2dLayout);
		m_context->VSSetShader(m_vertexShader2d, NULL, 0);
		m_context->PSSetShader(m_pixelShader2d, NULL, 0);
		m_context->VSSetConstantBuffers(0, 1, &m_constBuffer2d);
		m_blendState ? m_blendState->bind(this) : 
			m_nullBlendState->bind(this);
		m_samplerState ? m_samplerState->bind(this)
			:m_nullSamplerState->bind(this);
		m_rasterizerState ? m_rasterizerState->bind(this)
			: m_context->RSSetState(NULL);
		m_geometryShader ? m_geometryShader->bind(this)
			: m_context->GSSetShader(NULL, NULL, 0);
		m_depthStencilState ? m_depthStencilState->bind(this)
			: m_context->OMSetDepthStencilState(NULL, NULL);

		UINT stride = sizeof(Vertex2d);
		UINT offset = 0;
		shape->predraw(this);
		for (int i = 0; i < shape->m_resouceNum; i++) {
			shape->m_resouce[i]->bind(this);
		}
	}
	void Directx11_Context::draw(Object*, float x, float y, float z)
	{

	}
	void Directx11_Context::flush()
	{

	}
	void Directx11_Context::writeIn(Color* buffer)
	{
		writeIn(m_target, buffer);
	}
	void Directx11_Context::writeIn(Image* img, Color* buffer)
	{
		int w, h;
		w = img->getWidth();
		h = img->getHeight();
		ID3D11Texture2D* temp;
		D3D11_TEXTURE2D_DESC desc;
		desc.SampleDesc.Count = 1;
		desc.SampleDesc.Quality = 0;
		desc.Width = w;
		desc.Height = h;
		desc.MipLevels = 1;
		desc.ArraySize = 1;
		desc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		desc.Usage = D3D11_USAGE_STAGING;
		desc.BindFlags = 0;
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
		desc.MiscFlags = 0;
		m_device->CreateTexture2D(&desc, NULL, &temp);
		ID3D11Texture2D* tempDeault;
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.CPUAccessFlags = NULL;
		m_device->CreateTexture2D(&desc, NULL, &tempDeault);
		m_context->ResolveSubresource(tempDeault, 0, ((Directx11_Image*)img)->getTexture(), 0, DXGI_FORMAT_R32G32B32A32_FLOAT);
		m_context->CopyResource(temp, tempDeault);
		m_context->Flush();
		//m_context->CopyResource(temp, ((Directx11_Image*)img)->getTexture());
		D3D11_MAPPED_SUBRESOURCE msr;
		LRESULT rc;
		m_context->Map(temp, 0, D3D11_MAP_READ, 0, &msr);
		for (int i = 0; i < h; i++) {
			memcpy(buffer + i * w, (char*)msr.pData + i * msr.RowPitch, w * sizeof(Color));
		}
		m_context->Unmap(temp, 0);
		temp->Release();
	}
	Vertex2dBuffer* Directx11_Context::createVertex2dBuffer(Vertex2d* vertex, int vertexNum)
	{
		return FCT_NEW(Directx11_Vertex2dBuffer,m_device, vertex, vertexNum);
	}
	ConstBuffer* Directx11_Context::createConstBuffer(unsigned id, void* data, int biteSize, int type)
	{
		return FCT_NEW(Directx11_ConstBuffer,m_device, id, data, biteSize, type);
	}
	Topology* Directx11_Context::createToplogy(shape_primitive_topology_t t)
	{
		return FCT_NEW(Directx11_Topology,t);
	}
	PixelShader* Directx11_Context::createPixelShader(const char* code)
	{
		return FCT_NEW(Directx11_PixelShader,m_device,code);
	}
	VertexShader* Directx11_Context::createVertexShader(const char* code)
	{
		return FCT_NEW(Directx11_VertexShader,m_device, code);
	}
	void Directx11_Context::setDeafultResouce(ContextResouce* resouce)
	{
		setDeafultResouce(resouce->getResouceType(), resouce);
	}
	void Directx11_Context::setDeafultResouce(context_resouce_t resoutType, ContextResouce* resouce)
	{
		switch (resoutType)
		{
		case context_resource_rasterizer_state:
			m_rasterizerState = (Directx11_RasterizerState*)resouce;
			break;
		case context_resource_blend_state:
			m_blendState = resouce ? (Directx11_BlendState*)resouce
				: m_nullBlendState;
			break;
		case context_resource_depth_stencil_state:
			m_depthStencilState = (Directx11_DepthStencilState*)resouce;
			break;
		default:
			break;
		}
	}
	void Directx11_Context::setTexture(Image* img)
	{
		m_context->PSSetShaderResources(0, 1,
			((Directx11_Image*)img)->getShaderResourceViewPtr());
	}
};