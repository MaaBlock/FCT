/*
 @licstart  The following is the entire license notice for the JavaScript code in this file.

 The MIT License (MIT)

 Copyright (C) 1997-2020 by Dimitri van Heesch

 Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 and associated documentation files (the "Software"), to deal in the Software without restriction,
 including without limitation the rights to use, copy, modify, merge, publish, distribute,
 sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in all copies or
 substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

 @licend  The above is the entire license notice for the JavaScript code in this file
*/
var NAVTREE =
[
  [ "FCT", "index.html", [
    [ "3D渲染下的各种变换", "md_docs_2zh_2md_2rendering_23d__transforms.html", [
      [ "变换流程概览", "md_docs_2zh_2md_2rendering_23d__transforms.html#autotoc_md1", null ],
      [ "坐标系详解", "md_docs_2zh_2md_2rendering_23d__transforms.html#autotoc_md2", [
        [ "1. 局部坐标 (Local Space / Object Space)", "md_docs_2zh_2md_2rendering_23d__transforms.html#autotoc_md3", null ],
        [ "2. 世界坐标 (World Space)", "md_docs_2zh_2md_2rendering_23d__transforms.html#autotoc_md4", null ],
        [ "3. 观察坐标 (View Space / Camera Space)", "md_docs_2zh_2md_2rendering_23d__transforms.html#autotoc_md5", null ],
        [ "4. 裁剪坐标 (Clip Space)", "md_docs_2zh_2md_2rendering_23d__transforms.html#autotoc_md6", null ],
        [ "5. 标准化设备坐标 (NDC - Normalized Device Coordinates)", "md_docs_2zh_2md_2rendering_23d__transforms.html#autotoc_md7", null ],
        [ "6. 屏幕坐标 (Screen Space)", "md_docs_2zh_2md_2rendering_23d__transforms.html#autotoc_md8", null ]
      ] ],
      [ "详细变换步骤", "md_docs_2zh_2md_2rendering_23d__transforms.html#autotoc_md9", [
        [ "1. 模型变换 (Model Transform)", "md_docs_2zh_2md_2rendering_23d__transforms.html#autotoc_md10", null ],
        [ "2. 视图变换 (View Transform)", "md_docs_2zh_2md_2rendering_23d__transforms.html#autotoc_md11", null ],
        [ "3. 投影变换 (Projection Transform)", "md_docs_2zh_2md_2rendering_23d__transforms.html#autotoc_md12", null ],
        [ "4. 透视除法 (Perspective Division)", "md_docs_2zh_2md_2rendering_23d__transforms.html#autotoc_md13", null ],
        [ "5. 视口变换 (Viewport Transform)", "md_docs_2zh_2md_2rendering_23d__transforms.html#autotoc_md14", null ]
      ] ],
      [ "变换矩阵", "md_docs_2zh_2md_2rendering_23d__transforms.html#autotoc_md15", null ]
    ] ],
    [ "一个3D物体是怎么被画出来的", "md_docs_2zh_2md_2rendering_2how__3d__object__rendered.html", [
      [ "渲染管线流程", "md_docs_2zh_2md_2rendering_2how__3d__object__rendered.html#autotoc_md17", null ],
      [ "详细流程", "md_docs_2zh_2md_2rendering_2how__3d__object__rendered.html#autotoc_md18", null ],
      [ "详细流程", "md_docs_2zh_2md_2rendering_2how__3d__object__rendered.html#autotoc_md19", [
        [ "1. 加载3D模型", "md_docs_2zh_2md_2rendering_2how__3d__object__rendered.html#autotoc_md20", null ],
        [ "2. 变换到屏幕坐标", "md_docs_2zh_2md_2rendering_2how__3d__object__rendered.html#autotoc_md21", null ],
        [ "3. 图元装配与裁剪", "md_docs_2zh_2md_2rendering_2how__3d__object__rendered.html#autotoc_md22", null ],
        [ "4. 视口变换", "md_docs_2zh_2md_2rendering_2how__3d__object__rendered.html#autotoc_md23", null ],
        [ "5. 光栅化", "md_docs_2zh_2md_2rendering_2how__3d__object__rendered.html#autotoc_md24", null ],
        [ "6. 计算颜色", "md_docs_2zh_2md_2rendering_2how__3d__object__rendered.html#autotoc_md25", null ],
        [ "7. 深度测试", "md_docs_2zh_2md_2rendering_2how__3d__object__rendered.html#autotoc_md26", null ],
        [ "8. 混合", "md_docs_2zh_2md_2rendering_2how__3d__object__rendered.html#autotoc_md27", null ],
        [ "9. 输出", "md_docs_2zh_2md_2rendering_2how__3d__object__rendered.html#autotoc_md28", null ]
      ] ],
      [ "关键概念", "md_docs_2zh_2md_2rendering_2how__3d__object__rendered.html#autotoc_md29", null ],
      [ "相关文档", "md_docs_2zh_2md_2rendering_2how__3d__object__rendered.html#autotoc_md30", null ]
    ] ],
    [ "渲染管线概述", "md_docs_2zh_2md_2rendering_2pipeline__comparison.html", [
      [ "什么是渲染管线？", "md_docs_2zh_2md_2rendering_2pipeline__comparison.html#autotoc_md32", null ],
      [ "渲染管线分类", "md_docs_2zh_2md_2rendering_2pipeline__comparison.html#autotoc_md33", null ],
      [ "详细分类说明", "md_docs_2zh_2md_2rendering_2pipeline__comparison.html#autotoc_md34", [
        [ "1. 光栅化渲染", "md_docs_2zh_2md_2rendering_2pipeline__comparison.html#autotoc_md35", [
          [ "1.1 传统光栅化管线", "md_docs_2zh_2md_2rendering_2pipeline__comparison.html#autotoc_md36", null ],
          [ "1.2 MeshShader管线", "md_docs_2zh_2md_2rendering_2pipeline__comparison.html#autotoc_md37", null ]
        ] ],
        [ "2. 光线追踪渲染管线", "md_docs_2zh_2md_2rendering_2pipeline__comparison.html#autotoc_md38", null ]
      ] ],
      [ "性能对比", "md_docs_2zh_2md_2rendering_2pipeline__comparison.html#autotoc_md39", null ]
    ] ],
    [ "渲染概念详解", "render_concepts.html", [
      [ "目录", "render_concepts.html#autotoc_md40", null ],
      [ "DrawCall", "render_concepts.html#render_drawcall", [
        [ "概念定义", "render_concepts.html#autotoc_md42", null ]
      ] ],
      [ "渲染管线 (Pipeline)", "render_concepts.html#render_pipeline", [
        [ "概念定义", "render_concepts.html#autotoc_md43", null ],
        [ "管线类型", "render_concepts.html#autotoc_md44", [
          [ "传统光栅化管线 (Traditional Pipeline)", "render_concepts.html#autotoc_md45", [
            [ "概念定义", "render_concepts.html#autotoc_md46", null ],
            [ "流程图", "render_concepts.html#autotoc_md47", null ],
            [ "包含的状态", "render_concepts.html#autotoc_md48", null ]
          ] ],
          [ "MeshShader光栅化管线 (MeshShader Pipeline)", "render_concepts.html#autotoc_md49", [
            [ "概念定义", "render_concepts.html#autotoc_md50", null ],
            [ "流程图", "render_concepts.html#autotoc_md51", null ],
            [ "包含的状态", "render_concepts.html#autotoc_md52", null ]
          ] ],
          [ "光线追踪管线 (RayTracing Pipeline)", "render_concepts.html#autotoc_md53", null ]
        ] ]
      ] ],
      [ "渲染通道 (Pass) {render_pass", "render_concepts.html#autotoc_md55", [
        [ "概念定义", "render_concepts.html#autotoc_md56", null ],
        [ "核心特性", "render_concepts.html#autotoc_md57", null ]
      ] ],
      [ "通道组 (PassGroup)", "render_concepts.html#render_passgroup", [
        [ "概念定义", "render_concepts.html#autotoc_md58", null ],
        [ "设计目的", "render_concepts.html#autotoc_md59", null ]
      ] ]
    ] ],
    [ "RHI - 渲染硬件接口", "md_docs_2zh_2md_2rendering_2rhi.html", [
      [ "什么是RHI？", "md_docs_2zh_2md_2rendering_2rhi.html#autotoc_md61", null ],
      [ "为什么需要RHI？", "md_docs_2zh_2md_2rendering_2rhi.html#autotoc_md62", [
        [ "问题：图形API的碎片化", "md_docs_2zh_2md_2rendering_2rhi.html#autotoc_md63", null ],
        [ "解决方案：RHI抽象层", "md_docs_2zh_2md_2rendering_2rhi.html#autotoc_md64", null ]
      ] ],
      [ "FCT中的RHI设计", "md_docs_2zh_2md_2rendering_2rhi.html#autotoc_md65", [
        [ "架构概览", "md_docs_2zh_2md_2rendering_2rhi.html#autotoc_md66", null ],
        [ "Context类 - 渲染上下文的核心", "md_docs_2zh_2md_2rendering_2rhi.html#autotoc_md67", null ],
        [ "1. Device模块 - RHI资源创建器", "md_docs_2zh_2md_2rendering_2rhi.html#autotoc_md68", [
          [ "着色器资源", "md_docs_2zh_2md_2rendering_2rhi.html#autotoc_md69", null ],
          [ "缓冲区资源", "md_docs_2zh_2md_2rendering_2rhi.html#autotoc_md70", null ],
          [ "图像和纹理资源", "md_docs_2zh_2md_2rendering_2rhi.html#autotoc_md71", null ],
          [ "渲染状态资源", "md_docs_2zh_2md_2rendering_2rhi.html#autotoc_md72", null ],
          [ "渲染管线资源", "md_docs_2zh_2md_2rendering_2rhi.html#autotoc_md73", null ],
          [ "同步和命令资源", "md_docs_2zh_2md_2rendering_2rhi.html#autotoc_md74", null ]
        ] ],
        [ "2. ResourceManager模块 - 资源依赖管理器", "md_docs_2zh_2md_2rendering_2rhi.html#autotoc_md75", null ],
        [ "3. CommandBufferGraph模块 - 同步和命令管理器", "md_docs_2zh_2md_2rendering_2rhi.html#autotoc_md76", null ],
        [ "4. RenderGraph模块 - 渲染图管理器", "md_docs_2zh_2md_2rendering_2rhi.html#autotoc_md77", [
          [ "Pass资源类型", "md_docs_2zh_2md_2rendering_2rhi.html#autotoc_md78", null ],
          [ "完整的渲染图示例", "md_docs_2zh_2md_2rendering_2rhi.html#autotoc_md79", null ],
          [ "渲染图的优势", "md_docs_2zh_2md_2rendering_2rhi.html#autotoc_md80", null ]
        ] ]
      ] ]
    ] ],
    [ "着色器概述", "md_docs_2zh_2md_2rendering_2shader__overview.html", [
      [ "什么是着色器？", "md_docs_2zh_2md_2rendering_2shader__overview.html#autotoc_md82", [
        [ "核心特点", "md_docs_2zh_2md_2rendering_2shader__overview.html#autotoc_md83", null ]
      ] ],
      [ "着色器分类", "md_docs_2zh_2md_2rendering_2shader__overview.html#autotoc_md84", null ],
      [ "传统管线着色器", "md_docs_2zh_2md_2rendering_2shader__overview.html#autotoc_md85", [
        [ "1. 顶点着色器（Vertex Shader）", "md_docs_2zh_2md_2rendering_2shader__overview.html#autotoc_md86", null ],
        [ "2. 几何着色器（Geometry Shader）", "md_docs_2zh_2md_2rendering_2shader__overview.html#autotoc_md87", null ],
        [ "3. 像素着色器（Pixel Shader / Fragment Shader）", "md_docs_2zh_2md_2rendering_2shader__overview.html#autotoc_md88", null ]
      ] ],
      [ "现代管线着色器", "md_docs_2zh_2md_2rendering_2shader__overview.html#autotoc_md89", [
        [ "1. 任务着色器（Task Shader）", "md_docs_2zh_2md_2rendering_2shader__overview.html#autotoc_md90", null ],
        [ "2. 网格着色器（Mesh Shader）", "md_docs_2zh_2md_2rendering_2shader__overview.html#autotoc_md91", null ]
      ] ],
      [ "计算着色器（Compute Shader）", "md_docs_2zh_2md_2rendering_2shader__overview.html#autotoc_md92", null ],
      [ "着色器语言对比", "md_docs_2zh_2md_2rendering_2shader__overview.html#autotoc_md93", null ],
      [ "着色器开发流程", "md_docs_2zh_2md_2rendering_2shader__overview.html#autotoc_md94", [
        [ "开发步骤", "md_docs_2zh_2md_2rendering_2shader__overview.html#autotoc_md95", null ]
      ] ],
      [ "性能优化建议", "md_docs_2zh_2md_2rendering_2shader__overview.html#autotoc_md96", [
        [ "通用优化", "md_docs_2zh_2md_2rendering_2shader__overview.html#autotoc_md97", null ],
        [ "顶点着色器优化", "md_docs_2zh_2md_2rendering_2shader__overview.html#autotoc_md98", null ],
        [ "像素着色器优化", "md_docs_2zh_2md_2rendering_2shader__overview.html#autotoc_md99", null ]
      ] ],
      [ "调试工具", "md_docs_2zh_2md_2rendering_2shader__overview.html#autotoc_md100", null ],
      [ "相关文档", "md_docs_2zh_2md_2rendering_2shader__overview.html#autotoc_md101", null ],
      [ "总结", "md_docs_2zh_2md_2rendering_2shader__overview.html#autotoc_md102", null ]
    ] ],
    [ "顶点着色器详解", "md_docs_2zh_2md_2rendering_2vertex__shader.html", [
      [ "概述", "md_docs_2zh_2md_2rendering_2vertex__shader.html#autotoc_md104", null ],
      [ "FCT中的顶点着色器", "md_docs_2zh_2md_2rendering_2vertex__shader.html#autotoc_md105", [
        [ "基本使用示例", "md_docs_2zh_2md_2rendering_2vertex__shader.html#autotoc_md106", null ],
        [ "布局系统详解", "md_docs_2zh_2md_2rendering_2vertex__shader.html#autotoc_md107", null ],
        [ "代码生成机制", "md_docs_2zh_2md_2rendering_2vertex__shader.html#autotoc_md108", null ],
        [ "自定义着色器代码", "md_docs_2zh_2md_2rendering_2vertex__shader.html#autotoc_md109", null ],
        [ "优势特点", "md_docs_2zh_2md_2rendering_2vertex__shader.html#autotoc_md110", null ]
      ] ],
      [ "相关文档", "md_docs_2zh_2md_2rendering_2vertex__shader.html#autotoc_md111", null ]
    ] ],
    [ "命名空间", "namespaces.html", [
      [ "命名空间列表", "namespaces.html", "namespaces_dup" ],
      [ "命名空间成员", "namespacemembers.html", [
        [ "全部", "namespacemembers.html", null ],
        [ "函数", "namespacemembers_func.html", null ],
        [ "变量", "namespacemembers_vars.html", null ],
        [ "类型定义", "namespacemembers_type.html", null ],
        [ "枚举", "namespacemembers_enum.html", null ],
        [ "枚举值", "namespacemembers_eval.html", null ]
      ] ]
    ] ],
    [ "类", "annotated.html", [
      [ "类列表", "annotated.html", "annotated_dup" ],
      [ "类索引", "classes.html", null ],
      [ "类继承关系", "hierarchy.html", "hierarchy" ],
      [ "类成员", "functions.html", [
        [ "全部", "functions.html", "functions_dup" ],
        [ "函数", "functions_func.html", "functions_func" ],
        [ "变量", "functions_vars.html", "functions_vars" ],
        [ "类型定义", "functions_type.html", null ],
        [ "枚举", "functions_enum.html", null ],
        [ "枚举值", "functions_eval.html", null ],
        [ "相关符号", "functions_rela.html", null ]
      ] ]
    ] ],
    [ "文件", "files.html", [
      [ "文件列表", "files.html", "files_dup" ],
      [ "文件成员", "globals.html", [
        [ "全部", "globals.html", null ],
        [ "函数", "globals_func.html", null ],
        [ "变量", "globals_vars.html", null ],
        [ "宏定义", "globals_defs.html", null ]
      ] ]
    ] ]
  ] ]
];

