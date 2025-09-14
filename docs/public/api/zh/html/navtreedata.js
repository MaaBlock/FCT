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
"_pass_group_8h_source.html",
"_v_k___render_target_view_8cpp.html",
"class_f_c_t_1_1_android___window.html#a8567f9179e1f26134b8ccc3a2dd1e37d",
"class_f_c_t_1_1_call_back_event_handler.html#a53a1d75fbb1513777e8e2c8d330c2c63",
"class_f_c_t_1_1_command_buffer_nodes_1_1_input_from_window.html#a2057cd287253b712d7f9361730947542",
"class_f_c_t_1_1_context.html#a4c6607256a23ab3c6a276ca3ffa855d9",
"class_f_c_t_1_1_device.html#ad81488b6339fac66b4456f91ce0c99c0",
"class_f_c_t_1_1_freetype___font.html#aebd495432108b8bebce18c812a6b60ac",
"class_f_c_t_1_1_i_pipeline_resource.html#a58dbf88b7d41d5a9bcfba9eec61b85f0",
"class_f_c_t_1_1_layout.html#a1aaa31a8ea1236ec427c1a2e7ad7c097",
"class_f_c_t_1_1_mutil_buffer_affter_create_image_behavior.html#a955ee36cbdbb3b6e544dbeeb6def751b",
"class_f_c_t_1_1_old_render_graph.html#a04756793cfef1266eba98c209899fd35",
"class_f_c_t_1_1_pixel_shader.html#aca88529f9b473d326168fa808fd02300",
"class_f_c_t_1_1_r_h_i_1_1_index_buffer.html#a07c27280b1bd2bbebcb9d53be5b04eff",
"class_f_c_t_1_1_r_h_i_1_1_rasterization_pipeline.html#a37f260a8e1de8f3c98820fef38b1cfa5",
"class_f_c_t_1_1_r_h_i_1_1_texture_view.html#a33146ec5804be422936519224a3a7b3f",
"class_f_c_t_1_1_r_h_i_1_1_v_k___depth_stencil_state.html#ad001d86255bc64b9181428f2780cee65",
"class_f_c_t_1_1_r_h_i_1_1_v_k___input_layout.html#a5f01b0d3607f1cb46fc77c4819c14fe0",
"class_f_c_t_1_1_r_h_i_1_1_v_k___rasterization_pipeline.html#a33146ec5804be422936519224a3a7b3f",
"class_f_c_t_1_1_r_h_i_1_1_v_k___shader_binary.html#a9508b6de32fa750c31ae861edacc741e",
"class_f_c_t_1_1_r_h_i_1_1_v_k___traditional_pipeline.html#a0ece67653fd67194f24729f21217c913",
"class_f_c_t_1_1_rasterization_state.html#a19978956acaa0cfba67bdd082c075bbe",
"class_f_c_t_1_1_render_graph.html#ab195fe60a7dd017668c078e20501b850",
"class_f_c_t_1_1_render_graph_pass_node.html#a27eba767ef0c8c080f60f82ef2dabb25",
"class_f_c_t_1_1_resource_layout.html#ae580a010a86f7889769786e3a384fd21",
"class_f_c_t_1_1_shader_compiler.html",
"class_f_c_t_1_1_texture_edge.html#a773d2c38f4b5fd0b1fbe0c24fb144fbf",
"class_f_c_t_1_1_tradition_render_pass.html#aa6c2582a3863a073ab36d70f635502d2",
"class_f_c_t_1_1_v_k___context.html#a59c2f131121de6503df8d363b6853d45",
"class_f_c_t_1_1_v_k___pass_resource.html#a0fea0bed50f726d3e11ddde802dac5da",
"class_f_c_t_1_1_v_k___vertex_shader.html#a8c5c5d9fda7420078a3b28368259fc31",
"class_f_c_t_1_1_vertex_element.html#ad6bfaedf2b27df9ee4802d42704b32f2",
"class_f_c_t_1_1_viewport_state_behaviour.html#abf9cd82d4fdd4d034403aab90d9d1928",
"functions_z.html",
"namespace_f_c_t.html#a27301bf9820b6a2f74032d78ffe2806a",
"namespace_f_c_t.html#adb995786f2f649c122895cd47ab09d32afed8068cf66889c7c88bd5b7d3d02e4b",
"struct_f_c_t_1_1_depth_stencil.html#a6f314e61adb6c667e8cfc695903a65dd",
"struct_f_c_t_1_1_job.html#a875ef854b3268c18ca1e6e5ef4e1d980",
"struct_f_c_t_1_1_old_render_graph_1_1_window_depth_stencil_resource.html",
"struct_f_c_t_1_1_size_node.html#a841dd2fb34c5e249eedde53b3282b792",
"struct_f_c_t_1_1_tradition_render_job.html#a474ad3a918f2e87d75ff16075e1caeec",
"struct_f_c_t_1_1_vertex_screen_info.html#ac101ae10a26b459bbf73bfe29a46161d"
];

var SYNCONMSG = '点击 关闭 面板同步';
var SYNCOFFMSG = '点击 开启 面板同步';
var LISTOFALLMEMBERS = '所有成员列表';