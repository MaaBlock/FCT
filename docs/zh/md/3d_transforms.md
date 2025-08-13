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
## 详细变换步骤

### 1. 模型变换 (Model Transform)
将物体从局部坐标系转换到世界坐标系
- **平移**：移动物体位置
- **旋转**：改变物体朝向
- **缩放**：改变物体大小

### 2. 视图变换 (View Transform)
将世界坐标转换到摄像机坐标系
- 以摄像机为原点建立新的坐标系
- 摄像机看向的方向为-Z轴

### 3. 投影变换 (Projection Transform)
将3D坐标投影到2D平面
- **透视投影**：模拟人眼视觉，远小近大
- **正交投影**：平行投影，不考虑距离

### 4. 透视除法 (Perspective Division)
将裁剪坐标转换为标准化设备坐标
- 除以w分量实现透视效果

### 5. 视口变换 (Viewport Transform)
将NDC转换为屏幕像素坐标
- X、Y坐标映射到屏幕分辨率
- Z坐标映射到深度缓冲区范围

## 变换矩阵

每个变换都可以用4x4矩阵表示，多个变换可以通过矩阵乘法组合：
