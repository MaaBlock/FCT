class CreateContextFactory {
public:
	virtual FCT::RasterizerState* RasterizerState() = 0;
	virtual FCT::GeometryShader* GeometryShader() = 0;
	virtual FCT::DepthStencilState* DepthStencilState() = 0;
};

class Context : public RefCounted {
public:
	CreateContextFactory* createResouce;
	virtual void create() = 0;
	virtual Image* createImage(int w, int h) = 0;
	virtual void setTarget(Image* img) = 0;
	virtual void draw(Shape* shape, float x, float y) = 0;
	virtual void flush() = 0;
	virtual void writeIn(Color* buffer) = 0;
	virtual void writeIn(Image* img, Color* buffer) = 0;
	virtual void clear(float r, float g, float b, float a) = 0;
	virtual Vertex2dBuffer* createVertex2dBuffer(Vertex2d* vertex, int vertexNum) = 0;
	virtual ConstBuffer* createConstBuffer(unsigned id, void* data, int biteSize, int type) = 0;
	virtual Topology* createToplogy(shape_primitive_topology_t) = 0;
	virtual PixelShader* createPixelShader(const char* code) = 0;
	virtual VertexShader* createVertexShader(const char* code) = 0;
	virtual void setDeafultResouce(ContextResouce* resouce) = 0;
	virtual void setDeafultResouce(context_resouce_t resoutType, ContextResouce* resouce) = 0;
};