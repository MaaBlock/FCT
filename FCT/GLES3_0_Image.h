
class GLES3_0_Image : public Image{
public:
    static void Init(EGLDisplay display);
    GLES3_0_Image(Context* context);

    EGLSurface getSurface();
    void setSurface(EGLSurface surface);

    //�ڲ���������ֹ����
    GLES3_0_Image(Context* context,Android_Window* window);


    image_t getImageType();

    int getWidth() override;

    int getHeight() override;

    static EGLint nEGLConfigs;
    static EGLConfig EGLConfig;
private:
    image_t m_imageType;
    EGLSurface m_surface;
};