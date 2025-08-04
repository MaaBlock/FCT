# 渲染概念详解 {#render_concepts}

本文档详细介绍 MQEngine 中的核心渲染概念，这些概念是理解和使用引擎渲染系统的基础。

## 目录
- \ref render_drawcall "DrawCall"
- \ref render_pipeline "渲染管线 (Pipeline)"
- \ref render_pass "渲染通道 (Pass)"
- \ref render_passgroup "通道组 (PassGroup)"

---

## DrawCall {#render_drawcall}
### 概念定义
执行一次Draw操作
## 渲染管线 (Pipeline) {#render_pipeline}
### 概念定义
一次Draw操作所包含的所有状态信息
### 管线类型
#### 传统光栅化管线 (Traditional Pipeline)
##### 概念定义
##### 流程图
##### 包含的状态

#### MeshShader光栅化管线 (MeshShader Pipeline)
##### 概念定义
##### 流程图
##### 包含的状态

#### 光线追踪管线 (RayTracing Pipeline)

---

## 渲染通道 (Pass) {#render_pass}

### 概念定义

渲染通道（Pass）可以有多个Pipeline

### 核心特性

- **单一职责**：每个 Pass 只负责一种特定的渲染操作
- **可组合性**：多个 Pass 可以组合成复杂的渲染效果
- **资源管理**：管理自己的输入输出资源

## 通道组 (PassGroup) {#render_passgroup}

### 概念定义

通道组 (PassGroup)可以有多个Pass，但是target以及深度缓存大小必须一致

### 设计目的

- **逻辑分组**：将功能相关的 Pass 组织在一起，便于管理和维护
- **依赖管理**：自动处理 Pass 间的数据依赖关系，确保正确的执行顺序
- **资源共享**：组内 Pass 可以高效共享中间渲染结果和资源
- **并行优化**：支持无依赖关系的 Pass 并行执行，提升渲染性能
- **可复用性**：整个 PassGroup 可以作为一个单元在不同场景中复用
