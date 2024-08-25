
//
// Created by DEEP on 2024/8/7.
//

#include "hander.h"


namespace FCT {
   EGLDisplay GLES3_0_Context::EglDispaly = NULL;
   void GLES3_0_Context::create(){

   }
   Image* GLES3_0_Context::createImage(int w, int h) {
       
   }
   void GLES3_0_Context::setTarget(FCT::Image *img) {
        if (getContextType()) {

        }
   }
   void GLES3_0_Context::setTarget(FCT::Window *wnd) {
       if (getContextType()){
           return;
       }
       EglDispaly = eglGetDisplay(EGL_DEFAULT_DISPLAY);
       GLES3_0_Image::Init(EglDispaly);
       GLES3_0_Image* image = new GLES3_0_Image(this,(Android_Window*)wnd);
       //ToDo:已创建完surface

   }

    context_t GLES3_0_Context::getContextType() {
        return context_window;
    }

    GLES3_0_Context *GLES3_0_Context::Init() {
        GLES3_0_Context* ret = new GLES3_0_Context;
        ret->m_contextType = context_window;
        return ret;
    }

    void GLES3_0_Context::draw(Shape *shape, float x, float y) {

    }

    void GLES3_0_Context::writeIn(Color *buffer) {

    }

    void GLES3_0_Context::writeIn(Image *img, Color *buffer) {

    }

    void GLES3_0_Context::clear(float r, float g, float b, float a) {

    }

    Vertex2dBuffer* GLES3_0_Context::createVertex2dBuffer(Vertex2d* vertex, int vertexNum)
    {
        return nullptr;
    }

    ConstBuffer* GLES3_0_Context::createConstBuffer(unsigned id, void* data, int biteSize, int type)
    {
        return nullptr;
    }

    Topology* GLES3_0_Context::createToplogy(shape_primitive_topology_t)
    {
        return nullptr;
    }

    PixelShader* GLES3_0_Context::createPixelShader(const char* code)
    {
        return nullptr;
    }

    VertexShader* GLES3_0_Context::createVertexShader(const char* code)
    {
        return nullptr;
    }

    void GLES3_0_Context::setDeafultResouce(ContextResouce* resouce)
    {
    }

    void GLES3_0_Context::setDeafultResouce(context_resouce_t resoutType, ContextResouce* resouce)
    {
    }

    EGLDisplay GLES3_0_Context::getDisplay() {
        return EglDispaly;
    }

    EGLContext GLES3_0_Context::getContext() {
        return EglDispaly;
    }

    Image *GLES3_0_Context::getTarget() {
        return nullptr;
    }

    void GLES3_0_Context::flush() {

    }

    void GLES3_0_Context::setTexture(Image *img) {

    }

    Image *GLES3_0_Context::createImage() {
        return nullptr;
    }

    Texture *GLES3_0_Context::createTexture() {
        return nullptr;
    }

    void GLES3_0_Context::drawImage(Image *img, Pos2f dstPos, Pos2f srcPos, Pos2f size) {

    }


} // FCT