var NAVTREEINDEX =
[
"_access_flags_8h.html",
"_pipeline_stage_8h_source.html",
"_v_k___texture_view_8cpp_source.html",
"class_f_c_t_1_1_android___window.html#ab922a45877085cd709332b0d32c8b032",
"class_f_c_t_1_1_call_back_event_handler.html#aac2f5f24478b7ada5186fa763e5a3a63",
"class_f_c_t_1_1_command_buffer_nodes_1_1_output_to_window.html#a702a2bded159cabd500133579c48407f",
"class_f_c_t_1_1_context.html#aed5ee768dbd1e64f831cf65024133505",
"class_f_c_t_1_1_dynamic_mesh.html#ac94f553f5d98ef2054ec03cf43d6b0a7",
"class_f_c_t_1_1_g_l_f_w___window.html#a4c8588c4fe27f0e5e273fd78421b490b",
"class_f_c_t_1_1_image_behavior.html#a793761ed62f077d60c3ee1072409f0d6",
"class_f_c_t_1_1_mutil_buffer_image.html#a0fea0bed50f726d3e11ddde802dac5da",
"class_f_c_t_1_1_old_render_graph.html#a5eca63a9431242b1b0843aed59d0b617",
"class_f_c_t_1_1_r_h_i_1_1_command_buffer.html#af3dcfa6dbb473476a545dda2c9cea0fa",
"class_f_c_t_1_1_r_h_i_1_1_input_layout.html#aca88529f9b473d326168fa808fd02300",
"class_f_c_t_1_1_r_h_i_1_1_semaphore.html#ad7b72415b5c2e15a44bf488c7e27c4cd",
"class_f_c_t_1_1_r_h_i_1_1_v_k___command_buffer.html#adf6a0192fe851bf1c0b3603f80b1c74e",
"class_f_c_t_1_1_r_h_i_1_1_v_k___fence.html#aa11d4656b54ed291143d6c79da4c407b",
"class_f_c_t_1_1_r_h_i_1_1_v_k___pass.html#ab41b4758c6557c0596947beaeede42c1",
"class_f_c_t_1_1_r_h_i_1_1_v_k___sampler.html#a047cb3fd07ad00efb54677d30f7674d1",
"class_f_c_t_1_1_r_h_i_1_1_v_k___swapchain.html#a681c8c6935ce8604cb7e11e43205b304",
"class_f_c_t_1_1_r_h_i_1_1_v_k___vertex_buffer.html#aadc39e9165b47bcee2ff99c74138dc71",
"class_f_c_t_1_1_ref_count_policy.html",
"class_f_c_t_1_1_render_graph_image_node.html#a1e03845e1c9a1b6c61b1b94854c0ddfd",
"class_f_c_t_1_1_render_graph_window_target_node.html#acb9e78de8b46b61ed8b697f95b390952",
"class_f_c_t_1_1_scope_timer.html#a9c8319c5c921a8cd9b9db5a1c2eae8b6",
"class_f_c_t_1_1_static_mesh.html#aa3d0e16a9851d3dc0ffec540f16f0b72",
"class_f_c_t_1_1_tradition_render_pass.html#a27ec13a87b92e60bfa519478693203e9",
"class_f_c_t_1_1_v_k___context.html#a621b6e36528f72660eeda7f77d65b75a",
"class_f_c_t_1_1_v_k___pass_resource.html#a5a87c09644f12ae3b72621bd182923d0",
"class_f_c_t_1_1_v_k___viewport_state.html#a33146ec5804be422936519224a3a7b3f",
"class_f_c_t_1_1_vertex_layout.html#ae08626387512928c70619c3a7fcf21d4",
"class_f_c_t_1_1_window.html#a263187dd65b4ac02a3e23c78b30e26a1",
"md_docs_2zh_2md_2rendering_2how__3d__object__rendered.html#autotoc_md26",
"namespace_f_c_t.html#a0741721dca246274b1b72d07249443e4ad0a8fa71e3197bbf9b23d6d93235f3ca",
"namespace_f_c_t.html#aa6d1e7cd43d5bb06686de955be1a4309a4ac79e298654a08a862b24a0c5ccf47e",
"struct_f_c_t_1_1_blend_state_1_1_target.html#a2dfa8c8e4dbd355a136befc12c493408",
"struct_f_c_t_1_1_image_saved.html",
"struct_f_c_t_1_1_r_h_i_1_1_pass_neighbors.html",
"struct_f_c_t_1_1_texture_size.html#a727213614de5c7b06e5ac4af6bc03f4e",
"struct_f_c_t_1_1_vector4.html#a6bdb0fd0ec75598871475f093e4295e5"
];

var SYNCONMSG = '点击 关闭 面板同步';
var SYNCOFFMSG = '点击 开启 面板同步';
var LISTOFALLMEMBERS = '所有成员列表';