
struct directx11_constbuffer2d {
	struct TargetSize {
		float w;
		float h;
	} targetsize ;
	struct ShapePos {
		float x;
		float y;
	} shapepos;
};//must be a multiple of 16
/*
D3D11 ERROR : ID3D11Device::CreateBuffer : The Dimensions are invalid.
For ConstantBuffers, marked with the D3D11_BIND_CONSTANT_BUFFER BindFlag, 
the ByteWidth(value = 8) must be a multiple of 16.
[STATE_CREATION ERROR #66: CREATEBUFFER_INVALIDDIMENSIONS]
*/

class Directx11_CreateContextFactory : public CreateContextFactory {
public:
	FCT::RasterizerState* RasterizerState() {
		return new Directx11_RasterizerState;
	}
	FCT::GeometryShader* GeometryShader() {
		return new Directx11_GeometryShader;
	}
	FCT::DepthStencilState* DepthStencilState() {
		return new Directx11_DepthStencilState;
	}
	FCT::BlendState* BlendState() {
		return new Directx11_BlendState;
	}
};

class Directx11_Context : public Context {
protected:
	static ID3DBlob* VertexShader2dCompiled;
	static ID3DBlob* PixelShader2dCompiled;
public:
	friend class Directx11Interface;
	static void Init();
	static ID3DBlob* compileVertexShader(const char* code);
	static ID3DBlob* compilePixelShader(const char* code);
	Directx11_Context();
	void clear(float r, float g, float b, float a);
	void create();
	Image* createImage(int w,int h);
	void setTarget(Image* img);
	void draw(Shape* shape,float x,float y);
	void draw(Object*,float x,float y,float z);
	void flush();

	void setTexture(Image* img);
	void writeIn(Color* buffer);
	void writeIn(Image* img,Color* buffer);
	Vertex2dBuffer* createVertex2dBuffer(Vertex2d* vertex, int vertexNum);
	ConstBuffer* createConstBuffer(unsigned id, void* data, int biteSize, int type);
	//Vertex3dBuffer* create3dBuffer(Vertex3d* vertex, int vertexNum);
	Topology* createToplogy(shape_primitive_topology_t);
	PixelShader* createPixelShader(const char* code);
	VertexShader* createVertexShader(const char* code);
	void setDeafultResouce(ContextResouce* resouce);
	void setDeafultResouce(context_resouce_t resoutType, ContextResouce* resouce);
private:
	Color* m_color;
	Image* m_target;
	ID3D11Device* m_device;
	ID3D11DeviceContext* m_context;
	ID3D11Buffer* m_vertexBuffer;
	ID3D11Buffer* m_indexBuffer;
	ID3D11InputLayout* m_input2dLayout;
	ID3D11VertexShader* m_vertexShader2d;
	ID3D11PixelShader* m_pixelShader2d;
	ID3D11InputLayout* m_input3dLayout;
	ID3D11VertexShader* m_vertexShader3d;
	ID3D11PixelShader* m_pixelShader3d;
	ID3D11SamplerState* m_samplerState;
	ID3D11Buffer* m_constBuffer2d;
	Directx11_BlendState* m_nullBlendState;
	Directx11_BlendState* m_blendState = NULL;
	Directx11_RasterizerState* m_rasterizerState;
	Directx11_GeometryShader* m_geometryShader;
	Directx11_DepthStencilState* m_depthStencilState;
};