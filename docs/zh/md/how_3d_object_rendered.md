# 一个3D物体是怎么被画出来的

当你在屏幕上看到一个3D物体时，它实际上经历了一个复杂的渲染过程。这个过程将3D空间中的几何数据转换为屏幕上的2D像素。

## 渲染管线流程

一个3D物体从数据到屏幕显示，需要经过以下几个主要阶段：

\dot
digraph rendering_pipeline {
rankdir=TB;

    graph [fontname="SimHei", charset="UTF-8"];
    node [shape=box, style=filled, fontname="SimHei"];
    edge [fontname="SimHei"];

    A [label="加载3D模型", fillcolor=lightblue];
    B [label="变换到屏幕坐标", fillcolor=yellow];
    C [label="图元装配与裁剪", fillcolor=lightgreen];
    D [label="视口变换", fillcolor=lightcyan];
    E [label="光栅化", fillcolor=lightcoral];
    F [label="计算颜色", fillcolor=orange];
    G [label="深度测试", fillcolor=lightpink];
    H [label="混合", fillcolor=lightyellow];
    I [label="输出", fillcolor=lightgray];
    
    A -> B;
    B -> C;
    C -> D;
    D -> E;
    E -> F;
    F -> G;
    G -> H;
    H -> I;
}
\enddot

## 详细流程

## 详细流程

### 1. 加载3D模型
3D物体首先以数字形式存在，一般包含：
- 顶点坐标（位置信息）
- 顶点属性（颜色、法线、纹理坐标等）
- 索引信息（定义哪些顶点组成三角形）

### 2. 变换到屏幕坐标
3D图形经过矩阵运算，转换成为2D屏幕上的坐标。

通常发生在[顶点着色器](vertex_shader.md)

变换详见[3D渲染下的各种变换](3d_transforms.md)

[顶点着色器](vertex_shader.md)同时还会处理其他顶点属性（颜色、法线、纹理坐标等）

### 3. 图元装配与裁剪
- 将变换后的顶点组装成基本图形（通常是三角形）
- 裁剪处理：将屏幕外看不到的三角形移除，将能看到一部分的三角形切割，只保留可见部分

### 4. 视口变换
将标准化设备坐标（NDC）转换为屏幕像素坐标：
- X、Y坐标：从[-1,1]映射到实际屏幕像素范围（如0-1919, 0-1079）
- Z坐标：从[-1,1]映射到深度缓冲区范围（通常是[0,1]）

### 5. 光栅化
确定每个三角形覆盖屏幕上的哪些像素，
并为每个像素计算插值后的顶点属性（如颜色、纹理坐标、法线等）

### 6. 计算颜色
[像素着色器](pixel_shader.md)为每个像素计算最终结果：
- 应用材质和纹理
- 计算光照效果
- 处理透明度等特效

### 7. 深度测试
通过比较像素的深度值，确定哪些像素应该被显示（前面的物体遮挡后面的物体

### 8. 混合
处理透明物体的颜色混合

### 9. 输出
最终的像素颜色被写入帧缓冲区，显示在屏幕上

## 关键概念

- <b>顶点</b>：3D物体的基本构成单元，包含位置和属性信息
- <b>三角形</b>：现代图形硬件的基本渲染单元
- <b>变换矩阵</b>：用于坐标转换的数学工具
- <b>着色器</b>：在GPU上运行的小程序，处理顶点和像素

## 相关文档

- [顶点着色器详解](vertex_shader.md)
- [3D渲染下的各种变换](3d_transforms.md)
- [像素着色器详解](pixel_shader.md)
- [渲染管线概述](rendering_pipeline.md)