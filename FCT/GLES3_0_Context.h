class GLES3_0_CreateContextFactory : public CreateContextFactory{
public:

};
class GLES3_0_Context : public Context{
public:
    static GLES3_0_Context* Init();
    void create();
    Image* createImage(int w,int h);
    void setTarget(Image* img);

    void setTarget(Window* wnd);
    //内部函数，不允许调用

    Image* getTarget();
    context_t getContextType();
    void flush();
    EGLContext getContext();
    static EGLDisplay getDisplay();

    void draw(Shape *shape, float x, float y) override;

    void writeIn(Color *buffer) override;

    void writeIn(Image *img, Color *buffer) override;

    void clear(float r, float g, float b, float a) override;

private:
    context_t m_contextType;
    EGLContext m_eglContext;
    static EGLDisplay EglDispaly;

    // 通过 Context 继承
    Vertex2dBuffer* createVertex2dBuffer(Vertex2d* vertex, int vertexNum) override;
    ConstBuffer* createConstBuffer(unsigned id, void* data, int biteSize, int type) override;
    Topology* createToplogy(shape_primitive_topology_t) override;
    PixelShader* createPixelShader(const char* code) override;
    VertexShader* createVertexShader(const char* code) override;
    void setDeafultResouce(ContextResouce* resouce) override;
    void setDeafultResouce(context_resouce_t resoutType, ContextResouce* resouce) override;
};