//
// Created by Administrator on 2025/3/16.
//
#include "../FCTAPI.h"
#include "Context.h"
#include "RenderGraph.h"


namespace FCT {
    void Context::nextFrame() {
        m_nextFrame = true;
    }

    void Context::currentFlush() {
        m_currentFlush = true;
    }


    Image* Context::loadTexture(const std::string& filename)
    {
        auto data = m_imageLoader->load(filename);
        SingleBufferImage* image = new SingleBufferImage(this);
        image->width(data.width);
        image->height(data.height);

        bool isSRGB = true;


        Format format;
        switch (data.channels) {
        case 1:
            format = Format::R8_UNORM;
            break;
        case 2:
            format = Format::R8G8_UNORM;
            break;
        case 3:
            format = isSRGB ? Format::R8G8B8A8_SRGB : Format::R8G8B8_UNORM;
            break;
        case 4:
            format = isSRGB ? Format::R8G8B8A8_SRGB : Format::R8G8B8A8_UNORM;
            break;
        default:
            ferr << "Unsupported number of channels: " << data.channels << std::endl;
            format = isSRGB ? Format::R8G8B8A8_SRGB : Format::R8G8B8A8_UNORM;
            break;
        }

        image->format(format);
        image->as(ImageUsage::Texture);
        image->initData(data.data.data(), data.data.size());
        image->create();
        return image;
    }


    void Context::swapQueue() {
        //std::swap(m_pushQueue,m_submitQueue);

    }


    Context::Context(Runtime* runtime)
    {
        m_resourceManager = nullptr;
        m_defaultGraph = new OldRenderGraph(this);
        m_currentGraph = m_defaultGraph;
        m_currentGraph->addRef();
        m_compiler = nullptr;
        m_ctxRunning = true;
        //m_flushWnd = nullptr;
        m_nextFrame = false;
        m_currentFlush = true;
        bool isInited = false;
        m_submitThread = std::thread([this,&isInited]
        {
            m_submitThreadId = std::this_thread::get_id();
            isInited = true;
            submitThread();
        });
        FCT_WAIT_FOR(isInited);
        m_ticker = std::bind(&Context::defaultTick,this);
        createCompiler();
        m_generator = new ShaderGenerator();
        m_frameIndex = 0;
        m_maxFrameInFlight = 3;
        m_imageLoader = runtime->createImageLoader();
        m_modelLoader = runtime->createModelLoader();
        m_submitTickers[RenderGraphSubmitTickerName] = {
            [this]()
            {
                m_currentGraph->updateFrameIndices();
                m_currentGraph->checkAndUpdateResourceSizes();
                m_currentGraph->updateResource();
            },
            {},
            {
                RenderGraphExcutePassSubmitTickerName
            }
        };
        m_submitTickers[RenderGraphExcutePassSubmitTickerName] = {
            [this]()
            {
                ScopeTimer submitCmdAndWaitUploadTimer("submitCmdAndWaitUpload");
                auto cmdBuf = getCmdBuf(m_bindWindows[0], 0);
                cmdBuf->reset();
                cmdBuf->begin();
                excutePasses(cmdBuf);
                cmdBuf->end();
                cmdBuf->submit();
            },
            {},
            {
                SwapBufferSubmitTicker
            }
        };
        m_submitTickers[SwapBufferSubmitTicker] = {
            [this]()
            {
                std::this_thread::yield();
                {
                    ScopeTimer waitGpuTimer("waitGpu");
                    swapBuffers();
                }
            },
            {},
            {}
        };
        m_submitTickers.update();
        m_syncTickers[RenderGraphSyncTicker_SwapJobQueueName] =
            {
                [this]()
                {
                    m_currentGraph->swapJobQueue();
                },
            {InnerSync::CheckRecreateSwapchainSync},
            {}
            };
        m_syncTickers[InnerSync::CheckRecreateSwapchainSync] =
            {
            [this]()
            {
                for (auto& window : m_bindWindows)
                {
                    window->swapchain()->sync();
                }
            },
            {},
            {InnerSync::AdvanceFrameIndex}
            };
        m_syncTickers[InnerSync::AdvanceFrameIndex] =
            {
            [this]()
            {
                advanceLogicFrame();
                advanceSubmitFrame();
            },
            {},
            {}
            };
        m_syncTickers.update();
    }

    Context::~Context() {
        m_ctxRunning = false;
        m_currentGraph->release();
        m_defaultGraph->release();
        m_submitThread.join();
    }

    StaticMesh<uint32_t>* Context::createMesh(const ModelMesh* modelMesh, const VertexLayout& layout)
    {
        if (!modelMesh) {
            return nullptr;
        }

        StaticMesh<uint32_t>* mesh = new StaticMesh<uint32_t>(this, layout);
        VertexBuffer* vertexBuffer = mesh->getVertexBuffer();
        vertexBuffer->resize(modelMesh->vertices.size());
        for (uint32_t i = 0; i < modelMesh->vertices.size(); ++i) {
            const auto& modelVertex = modelMesh->vertices[i];
            Vertex vertex = (*vertexBuffer)[i];

            for (size_t j = 0; j < layout.getElementCount(); ++j) {
                const VertexElement& element = layout.getElement(j);
                setVertexAttributeFromModel(vertex, j, element, modelVertex);
            }
        }

        std::vector<uint32_t> indices = modelMesh->indices;
        mesh->setIndices(indices);

        mesh->create();

        return mesh;
    }

    StaticMesh<uint32_t>* Context::loadMesh(const std::string& filename, const std::string& meshName,
                                            const VertexLayout& layout)
    {
        auto md = m_modelLoader->loadModel(filename);
        auto mMesh =  md->findMesh(meshName);
        return createMesh(mMesh,layout);
    }
}
