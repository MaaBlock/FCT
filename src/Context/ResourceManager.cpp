//
// Created by Administrator on 2025/7/28.
//
#include "ResourceManager.h"

#include "MutilBufferImage.h"
#include "SingleBufferImage.h"

#include "./Context.h"
#include "../Base/TokenGraph.h"
#include "../RHI/Swapcain.h"
#include "../UI/Window.h"

namespace FCT {
    std::string WindowToToken(Window* wnd)
    {
        return SwapchainToToken(wnd->swapchain());
    }

    std::string SwapchainToToken(RHI::Swapchain* swapchain)
    {
        return "Swapchain_" + std::to_string(reinterpret_cast<uintptr_t>(swapchain));
    }

    ImageSaved::ImageSaved(RHI::Swapchain* swapchain)
    {
        img = swapchain->image();
    }

    ImageSaved::ImageSaved(ImageSaved* denpendency)
    {
        mutilBuffer = denpendency->mutilBuffer;
    }

    ResourceManager::ResourceManager(Context* ctx)
    {
        m_context = ctx;
        m_context->subscribe<ContextEvent::WindowBound>([this](const ContextEvent::WindowBound& env)
        {
            registerWindow(env.window);
        });
        for (auto wnd : m_context->getBindWindows())
        {
            registerWindow(wnd);
        }
    }

    Image* ResourceManager::allocateImage(std::string name, Window* dependency,ImageDesc desc)
    {
        return allocateImage(name, WindowToToken(dependency),desc);
    }

    Image* ResourceManager::allocateImage(std::string name, std::string dependency,ImageDesc desc)
    {
        auto saved = m_dependencyGraph[name]->value;
        auto ret = ImageSaved(saved);
        if (ret.mutilBuffer)
        {
            auto savedImg = dynamic_cast<MutilBufferImage*>(saved.img);
            auto img = m_resourceDevice->createResource<MutilBufferImage>();
            img->samples(savedImg->samples());
            img->format(desc.format);
            img->width(savedImg->width());
            img->height(savedImg->height());
            img->as(desc.usage);
            img->create();
        }  else
        {
            auto savedImg = dynamic_cast<SingleBufferImage*>(saved.img);
            auto img = m_resourceDevice->createResource<SingleBufferImage>();
            img->samples(savedImg->samples());
            img->format(desc.format);
            img->width(savedImg->width());
            img->height(savedImg->height());
            img->as(desc.usage);
            img->create();
        }
        m_dependencyGraph[name] = {
            ret,
            {dependency},
            {},
        };
        return ret.img;
    }

    void ResourceManager::registerWindow(Window* wnd)
    {
        std::string token = WindowToToken(wnd);
        RHI::Swapchain* swapchain = wnd->swapchain();
        swapchain->subscribe<SwapchainEvent::Recreate>([this](const SwapchainEvent::Recreate& env)
        {
            resizeSub(
                SwapchainToToken(env.swapchain),
                env.width,
                env.height);
        });
        m_dependencyGraph[token] = {
            ImageSaved(swapchain),
            {},
            {},
        };
    }

    void ResourceManager::resizeSub(std::string token, int width, int height)
    {
        m_dependencyGraph.visitBFS(token,[width,height](ImageSaved img)
        {
            img.img->resize(width,height);
        },false);
    }

    void ResourceManager::resize(std::string token, int width, int height)
    {
        m_dependencyGraph.visitBFS(token,[width,height](ImageSaved img)
        {
            img.img->resize(width,height);
        },true);
    }


}
//todo:
namespace FCT
{
    void ResourceManager::resizeImage(std::string name, int width, int height)
    {
    }

    Image* ResourceManager::allocateTarget(std::string target)
    {
        return nullptr;
    }
}