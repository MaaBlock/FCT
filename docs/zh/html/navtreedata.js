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
    [ "3D渲染下的各种变换", "md_docs_2zh_2md_23d__transforms.html", [
      [ "变换流程概览", "md_docs_2zh_2md_23d__transforms.html#autotoc_md1", null ],
      [ "详细变换步骤", "md_docs_2zh_2md_23d__transforms.html#autotoc_md2", [
        [ "1. 模型变换 (Model Transform)", "md_docs_2zh_2md_23d__transforms.html#autotoc_md3", null ],
        [ "2. 视图变换 (View Transform)", "md_docs_2zh_2md_23d__transforms.html#autotoc_md4", null ],
        [ "3. 投影变换 (Projection Transform)", "md_docs_2zh_2md_23d__transforms.html#autotoc_md5", null ],
        [ "4. 透视除法 (Perspective Division)", "md_docs_2zh_2md_23d__transforms.html#autotoc_md6", null ],
        [ "5. 视口变换 (Viewport Transform)", "md_docs_2zh_2md_23d__transforms.html#autotoc_md7", null ]
      ] ],
      [ "变换矩阵", "md_docs_2zh_2md_23d__transforms.html#autotoc_md8", null ]
    ] ],
    [ "一个3D物体是怎么被画出来的", "md_docs_2zh_2md_2how__3d__object__rendered.html", [
      [ "渲染管线流程", "md_docs_2zh_2md_2how__3d__object__rendered.html#autotoc_md10", null ],
      [ "详细流程", "md_docs_2zh_2md_2how__3d__object__rendered.html#autotoc_md11", null ],
      [ "详细流程", "md_docs_2zh_2md_2how__3d__object__rendered.html#autotoc_md12", [
        [ "1. 加载3D模型", "md_docs_2zh_2md_2how__3d__object__rendered.html#autotoc_md13", null ],
        [ "2. 变换到屏幕坐标", "md_docs_2zh_2md_2how__3d__object__rendered.html#autotoc_md14", null ],
        [ "3. 图元装配与裁剪", "md_docs_2zh_2md_2how__3d__object__rendered.html#autotoc_md15", null ],
        [ "4. 视口变换", "md_docs_2zh_2md_2how__3d__object__rendered.html#autotoc_md16", null ],
        [ "5. 光栅化", "md_docs_2zh_2md_2how__3d__object__rendered.html#autotoc_md17", null ],
        [ "6. 计算颜色", "md_docs_2zh_2md_2how__3d__object__rendered.html#autotoc_md18", null ],
        [ "7. 深度测试", "md_docs_2zh_2md_2how__3d__object__rendered.html#autotoc_md19", null ],
        [ "8. 混合", "md_docs_2zh_2md_2how__3d__object__rendered.html#autotoc_md20", null ],
        [ "9. 输出", "md_docs_2zh_2md_2how__3d__object__rendered.html#autotoc_md21", null ]
      ] ],
      [ "关键概念", "md_docs_2zh_2md_2how__3d__object__rendered.html#autotoc_md22", null ],
      [ "相关文档", "md_docs_2zh_2md_2how__3d__object__rendered.html#autotoc_md23", null ]
    ] ],
    [ "渲染管线概述", "md_docs_2zh_2md_2pipeline__comparison.html", [
      [ "什么是渲染管线？", "md_docs_2zh_2md_2pipeline__comparison.html#autotoc_md25", null ],
      [ "渲染管线分类", "md_docs_2zh_2md_2pipeline__comparison.html#autotoc_md26", null ],
      [ "详细分类说明", "md_docs_2zh_2md_2pipeline__comparison.html#autotoc_md27", [
        [ "1. 光栅化渲染", "md_docs_2zh_2md_2pipeline__comparison.html#autotoc_md28", [
          [ "1.1 传统光栅化管线", "md_docs_2zh_2md_2pipeline__comparison.html#autotoc_md29", null ],
          [ "1.2 MeshShader管线", "md_docs_2zh_2md_2pipeline__comparison.html#autotoc_md30", null ]
        ] ],
        [ "2. 光线追踪渲染", "md_docs_2zh_2md_2pipeline__comparison.html#autotoc_md31", null ]
      ] ],
      [ "性能对比", "md_docs_2zh_2md_2pipeline__comparison.html#autotoc_md32", null ]
    ] ],
    [ "渲染概念详解", "render_concepts.html", [
      [ "目录", "render_concepts.html#autotoc_md33", null ],
      [ "DrawCall", "render_concepts.html#render_drawcall", [
        [ "概念定义", "render_concepts.html#autotoc_md35", null ]
      ] ],
      [ "渲染管线 (Pipeline)", "render_concepts.html#render_pipeline", [
        [ "概念定义", "render_concepts.html#autotoc_md36", null ],
        [ "管线类型", "render_concepts.html#autotoc_md37", [
          [ "传统光栅化管线 (Traditional Pipeline)", "render_concepts.html#autotoc_md38", [
            [ "概念定义", "render_concepts.html#autotoc_md39", null ],
            [ "流程图", "render_concepts.html#autotoc_md40", null ],
            [ "包含的状态", "render_concepts.html#autotoc_md41", null ]
          ] ],
          [ "MeshShader光栅化管线 (MeshShader Pipeline)", "render_concepts.html#autotoc_md42", [
            [ "概念定义", "render_concepts.html#autotoc_md43", null ],
            [ "流程图", "render_concepts.html#autotoc_md44", null ],
            [ "包含的状态", "render_concepts.html#autotoc_md45", null ]
          ] ],
          [ "光线追踪管线 (RayTracing Pipeline)", "render_concepts.html#autotoc_md46", null ]
        ] ]
      ] ],
      [ "渲染通道 (Pass) {render_pass", "render_concepts.html#autotoc_md48", [
        [ "概念定义", "render_concepts.html#autotoc_md49", null ],
        [ "核心特性", "render_concepts.html#autotoc_md50", null ]
      ] ],
      [ "通道组 (PassGroup)", "render_concepts.html#render_passgroup", [
        [ "概念定义", "render_concepts.html#autotoc_md51", null ],
        [ "设计目的", "render_concepts.html#autotoc_md52", null ]
      ] ]
    ] ],
    [ "着色器概述", "md_docs_2zh_2md_2shader__overview.html", [
      [ "什么是着色器？", "md_docs_2zh_2md_2shader__overview.html#autotoc_md54", [
        [ "核心特点", "md_docs_2zh_2md_2shader__overview.html#autotoc_md55", null ]
      ] ],
      [ "着色器分类", "md_docs_2zh_2md_2shader__overview.html#autotoc_md56", null ],
      [ "传统管线着色器", "md_docs_2zh_2md_2shader__overview.html#autotoc_md57", [
        [ "1. 顶点着色器（Vertex Shader）", "md_docs_2zh_2md_2shader__overview.html#autotoc_md58", null ],
        [ "2. 几何着色器（Geometry Shader）", "md_docs_2zh_2md_2shader__overview.html#autotoc_md59", null ],
        [ "3. 像素着色器（Pixel Shader / Fragment Shader）", "md_docs_2zh_2md_2shader__overview.html#autotoc_md60", null ]
      ] ],
      [ "现代管线着色器", "md_docs_2zh_2md_2shader__overview.html#autotoc_md61", [
        [ "1. 任务着色器（Task Shader）", "md_docs_2zh_2md_2shader__overview.html#autotoc_md62", null ],
        [ "2. 网格着色器（Mesh Shader）", "md_docs_2zh_2md_2shader__overview.html#autotoc_md63", null ]
      ] ],
      [ "计算着色器（Compute Shader）", "md_docs_2zh_2md_2shader__overview.html#autotoc_md64", null ],
      [ "着色器语言对比", "md_docs_2zh_2md_2shader__overview.html#autotoc_md65", null ],
      [ "着色器开发流程", "md_docs_2zh_2md_2shader__overview.html#autotoc_md66", [
        [ "开发步骤", "md_docs_2zh_2md_2shader__overview.html#autotoc_md67", null ]
      ] ],
      [ "性能优化建议", "md_docs_2zh_2md_2shader__overview.html#autotoc_md68", [
        [ "通用优化", "md_docs_2zh_2md_2shader__overview.html#autotoc_md69", null ],
        [ "顶点着色器优化", "md_docs_2zh_2md_2shader__overview.html#autotoc_md70", null ],
        [ "像素着色器优化", "md_docs_2zh_2md_2shader__overview.html#autotoc_md71", null ]
      ] ],
      [ "调试工具", "md_docs_2zh_2md_2shader__overview.html#autotoc_md72", null ],
      [ "相关文档", "md_docs_2zh_2md_2shader__overview.html#autotoc_md73", null ],
      [ "总结", "md_docs_2zh_2md_2shader__overview.html#autotoc_md74", null ]
    ] ],
    [ "顶点着色器详解", "md_docs_2zh_2md_2vertex__shader.html", [
      [ "概述", "md_docs_2zh_2md_2vertex__shader.html#autotoc_md76", null ],
      [ "FCT中的顶点着色器", "md_docs_2zh_2md_2vertex__shader.html#autotoc_md77", [
        [ "基本使用示例", "md_docs_2zh_2md_2vertex__shader.html#autotoc_md78", null ],
        [ "布局系统详解", "md_docs_2zh_2md_2vertex__shader.html#autotoc_md79", null ],
        [ "代码生成机制", "md_docs_2zh_2md_2vertex__shader.html#autotoc_md80", null ],
        [ "自定义着色器代码", "md_docs_2zh_2md_2vertex__shader.html#autotoc_md81", null ],
        [ "优势特点", "md_docs_2zh_2md_2vertex__shader.html#autotoc_md82", null ]
      ] ],
      [ "相关文档", "md_docs_2zh_2md_2vertex__shader.html#autotoc_md83", null ]
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
"_pass_source_8h_source.html",
"_v_k___texture_view_8h_source.html",
"class_f_c_t_1_1_android___window.html#ab95cdb60248c488e182bd97bdb761a0b",
"class_f_c_t_1_1_call_back_event_handler.html#a954e4d0827e6b0be50ecd5bde87a22b9",
"class_f_c_t_1_1_context.html#a9053397bba286120ce3de5ebd6fc0b37",
"class_f_c_t_1_1_device.html#ae8f580cf023546aa540d030314de752b",
"class_f_c_t_1_1_g_l_f_w___swapchain_target_wrapper.html#ac4853f7a0c5aff4326e54aa04d463c81",
"class_f_c_t_1_1_image.html#a00e12d9e8b273151616fc2183c2f9fce",
"class_f_c_t_1_1_mat4.html#a0a1d014550c518156cdcc5a83c72b185",
"class_f_c_t_1_1_old_pass.html#a6abe5783ee5a943451b40024f8a685b4",
"class_f_c_t_1_1_pixel_shader.html#a8c6c9dadf4a0d5f6266c855e62a1c592",
"class_f_c_t_1_1_r_h_i_1_1_image.html#abe5d8b322123b8de96d7a37731b6c6a9",
"class_f_c_t_1_1_r_h_i_1_1_rasterization_pipeline.html#a37f260a8e1de8f3c98820fef38b1cfa5",
"class_f_c_t_1_1_r_h_i_1_1_texture_view.html#a33146ec5804be422936519224a3a7b3f",
"class_f_c_t_1_1_r_h_i_1_1_v_k___depth_stencil_state.html#aebec21cfd6277dcd0a804d1c40fab69d",
"class_f_c_t_1_1_r_h_i_1_1_v_k___input_layout.html#a9de9245ad9930de1c8a039fc0fc3f76d",
"class_f_c_t_1_1_r_h_i_1_1_v_k___rasterization_pipeline.html#a64afc601b21a37c7077916c2881b5837",
"class_f_c_t_1_1_r_h_i_1_1_v_k___swapchain.html#a01a2132e6c3ae5841dbf9b598df96e02",
"class_f_c_t_1_1_r_h_i_1_1_v_k___traditional_pipeline.html#a6a068f7a05ac880f0dc7574bcbc62a1a",
"class_f_c_t_1_1_rasterization_state.html#a8c07a181c3fdf0545b844cee55f5b68a",
"class_f_c_t_1_1_render_graph.html#adc5fb8038856ec115d0834aadef091d1",
"class_f_c_t_1_1_render_graph_pass_node.html#a85c4782b27c6c062dfe221c1c74da6ef",
"class_f_c_t_1_1_resource_manager.html#a954addf5ebf3890aa5ed2853cb9efc32",
"class_f_c_t_1_1_shader_generator.html#ab91186ecee3ab2bbf373dad6c281c9be",
"class_f_c_t_1_1_tls_ptr.html#a4b602225c2c546b1351c13ddd7241499",
"class_f_c_t_1_1_union_find.html#a04f762c63c853ddb72cdcad6f64951fd",
"class_f_c_t_1_1_v_k___context.html#aa31955989323b2d0f1f97a9dd8563e5e",
"class_f_c_t_1_1_v_k___pass_resource.html#adce903a017bf01a4df07064f8eae2310",
"class_f_c_t_1_1_v_k___viewport_state.html#adb929759aca9a702e5a27e8e541bb057",
"class_f_c_t_1_1_vertex_path.html#a33146ec5804be422936519224a3a7b3f",
"class_f_c_t_1_1_window.html#a58737ce5ad34870d946ce4cf65b6218e",
"md_docs_2zh_2md_2shader__overview.html#autotoc_md74",
"namespace_f_c_t.html#a1f3fd882e4a9d228566255fb96faa014a29842c3a0269b74e7697727f9eeece4a",
"namespace_f_c_t.html#aca2f02796bb2000f510d9542ef85e9d1a0a152d9f3e1df14068c5857fb3352505",
"struct_f_c_t_1_1_compiled_pass.html",
"struct_f_c_t_1_1_i_event_system_1_1_queued_event.html#a562c710b8c5b6893c89c7c488bfe0925",
"struct_f_c_t_1_1_pass_desc.html#a1728d45ae0fd682b096fc441c6d0cd9e",
"struct_f_c_t_1_1_size_node.html#aa7907fd33836d334cad7298a745bf999",
"struct_f_c_t_1_1_tradition_pipeline_state.html#ab538c23428554436c2a0969e59975973",
"struct_f_c_t_1_1_viewport_job.html#a83619a3a4984e9acb859a57783adc16c"
];

var SYNCONMSG = '点击 关闭 面板同步';
var SYNCOFFMSG = '点击 开启 面板同步';
var LISTOFALLMEMBERS = '所有成员列表';