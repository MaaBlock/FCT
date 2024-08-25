
class GLES3_0_Image : public Image{
public:
    static void Init(EGLDisplay display);
    GLES3_0_Image(Context* context);

    EGLSurface getSurface();
    void setSurface(EGLSurface surface);

    //内部函数，禁止调用
    GLES3_0_Image(Context* context,Android_Window* window);


    image_t getImageType();

    int getWidth() override;

    int getHeight() override;

    void setSize(unsigned int width, unsigned int height) override;

    int create() override;

    int msaaEnable(bool enable, unsigned int count) override;

    static EGLint nEGLConfigs;
    static EGLConfig EGLConfig;
private:
    image_t m_imageType;
    EGLSurface m_surface;
};