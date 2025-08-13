# 顶点着色器详解
## 概述

顶点着色器（Vertex Shader）允许你对顶点进行变换和处理。

想象一下：
- 你有一个图形，它由很多个顶点组成
- 每个顶点都有自己的位置、颜色、纹理坐标等信息
- 顶点着色器就像一个工人，负责处理每一个顶点
- 它可以移动顶点位置、改变颜色、计算动画效果等
- 为每个顶点计算需要传递给下一阶段的数据

<b>简单来说</b>：顶点着色器决定了每个顶点的最终属性和位置，以及要传递给渲染管线下一阶段的信息。
> <b>FCT库说明</b>：在FCT中，你不需要从零开始写复杂的着色器代码，只需要定义数据结构和核心逻辑，FCT会帮你生成完整的着色器程序。

> <b>详细了解</b>：
> - [3D渲染下的各种变换](3d_transforms.md)
> - [一个3D物体是怎么被画出来的](how_3d_object_rendered.md)

## FCT中的顶点着色器

FCT库提供了 `VertexShader` 类来简化顶点着色器的创建和管理：
### 基本使用示例

```cpp
// 1. 定义顶点数据结构（告诉FCT顶点包含什么信息）
FCT::VertexLayout vertexLayout = {
FCT::VertexElement{FCT::VtxType::Position4f, "position"},  // 顶点位置
FCT::VertexElement{FCT::VtxType::Normal3f, "normal"},      // 法线向量
FCT::VertexElement{FCT::VtxType::TexCoord2f, "texCoord"},  // 纹理坐标
FCT::VertexElement{FCT::VtxType::Color4f, "color"},        // 顶点颜色
};

// 2. 定义输出数据结构（告诉FCT要传递给像素着色器什么信息）
FCT::PixelLayout pixelLayout = {
vertexLayout  // 把顶点数据原样传递
};

// 3. 定义变换矩阵（告诉FCT需要什么常量数据）
FCT::ConstLayout transformLayout = {
"transform",
FCT::ConstElement{FCT::ConstType::MVPMatrix, "mvp"},  // 模型-视图-投影矩阵
};

// 4. 创建顶点着色器
auto vs = m_ctx->createResource<ContextResource::VertexShader>();
vs->addLayout(0, vertexLayout);      // 设置输入数据格式
vs->pixelLayout(pixelLayout);        // 设置输出数据格式
vs->addUniform(transformLayout);     // 添加变换矩阵

// 5. 编写核心逻辑（只需要写最重要的变换代码）
vs->code(R"(
ShaderOut main(ShaderIn sIn) {
ShaderOut sOut;

    // 坐标变换：把3D坐标转换为屏幕坐标
    sOut.position = mul(mvp, sIn.position);
    
    // 传递其他属性
    sOut.normal = sIn.normal;
    sOut.texCoord = sIn.texCoord;
    sOut.color = sIn.color;
    
    return sOut;
}
)");

// 6. 创建着色器
vs->create();
```

### 布局系统详解

FCT使用声明式的布局系统来定义着色器的输入输出：

- <b>[VertexLayout](vertex_layout.md)</b> - 定义顶点数据的结构和格式
- <b>[PixelLayout](pixel_layout.md)</b> - 定义传递给像素着色器的数据
- <b>[ConstLayout](const_layout.md)</b> - 定义常量缓冲区的结构
- <b>[ResourceLayout](resource_layout.md)</b> - 定义纹理和采样器等资源

### 代码生成机制

FCT会根据布局自动生成：

1. <b>输入结构体</b> (`ShaderIn`) - 基于 `VertexLayout`
2. <b>输出结构体</b> (`ShaderOut`) - 基于 `PixelLayout`
3. <b>常量缓冲区</b> - 基于 `ConstLayout`
4. <b>资源绑定</b> - 基于 `ResourceLayout`

### 自定义着色器代码

用户只需要编写主要的变换逻辑：

```hlsl
ShaderOut main(ShaderIn sIn) {
ShaderOut sOut;

    // 基本属性传递
    sOut.color = sIn.color;
    sOut.texCoord = sIn.texCoord;
    sOut.normal = sIn.normal;
    
    // 坐标变换
    sOut.position = mul(mvp, sIn.position);
    
    // 自定义计算
    sOut.srcpos = sIn.position;
    sOut.shadowPos = mul(lightMvp, sIn.position);
    
    return sOut;
}
```

### 优势特点

- <b>类型安全</b>：编译时检查布局匹配
- <b>自动生成</b>：减少样板代码
- <b>灵活扩展</b>：支持自定义数据类型
- <b>性能优化</b>：自动优化内存布局

## 相关文档

- [着色器概述](shader_overview.md)
- [渲染管线概述](pipeline_comparison.md)
