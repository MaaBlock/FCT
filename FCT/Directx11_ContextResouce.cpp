#include "hander.h"
namespace FCT {
	Directx11_Vertex2dBuffer::Directx11_Vertex2dBuffer(ID3D11Device* device, Vertex2d* vertex, int vertexNum)
	{
		REF_CLASS_BEGIN();
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(Vertex2d) * vertexNum;
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = 0;
		D3D11_SUBRESOURCE_DATA InitData;
		ZeroMemory(&InitData, sizeof(InitData));
		InitData.pSysMem = vertex;
		device->CreateBuffer(&bd, &InitData, &m_vertexBuffer);
		m_vertexNum = vertexNum;
	}

	int Directx11_Vertex2dBuffer::getVertexNum()
	{
		return m_vertexNum;  // return the number of vertices in the buffer
	}

	Directx11_Vertex2dBuffer::~Directx11_Vertex2dBuffer()
	{
		COM_RELEASE(m_vertexBuffer);
	}

	void Directx11_Vertex2dBuffer::bind(Context* _context)
	{
		ID3D11DeviceContext* context = GetContext((Directx11_Context*)_context);
		UINT stride = sizeof(Vertex2d);
		UINT offset = 0;
		context->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);
		context->Draw(m_vertexNum, 0);
	}

	Directx11_Topology::Directx11_Topology(shape_primitive_topology_t topology) {
		REF_CLASS_BEGIN();
		switch (topology)
		{
		case FCT::shape_primitive_topology_pointlist:
			break;
		case FCT::shape_primitive_topology_linelist:
			m_topology = D3D11_PRIMITIVE_TOPOLOGY_LINELIST;
			break;
		case FCT::shape_primitive_topology_lineloop:
			break;
		case FCT::shape_primitive_topology_linestrip:
			m_topology = D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP;
			break;
		case FCT::shape_primitive_topology_trianglelist:
			m_topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
			break;
		case FCT::shape_primitive_topology_trianglestrip:
			m_topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP;
			break;
		default:
			break;
		}
	}

	void Directx11_Topology::bind(Context* _context)
	{
		ID3D11DeviceContext* context = GetContext((Directx11_Context*)_context);
		context->IASetPrimitiveTopology(m_topology);
	}

	ID3D11Device* Directx11Interface::GetDevice(Directx11_Context* context)
	{
		return context->m_device;
	}

	ID3D11DeviceContext* Directx11Interface::GetContext(Directx11_Context* context)
	{
		return context->m_context;
	}

	Directx11_VertexShader::Directx11_VertexShader(ID3D11Device* device, const char* shadercode)
	{
		REF_CLASS_BEGIN();
		ID3DBlob* ErrorMessage = NULL;
		D3DCompile(shadercode, strlen(shadercode)
			, NULL, NULL, D3D_COMPILE_STANDARD_FILE_INCLUDE,
			"main", "vs_5_0", D3DCOMPILE_DEBUG, 0, &m_byteCode, &ErrorMessage);
		if (ErrorMessage) {
			std::cout << (char*)ErrorMessage->GetBufferPointer() << std::endl;
			//TODO:error
			ErrorMessage->Release();
		}
		device->CreateVertexShader(m_byteCode->GetBufferPointer(), m_byteCode->GetBufferSize(), NULL, &m_vertexShader);
	}

	void Directx11_VertexShader::bind(Context* _context)
	{
		ID3D11DeviceContext* context = GetContext((Directx11_Context*)_context);
		context->VSSetShader(m_vertexShader, NULL, 0);
	}

	Directx11_PixelShader::Directx11_PixelShader(ID3D11Device* device, const char* shadercode)
	{
		REF_CLASS_BEGIN();
		ID3DBlob* ErrorMessage = NULL;
		D3DCompile(shadercode, strlen(shadercode)
			, NULL, NULL, D3D_COMPILE_STANDARD_FILE_INCLUDE,
			"main", "ps_5_0", D3DCOMPILE_DEBUG, 0, &m_byteCode, &ErrorMessage);
		if (ErrorMessage) {
			std::cout << (char*)ErrorMessage->GetBufferPointer() << std::endl;
			//TODO:error
			ErrorMessage->Release();
		}
		device->CreatePixelShader(m_byteCode->GetBufferPointer(), m_byteCode->GetBufferSize(), NULL, &m_pixelShader);
	}
	void Directx11_PixelShader::bind(Context* _context)
	{
		ID3D11DeviceContext* context = GetContext((Directx11_Context*)_context);
		context->PSSetShader(m_pixelShader, NULL, 0);
	}

	Directx11_GeometryShader::Directx11_GeometryShader()
	{
		m_byteCode = nullptr;
	}

	void Directx11_GeometryShader::setCode(const char* code)
	{
		m_code = code;
	}

	void Directx11_GeometryShader::create(Context* context)
	{
		ID3D11Device* device = GetDevice((Directx11_Context*)context);
		ID3DBlob* ErrorMessage = NULL;
		D3DCompile(m_code, strlen(m_code), nullptr, nullptr, nullptr, "main", "gs_5_0", 0, 0, &m_byteCode, &ErrorMessage);
		if (ErrorMessage) {
			std::cout << (const char*)ErrorMessage->GetBufferPointer() << std::endl;
			//ToDo:error
			ErrorMessage->Release();
		}
		device->CreateGeometryShader(m_byteCode->GetBufferPointer(), m_byteCode->GetBufferSize(), nullptr, &m_geometryShader);
	}

	void Directx11_GeometryShader::bind(Context* _context)
	{
		ID3D11DeviceContext* context = GetContext((Directx11_Context*)_context);
		context->GSSetShader(m_geometryShader, NULL, 0);
	}


	Directx11_ConstBuffer::Directx11_ConstBuffer(ID3D11Device* device, unsigned id, const void* data, size_t size, int bindflag)
	{
		REF_CLASS_BEGIN();
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = size;
		bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		bd.CPUAccessFlags = 0;
		D3D11_SUBRESOURCE_DATA InitData;
		ZeroMemory(&InitData, sizeof(InitData));
		InitData.pSysMem = data;
		device->CreateBuffer(&bd, &InitData, &m_constBuffer);
		m_id = id;
		m_flag = bindflag;
	}

	void Directx11_ConstBuffer::bind(Context* _context)
	{
		ID3D11DeviceContext* context = GetContext((Directx11_Context*)_context);
		if (m_flag & const_buffer_bind_vertex_shader) {
			context->VSSetConstantBuffers(m_id, 1, &m_constBuffer);
		}
		if (m_flag & const_buffer_bind_pixel_shader) {
			context->PSSetConstantBuffers(m_id, 1, &m_constBuffer);
		}
		if (m_flag & const_buffer_bind_geometry_shader) {
			context->GSSetConstantBuffers(m_id, 1, &m_constBuffer);
		}
	}

	Directx11_BlendState::Directx11_BlendState()
	{
		REF_CLASS_BEGIN();
		m_blendDesc.AlphaToCoverageEnable = false;
		m_blendDesc.IndependentBlendEnable = false;
		m_blendDesc.RenderTarget[0].BlendEnable = true;
		m_blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
		m_blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
		m_blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
		m_blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ZERO;
		m_blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ONE;
		m_blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
		m_blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	}

	void Directx11_BlendState::alphaToCoverage(bool enable)
	{
		m_blendDesc.AlphaToCoverageEnable = enable;
	}

	void Directx11_BlendState::independentBlend(bool enable)
	{
		m_blendDesc.IndependentBlendEnable = enable;
	}

	void Directx11_BlendState::blendEnable(bool enable, int index)
	{
		m_blendDesc.RenderTarget[index].BlendEnable = enable;
	}
	D3D11_BLEND FCTtoD3D11BLEND(blend_factor_t src) {
		switch (src)
		{
		case blend_factor_t::blend_factor_zero:
		return D3D11_BLEND_ZERO;
		case blend_factor_t::blend_factor_one:
		return D3D11_BLEND_ONE;
		case blend_factor_t::blend_factor_src_color:
		return D3D11_BLEND_SRC_COLOR;
		case blend_factor_t::blend_factor_inv_src_color:
			return D3D11_BLEND_INV_SRC_COLOR;
		case blend_factor_t::blend_factor_src_alpha:
			return D3D11_BLEND_SRC_ALPHA;
		case blend_factor_t::blend_factor_inv_src_alpha:
			return D3D11_BLEND_INV_SRC_ALPHA;
		case blend_factor_t::blend_factor_dest_alpha:
			return D3D11_BLEND_DEST_ALPHA;
		case blend_factor_t::blend_factor_inv_dest_alpha:
			return D3D11_BLEND_INV_DEST_ALPHA;
		case blend_factor_t::blend_factor_dest_color:
			return D3D11_BLEND_DEST_COLOR;
			break;
		case blend_factor_t::blend_factor_inv_dest_color:
			return D3D11_BLEND_INV_DEST_COLOR;
			break;
		case blend_factor_t::blend_factor_src_alpha_sat:
			return D3D11_BLEND_SRC_ALPHA_SAT;
		case blend_factor_t::blend_factor_blend_factor:
			return D3D11_BLEND_BLEND_FACTOR;
		case blend_factor_t::blend_factor_inv_blend_factor:
			return D3D11_BLEND_INV_BLEND_FACTOR;
		default:
			// todo: error
			break;
		}
	}
	void Directx11_BlendState::srcBlendRGB(blend_factor_t src, int index)
	{
		m_blendDesc.RenderTarget[index].SrcBlend = FCTtoD3D11BLEND(src);
	}

	void Directx11_BlendState::destBlendRGB(blend_factor_t dest, int index)
	{
		m_blendDesc.RenderTarget[index].DestBlend = FCTtoD3D11BLEND(dest);
	}
	inline D3D11_BLEND_OP FCTtoD3D11BLENDOP(blend_op_t src) {
		switch (src)
		{
		case blend_op_t::blend_op_add:
			return D3D11_BLEND_OP_ADD;
		case blend_op_t::blend_op_subtract:
			return D3D11_BLEND_OP_SUBTRACT;
		case blend_op_t::blend_op_rev_subtract:
			return D3D11_BLEND_OP_REV_SUBTRACT;
		case blend_op_t::blend_op_min:
			return D3D11_BLEND_OP_MIN;
		case blend_op_t::blend_op_max:
			return D3D11_BLEND_OP_MAX;
		default:
			// todo: error
			break;
		}
	}
	void Directx11_BlendState::blendOpRGB(blend_op_t op, int index)
	{
		m_blendDesc.RenderTarget[index].BlendOp = FCTtoD3D11BLEND_OP(op);
	}

	void Directx11_BlendState::srcBlendAlpha(blend_factor_t src, int index)
	{
		m_blendDesc.RenderTarget[index].SrcBlendAlpha = FCTtoD3D11BLEND(src);
	}

	void Directx11_BlendState::destBlendAlpha(blend_factor_t dest, int index)
	{
		m_blendDesc.RenderTarget[index].DestBlendAlpha = FCTtoD3D11BLEND(dest);
	}

	void Directx11_BlendState::blendOpAlpha(blend_op_t op, int index)
	{
		m_blendDesc.RenderTarget[index].BlendOpAlpha = FCTtoD3D11BLEND_OP(op);
	}

	void Directx11_BlendState::writeMask(char mask)
	{
		m_blendDesc.RenderTarget[0].RenderTargetWriteMask = mask;
	}

	void Directx11_BlendState::create(ID3D11Device* device)
	{
		device->CreateBlendState(&m_blendDesc, &m_blendState);
	}

	void Directx11_BlendState::bind(Context* _context)
	{
		ID3D11DeviceContext* context = GetContext((Directx11_Context*)_context);
		context->OMSetBlendState(m_blendState, NULL, 0xFFFFFFFF);
	}


	Directx11_DepthStencilState::Directx11_DepthStencilState()
	{
		REF_CLASS_BEGIN();
		m_desc.DepthEnable = true;
		m_desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		m_desc.DepthFunc = D3D11_COMPARISON_LESS;
		m_desc.StencilEnable = true;
		m_desc.StencilReadMask = D3D11_DEFAULT_STENCIL_READ_MASK; //0xff
		m_desc.StencilWriteMask = D3D11_DEFAULT_STENCIL_WRITE_MASK;//0xff
		m_desc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		m_desc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
		m_desc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
		m_desc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
		m_desc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		m_desc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
		m_desc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
		m_desc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
		m_stencil = 0;
	}

	void Directx11_DepthStencilState::setRefStencil(unsigned char stencil)
	{
		m_stencil = stencil;
	}

	void Directx11_DepthStencilState::setDepthEnable(bool enable)
	{
		m_desc.DepthEnable = enable;
	}

	void Directx11_DepthStencilState::setDepthWrite(bool write)
	{
		m_desc.DepthWriteMask = write ? D3D11_DEPTH_WRITE_MASK_ALL : D3D11_DEPTH_WRITE_MASK_ZERO;
	}

	void Directx11_DepthStencilState::setDepthFunc(depth_func_t func)
	{
		switch (func)
		{
		case FCT::depth_func_less:
			m_desc.DepthFunc = D3D11_COMPARISON_LESS;
			break;
		case FCT::depth_func_less_equal:
			m_desc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
			break;
		case FCT::depth_func_greater:
			m_desc.DepthFunc = D3D11_COMPARISON_GREATER;
			break;
		case FCT::depth_func_greater_equal:
			m_desc.DepthFunc = D3D11_COMPARISON_GREATER_EQUAL;
			break;
		case FCT::depth_func_equal:
			m_desc.DepthFunc = D3D11_COMPARISON_EQUAL;
			break;
		case FCT::depth_func_notequal:
			m_desc.DepthFunc = D3D11_COMPARISON_NOT_EQUAL;
			break;
		case FCT::depth_func_always:
			m_desc.DepthFunc = D3D11_COMPARISON_ALWAYS;
			break;
		case FCT::depth_func_never:
			m_desc.DepthFunc = D3D11_COMPARISON_NEVER;
			break;
		default:
			//ToDo:error or warning
			break;
		}
	}

	void Directx11_DepthStencilState::setStencilEnable(bool enable)
	{
		m_desc.StencilEnable = enable;
	}

	void Directx11_DepthStencilState::setStencilWriteMask(unsigned mask)
	{
		m_desc.StencilWriteMask = mask;
	}

	void Directx11_DepthStencilState::setStencilReadMask(unsigned mask)
	{
		m_desc.StencilReadMask = mask;
	}
	D3D11_COMPARISON_FUNC FCTStencilFuncToDirectx11StencilFunc(stencil_func_t func) {
		switch (func) {
		case stencil_func_never:
			return D3D11_COMPARISON_NEVER;
		case stencil_func_less:
			return D3D11_COMPARISON_LESS;
		case stencil_func_equal:
			return D3D11_COMPARISON_EQUAL;
		case stencil_func_less_equal:
			return D3D11_COMPARISON_LESS_EQUAL;
		case stencil_func_greater:
			return D3D11_COMPARISON_GREATER;
		case stencil_func_greater_equal:
			return D3D11_COMPARISON_GREATER_EQUAL;
		case stencil_func_notequal:
			return D3D11_COMPARISON_NOT_EQUAL;
		case stencil_func_always:
			return D3D11_COMPARISON_ALWAYS;
		default:
			//ToDo: error or warning
			return D3D11_COMPARISON_ALWAYS;
		}
	}
	void Directx11_DepthStencilState::setFrontFaceStencilFunc(stencil_func_t func)
	{
		m_desc.FrontFace.StencilFunc = FCTStencilFuncToDirectx11StencilFunc(func);
	}

	void Directx11_DepthStencilState::setBackFaceStencilFunc(stencil_func_t func)
	{
		m_desc.BackFace.StencilFunc = FCTStencilFuncToDirectx11StencilFunc(func);
	}
	D3D11_STENCIL_OP FCTStencilOpToDirectx11StencilOp(stencil_op_t op) {
		switch (op) {
		case stencil_op_keep:
			return D3D11_STENCIL_OP_KEEP;
		case stencil_op_zero:
			return D3D11_STENCIL_OP_ZERO;
		case stencil_op_replace:
			return D3D11_STENCIL_OP_REPLACE;
		case stencil_op_increment_saturate:
			return D3D11_STENCIL_OP_INCR_SAT;
		case stencil_op_decrement_saturate:
			return D3D11_STENCIL_OP_DECR_SAT;
		case stencil_op_invert:
			return D3D11_STENCIL_OP_INVERT;
		case stencil_op_increment:
			return D3D11_STENCIL_OP_INCR;
		case stencil_op_decrement:
			return D3D11_STENCIL_OP_DECR;
		default:
			//ToDo: error or warning
			return D3D11_STENCIL_OP_KEEP;
		}
	}
	void Directx11_DepthStencilState::setFrontFaceStencilPass(stencil_op_t op)
	{
		m_desc.FrontFace.StencilPassOp = FCTStencilOpToDirectx11StencilOp(op);
	}

	void Directx11_DepthStencilState::setBackFaceStencilPass(stencil_op_t op)
	{
		m_desc.BackFace.StencilPassOp = FCTStencilOpToDirectx11StencilOp(op);
	}

	void Directx11_DepthStencilState::setFrontFaceStencilFail(stencil_op_t op)
	{
		m_desc.FrontFace.StencilFailOp = FCTStencilOpToDirectx11StencilOp(op);
	}

	void Directx11_DepthStencilState::setBackFaceStencilFail(stencil_op_t op)
	{
		m_desc.BackFace.StencilFailOp = FCTStencilOpToDirectx11StencilOp(op);
	}

	void Directx11_DepthStencilState::setFrontFaceStencilFailDepth(stencil_op_t op)
	{
		m_desc.FrontFace.StencilFailOp = FCTStencilOpToDirectx11StencilOp(op);
	}

	void Directx11_DepthStencilState::setBackFaceStencilFailDepth(stencil_op_t op)
	{
		m_desc.BackFace.StencilFailOp = FCTStencilOpToDirectx11StencilOp(op);
	}

	void Directx11_DepthStencilState::create(ID3D11Device* device)
	{
		device->CreateDepthStencilState(&m_desc, &m_depthStencilState);
	}

	void Directx11_DepthStencilState::bind(Context* _context)
	{
		ID3D11DeviceContext* context = GetContext((Directx11_Context*)_context);
		if (m_depthStencilState) {
			context->OMSetDepthStencilState(m_depthStencilState, m_stencil);
			return;
		}
		ID3D11Device* device = GetDevice((Directx11_Context*)_context);
		this->create(device);
		return bind(_context);
	}

	Directx11_RasterizerState::Directx11_RasterizerState()
	{
		m_desc.FillMode = D3D11_FILL_SOLID;
		m_desc.CullMode = D3D11_CULL_BACK;
		m_desc.FrontCounterClockwise = FALSE;
		m_desc.DepthBias = 0;
		m_desc.SlopeScaledDepthBias = 0.0f;
		m_desc.DepthBiasClamp = 0.0f;
		m_desc.DepthClipEnable = TRUE;
		m_desc.ScissorEnable = FALSE;
		m_desc.MultisampleEnable = FALSE;
		m_desc.AntialiasedLineEnable = FALSE;
	}

	void Directx11_RasterizerState::setCullMode(cull_mode_t mode)
	{
		switch (mode)
		{
		case cull_mode_none:
			m_desc.CullMode = D3D11_CULL_NONE;
			break;
		case cull_mode_front:
			m_desc.CullMode = D3D11_CULL_FRONT;
			break;
		case cull_mode_back:
			m_desc.CullMode = D3D11_CULL_BACK;
			break;
		default:
			//ToDo: error or warning
			m_desc.CullMode = D3D11_CULL_BACK;
			break;
		}
	}

	void Directx11_RasterizerState::setFillMode(fill_mode_t mode)
	{
		switch (mode)
		{
		case fill_mode_solid:
			m_desc.FillMode = D3D11_FILL_SOLID;
			break;
		case fill_mode_wireframe:
			m_desc.FillMode = D3D11_FILL_WIREFRAME;
			break;
		default:
			//ToDo: error or warning
			m_desc.FillMode = D3D11_FILL_SOLID;
			break;
		}
	}

	void Directx11_RasterizerState::setFrontCounterClockwise(bool ccw)
	{
		m_desc.FrontCounterClockwise = ccw;
	}

	void Directx11_RasterizerState::setDepthClipEnable(bool enable)
	{
		m_desc.DepthClipEnable = enable;
	}

	void Directx11_RasterizerState::setDepthBias(float bias)
	{
		m_desc.DepthBias = bias;
	}

	void Directx11_RasterizerState::setDepthBiasClamp(float clamp)
	{
		m_desc.DepthBiasClamp = clamp;
	}

	void Directx11_RasterizerState::setSlopeScaledDepthBias(float slope)
	{
		m_desc.SlopeScaledDepthBias = slope;
	}

	void Directx11_RasterizerState::setScissorEnable(bool enable)
	{
		m_desc.ScissorEnable = enable;
	}

	void Directx11_RasterizerState::setMultisampleEnable(bool enable)
	{
		m_desc.MultisampleEnable = enable;
	}

	void Directx11_RasterizerState::setAntialiasedLineEnable(bool enable)
	{
		m_desc.AntialiasedLineEnable = enable;
	}

	void Directx11_RasterizerState::create(ID3D11Device* device)
	{
		device->CreateRasterizerState(&m_desc, &m_rasterizerState);
	}

	void Directx11_RasterizerState::create(Context* _context)
	{
		ID3D11Device* device = GetDevice((Directx11_Context*)_context);
		create(device);
	}

	void Directx11_RasterizerState::bind(Context* _context)
	{
		ID3D11DeviceContext* context = GetContext((Directx11_Context*)_context);
		context->RSSetState(m_rasterizerState);
	}
}
