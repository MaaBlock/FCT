#ifndef UNIFORMWRAPPER_H
#define UNIFORMWRAPPER_H
#include "./Uniform.h"
namespace FCT {
    class Context;
    namespace RHI {
        class UniformBuffer;
        class ConstBuffer;
    }

    struct Uniform
    {
    public:
        Uniform();
        Uniform(Uniform&& other) noexcept;
        Uniform& operator=(Uniform&& other) noexcept;
        Uniform(FCT::Context* ctx, const FCT::ConstLayout& layout);
        ~Uniform();
        template<typename T>
        void setValue(const char* name, const T& value)
        {
            m_uniformBuffer->setValue(name, value);
        }
        template<typename T>
        void setValue(UniformType type, const T& value)
        {
            m_uniformBuffer->setValue(type, value);
        }
        void update();
        operator FCT::RHI::ConstBuffer*() const;
        FCT::RHI::ConstBuffer* getConstBuffer() const;
    private:
        FCT::UniformBuffer* m_uniformBuffer;
        FCT::RHI::ConstBuffer* m_constBuffer;
    };
}
#endif //UNIFORMWRAPPER_H
