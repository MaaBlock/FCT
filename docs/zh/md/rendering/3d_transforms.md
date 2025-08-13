# 3D渲染下的各种变换

在3D图形渲染中，物体需要经过一系列坐标变换才能最终显示在屏幕上。这些变换将3D空间中的几何体转换为2D屏幕像素。

## 变换流程概览

\dot
digraph transform_pipeline {
rankdir=LR;

    graph [fontname="SimHei", charset="UTF-8"];
    node [shape=box, style=filled, fontname="SimHei"];
    edge [fontname="SimHei"];

    A [label="局部坐标\n(Local Space)", fillcolor=lightblue];
    B [label="世界坐标\n(World Space)", fillcolor=lightgreen];
    C [label="观察坐标\n(View Space)", fillcolor=lightyellow];
    D [label="裁剪坐标\n(Clip Space)", fillcolor=lightcoral];
    E [label="标准化设备坐标\n(NDC)", fillcolor=lightpink];
    F [label="屏幕坐标\n(Screen Space)", fillcolor=lightgray];
    
    A -> B [label="模型变换"];
    B -> C [label="视图变换"];
    C -> D [label="投影变换"];
    D -> E [label="透视除法"];
    E -> F [label="视口变换"];
}
\enddot

## 坐标系详解

### 1. 局部坐标 (Local Space / Object Space)
- <b>定义</b>：物体自身的坐标系，以物体中心为原点
- <b>特点</b>：每个物体都有自己独立的局部坐标系
- <b>用途</b>：建模时使用，便于物体的创建和编辑
- <b>示例</b>：一个立方体的顶点坐标可能是 (-1,-1,-1) 到 (1,1,1)

### 2. 世界坐标 (World Space)
- <b>定义</b>：整个3D场景的全局坐标系
- <b>特点</b>：所有物体都统一在这个坐标系中
- <b>用途</b>：确定物体在场景中的绝对位置和相对关系
- <b>示例</b>：房间中的桌子位于 (5,0,3)，椅子位于 (5,0,1)

### 3. 观察坐标 (View Space / Camera Space)
- <b>定义</b>：以摄像机为原点的坐标系
- <b>特点</b>：摄像机位于原点，看向-Z方向，Y轴向上
- <b>用途</b>：简化后续的投影计算
- <b>示例</b>：摄像机前方2米的物体坐标为 (0,0,-2)

### 4. 裁剪坐标 (Clip Space)
- <b>定义</b>：应用投影变换后的坐标系
- <b>特点</b>：包含齐次坐标的w分量，用于透视除法
- <b>用途</b>：进行视锥体裁剪，剔除不可见的几何体
- <b>示例</b>：坐标范围通常在 [-w, w] 之间

### 5. 标准化设备坐标 (NDC - Normalized Device Coordinates)
- <b>定义</b>：经过透视除法后的标准化坐标
- <b>特点</b>：坐标范围固定在 [-1, 1] 之间（OpenGL）或 [0, 1]（DirectX）
- <b>用途</b>：与具体屏幕分辨率无关的标准化表示
- <b>示例</b>：屏幕中心为 (0,0)，四个角为 (±1,±1)

### 6. 屏幕坐标 (Screen Space)
- <b>定义</b>：最终的像素坐标
- <b>特点</b>：以像素为单位，左上角通常为原点
- <b>用途</b>：直接对应屏幕上的像素位置
- <b>示例</b>：1920x1080屏幕的坐标范围为 (0,0) 到 (1919,1079)

## 详细变换步骤

### 1. 模型变换 (Model Transform)
将物体从局部坐标系转换到世界坐标系
- <b>平移</b>：移动物体位置
- <b>旋转</b>：改变物体朝向
- <b>缩放</b>：改变物体大小

### 2. 视图变换 (View Transform)
将世界坐标转换到摄像机坐标系
- 以摄像机为原点建立新的坐标系
- 摄像机看向的方向为-Z轴

### 3. 投影变换 (Projection Transform)
将3D坐标投影到2D平面
- <b>透视投影</b>：模拟人眼视觉，远小近大
- <b>正交投影</b>：平行投影，不考虑距离

### 4. 透视除法 (Perspective Division)
将裁剪坐标转换为标准化设备坐标
- 除以w分量实现透视效果

### 5. 视口变换 (Viewport Transform)
将NDC转换为屏幕像素坐标
- X、Y坐标映射到屏幕分辨率
- Z坐标映射到深度缓冲区范围

## 变换矩阵

每个变换都可以用4x4矩阵表示，多个变换可以通过矩阵乘法组合：
