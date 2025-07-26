#ifndef FCT_MESH_HPP
#define FCT_MESH_HPP
namespace FCT {
    template <typename IndexType>
    void StaticMesh<IndexType>::create()
    {
        m_gpuVertex = m_ctx->createResource<RHI::VertexBuffer>();
        m_gpuVertex->vertexBuffer(m_cpuVertex);
        m_gpuVertex->create();
        m_gpuVertex->updataBuffer();

        if (!m_cpuIndices.empty()) {
            m_gpuIndex = m_ctx->createResource<RHI::IndexBuffer>();
            m_gpuIndex->indexBuffer(m_cpuIndices);
            m_gpuIndex->create();
            m_gpuIndex->updataBuffer();
        }
    }

    template <typename IndexType>
    void DynamicMesh<IndexType>::create()
    {
        m_gpuVertex = m_ctx->createResource<RHI::VertexBuffer>();
        m_gpuVertex->vertexBuffer(m_cpuVertex);
        m_gpuVertex->updateFrequency(UpdateFrequency::PerFrame);

        if (m_vertexCapacity > m_cpuVertex->getVertexCount()) {

        } else {
            m_vertexCapacity = m_cpuVertex->getVertexCount();
        }
        m_gpuVertex->reserve(m_vertexCapacity);

        m_gpuVertex->create();
        m_gpuVertex->updataBuffer();

        if (!m_cpuIndices.empty() || m_indexCapacity > 0) {
            m_gpuIndex = m_ctx->createResource<RHI::IndexBuffer>();
            m_gpuIndex->indexBuffer(m_cpuIndices);
            m_gpuIndex->updateFrequency(UpdateFrequency::PerFrame);

            if (m_indexCapacity > m_cpuIndices.size()) {
            } else {
                m_indexCapacity = m_cpuIndices.size();
            }
            m_gpuIndex->reserve(m_indexCapacity);

            m_gpuIndex->create();
            m_gpuIndex->updataBuffer();
        }
    }
}
#endif