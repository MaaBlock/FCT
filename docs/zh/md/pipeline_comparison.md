# 渲染管线类型对比 {#pipeline_comparison}

本文档详细对比 MQEngine 中支持的三种渲染管线类型，帮助开发者理解各自的特点、适用场景和性能特征。

## 目录
- \ref pipeline_overview "管线概览"
- \ref traditional_pipeline_detail "传统光栅化管线详解"
- \ref meshshader_pipeline_detail "MeshShader管线详解"
- \ref raytracing_pipeline_detail "光线追踪管线详解"
- \ref pipeline_comparison_table "管线对比表"
- \ref usage_recommendations "使用建议"

---

## 管线概览 {#pipeline_overview}

MQEngine 支持三种主要的渲染管线类型，每种都有其独特的优势和适用场景：

| 管线类型 | 主要特点 | 适用场景 |
|---------|---------|---------|
| 传统光栅化管线 | 成熟稳定，硬件支持广泛 | 实时渲染，游戏开发 |
| MeshShader管线 | 几何处理灵活，支持GPU驱动渲染 | 复杂几何，程序化生成 |
| 光线追踪管线 | 物理准确，真实光照 | 高质量渲染，离线渲染 |

---

## 传统光栅化管线详解 {#traditional_pipeline_detail}

### 概念定义
传统光栅化管线是最经典的GPU渲染管线，基于固定的几何处理流程，通过顶点着色器、几何着色器（可选）、光栅化和片段着色器完成渲染。

### 流程图