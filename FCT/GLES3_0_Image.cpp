
#include "hander.h"


namespace FCT{
    EGLConfig GLES3_0_Image::EGLConfig = NULL;
    EGLint GLES3_0_Image::nEGLConfigs = NULL;
    void GLES3_0_Image::Init(EGLDisplay display) {
        const EGLint attribs[] = {
                EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT, // request OpenGL ES 2.0
                EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
                EGL_BLUE_SIZE, 32,
                EGL_GREEN_SIZE, 32,
                EGL_RED_SIZE, 32,
                EGL_DEPTH_SIZE, 24,
                EGL_NONE
        };
        eglChooseConfig(display, attribs, &EGLConfig, 1, &nEGLConfigs);
    }
    GLES3_0_Image::GLES3_0_Image(Context* pContext,Android_Window* window) {
        GLES3_0_Context* context = (GLES3_0_Context*)pContext;
        m_surface = eglCreateWindowSurface(context->getDisplay(),
                                           EGLConfig,
                                           window->getNativeWindow(),
                                           NULL);
        m_imageType = image_type_window;
        //ToDo:已创建完surface

    }
    EGLSurface GLES3_0_Image::getSurface() {
        return m_surface;
    }
    void GLES3_0_Image::setSurface(EGLSurface surface) {
        m_surface = surface;
    }

    image_t GLES3_0_Image::getImageType() {
        return m_imageType;
    }

    int GLES3_0_Image::getWidth() {
        return 0;
    }

    int GLES3_0_Image::getHeight() {
        return 0;
    }

    void GLES3_0_Image::setSize(unsigned int width, unsigned int height) {

    }

    int GLES3_0_Image::create() {
        return 0;
    }

    int GLES3_0_Image::msaaEnable(bool enable, unsigned int count) {
        return 0;
    }

}