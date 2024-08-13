class Directx11Interface{
protected:
	ID3D11Device* GetDevice(Directx11_Context*);
	ID3D11DeviceContext* GetContext(Directx11_Context*);
};


class Directx11_Vertex2dBuffer : public Vertex2dBuffer, public Directx11Interface {
public:
	Directx11_Vertex2dBuffer(ID3D11Device* device,Vertex2d* vertex,int vertexNum);
	~Directx11_Vertex2dBuffer();
	void bind(Context* context);
	int getVertexNum();
	ID3D11Buffer* m_vertexBuffer;
	int m_vertexNum;
};

class Directx11_Topology : public Topology, public Directx11Interface {
public:
	Directx11_Topology(shape_primitive_topology_t topology);
	void bind(Context* context);
	D3D11_PRIMITIVE_TOPOLOGY m_topology;
};

class Directx11_VertexShader : public VertexShader, public Directx11Interface {
public:
	Directx11_VertexShader(ID3D11Device* device, const char* shaderCode);
	~Directx11_VertexShader()
	{
		COM_RELEASE(m_vertexShader);
		COM_RELEASE(m_byteCode);
	}
	void bind(Context* _context);

private:
	ID3D11VertexShader* m_vertexShader;
	ID3DBlob* m_byteCode;
};

class Directx11_PixelShader : public PixelShader, public Directx11Interface {
public:
	Directx11_PixelShader(ID3D11Device* device, const char* shaderCode);
	~Directx11_PixelShader()
	{
		COM_RELEASE(m_pixelShader);
		COM_RELEASE(m_byteCode);
	}
	void bind(Context * _context);
private:
	ID3D11PixelShader* m_pixelShader;
	ID3DBlob* m_byteCode;
}; 

class Directx11_GeometryShader : public GeometryShader,public Directx11Interface {
public:
	Directx11_GeometryShader();
	~Directx11_GeometryShader()
	{
		COM_RELEASE(m_geometryShader);
		COM_RELEASE(m_byteCode);
	}
	void setCode(const char* code);
	void create(Context* context);
	void bind(Context* _context);
private:
	const char* m_code;
	ID3D11GeometryShader* m_geometryShader;
	ID3DBlob* m_byteCode;
};
class Directx11_ConstBuffer : public ConstBuffer, public Directx11Interface {
public:
	Directx11_ConstBuffer(ID3D11Device* device, unsigned id, const void* data, size_t size, int bindflag);
	~Directx11_ConstBuffer();

	void bind(Context* _context);
private:
	ID3D11Buffer* m_constBuffer;
	unsigned m_flag;
	unsigned m_id;
};
class Directx11_BlendState : public BlendState, public Directx11Interface {
public:
	Directx11_BlendState();
	void alphaToCoverage(bool enable);
	void independentBlend(bool enable);
	void blendEnable(bool enable,int index = 0);
	void srcBlendRGB(blend_factor_t src,int index = 0);
	void destBlendRGB(blend_factor_t dest, int index = 0);
	void blendOpRGB(blend_op_t op, int index = 0);
	void srcBlendAlpha(blend_factor_t src, int index = 0);
	void destBlendAlpha(blend_factor_t dest, int index = 0);
	void blendOpAlpha(blend_op_t op, int index = 0);
	void writeMask(char mask = 0xf);// a b g r
	void create(ID3D11Device* device);
	void bind(Context* _context);
private:
	static void Directx11_BlendStateFirstBind(Directx11_BlendState* pThis, Context* context);
	static void Directx11_BlendStateBind(Directx11_BlendState* pThis, Context* context);
	void (*m_bindFunc)(Directx11_BlendState* pThis, Context* context);
	D3D11_BLEND_DESC m_blendDesc;
	ID3D11BlendState* m_blendState;
};

class Directx11_DepthStencilState : public DepthStencilState, public Directx11Interface {
public:
	Directx11_DepthStencilState();
	void setRefStencil(unsigned char stencil);
	void setDepthEnable(bool enable);
	void setDepthWrite(bool write);
	void setDepthFunc(depth_func_t func);
	void setStencilEnable(bool enable);
	void setStencilWriteMask(unsigned mask);
	void setStencilReadMask(unsigned mask);
	void setFrontFaceStencilFunc(stencil_func_t func);
	void setBackFaceStencilFunc(stencil_func_t func);
	void setFrontFaceStencilPass(stencil_op_t op);
	void setBackFaceStencilPass(stencil_op_t op);
	void setFrontFaceStencilFail (stencil_op_t op);
	void setBackFaceStencilFail(stencil_op_t op);
	void setFrontFaceStencilFailDepth(stencil_op_t op);
	void setBackFaceStencilFailDepth(stencil_op_t op);
	void create(ID3D11Device* device);
	void bind(Context* _context);
private:
	unsigned char m_stencil;
	D3D11_DEPTH_STENCIL_DESC m_desc;
	ID3D11DepthStencilState* m_depthStencilState;
};

class Directx11_RasterizerState : public RasterizerState, public Directx11Interface {
public:
	Directx11_RasterizerState();
	void setCullMode(cull_mode_t mode);
	void setFillMode(fill_mode_t mode);
	void setFrontCounterClockwise(bool ccw);
	void setDepthClipEnable(bool enable);
	void setDepthBias(float bias);
	void setDepthBiasClamp(float clamp);
	void setSlopeScaledDepthBias(float slope);
	void setScissorEnable(bool enable);
	void setMultisampleEnable(bool enable);
	void setAntialiasedLineEnable(bool enable);
	void create(ID3D11Device* device);
	void create(Context* _context);
	void bind(Context* _context);
	
private:
	ID3D11RasterizerState* m_rasterizerState;
	D3D11_RASTERIZER_DESC m_desc;
};

class Directx11_SamplerState : public SamplerState, public Directx11Interface {
public:
	Directx11_SamplerState();
	void setFilter(texture_filter_t filter);
	void setAddressU(texture_address_mode_t address);
	void setAddressV(texture_address_mode_t address);
	void setAddressW(texture_address_mode_t address);
	void setMipLODBias(float bias);
	void setMaxAnisotropy(unsigned int max);
	void setComparisonFunc(comparison_func_t func);
	void setMinLod(float min);
	void setMaxLod(float max);
	void setBorderColor(Color color);
	void create(Context* context);
	void bind(Context* _context);
private:
	ID3D11SamplerState* m_samplerState = {};
	D3D11_SAMPLER_DESC m_desc;
};