enum shape_primitive_topology_t {
	shape_primitive_topology_pointlist,
	shape_primitive_topology_linelist,
	shape_primitive_topology_lineloop,
	shape_primitive_topology_linestrip,
	shape_primitive_topology_trianglelist,
	shape_primitive_topology_trianglestrip,
};
enum const_buffer_bind_shader_t : int {
	const_buffer_bind_vertex_shader = 0x1,
	const_buffer_bind_pixel_shader	= 0x2,
	const_buffer_bind_compute_shader = 0x4,
	const_buffer_bind_geometry_shader = 0x8
};
enum depth_func_t{
	depth_func_less,
	depth_func_less_equal,
	depth_func_greater,
	depth_func_greater_equal,
	depth_func_equal,
	depth_func_notequal,
	depth_func_always,
	depth_func_never,
};
enum stencil_func_t {
	stencil_func_always,
	stencil_func_never,
	stencil_func_less,
	stencil_func_less_equal,
	stencil_func_equal,
	stencil_func_notequal,
	stencil_func_greater,
	stencil_func_greater_equal,
};
enum stencil_op_t {
	stencil_op_keep,
	stencil_op_zero,
	stencil_op_replace,
	stencil_op_increment_saturate,
	stencil_op_decrement_saturate,
	stencil_op_invert,
	stencil_op_increment,
	stencil_op_decrement,
};
enum cull_mode_t {
	cull_mode_none,
	cull_mode_front,
	cull_mode_back,
};
enum fill_mode_t {
	fill_mode_wireframe,
	fill_mode_solid,
};
enum context_resouce_t { 
	context_resource_vertex2d_buffer,
	context_resource_constant_buffer,
	context_resource_index_buffer,
	context_resource_rasterizer_state,
	context_resource_depth_stencil_state,
	context_resource_blend_state,
	context_resource_sampler_state, 
	context_resource_topology,
	context_resource_pixel_shader,
	context_resource_vertex_shader,
	context_resource_geometry_shader,
};
enum blend_factor_t {
	blend_factor_zero,
	blend_factor_one,
	blend_factor_src_color,
	blend_factor_inv_src_color,
	blend_factor_src_alpha,
	blend_factor_inv_src_alpha,
	blend_factor_dest_alpha,
	blend_factor_inv_dest_alpha,
	blend_factor_dest_color,
	blend_factor_inv_dest_color,
	blend_factor_src_alpha_sat,
	blend_factor_blend_factor,
	blend_factor_inv_blend_factor
};
enum blend_op_t {
	blend_op_add,
	blend_op_subtract,
	blend_op_rev_subtract,
	blend_op_min,
	blend_op_max,
};

enum blend_state_write_mask_t {
	blend_state_write_mask_r = 0x1,
	blend_state_write_mask_g = 0x2,
	blend_state_write_mask_b = 0x4,
	blend_state_write_mask_a = 0x8,
};
enum texture_filter_t {
	texture_filter_min_mag_mip_point,
	texture_filter_min_mag_point_mip_linear,
	texture_filter_min_mag_linear_mip_point,
	texture_filter_min_mag_linear_mip_linear,
	texture_filter_anisotropic,
};
enum texture_address_mode_t {
	texture_address_mode_wrap,
	texture_address_mode_mirror,
	texture_address_mode_clamp,
	texture_address_mode_border,
	texture_address_mode_mirror_once
};
enum comparison_func_t {
	comparison_func_never,
	comparison_func_less,
	comparison_func_equal,
	comparison_func_less_equal,
	comparison_func_greater,
	comparison_func_not_equal,
	comparison_func_always,
};


class ContextResouce: public RefCounted{
public:
	virtual context_resouce_t getResouceType() = 0;
	virtual void bind(Context*) = 0;
private:
};

class Vertex2dBuffer : public ContextResouce {
public:
	context_resouce_t getResouceType() {
		return context_resource_vertex2d_buffer;
	}
	virtual int getVertexNum() = 0;
};
class Topology : public ContextResouce {
public:
	context_resouce_t getResouceType() {
		return context_resource_topology;
	}
};
class PixelShader : public ContextResouce {
public:
	context_resouce_t getResouceType() {
		return context_resource_pixel_shader;
	}
};
class GeometryShader : public ContextResouce {
public:
	context_resouce_t getResouceType() {
		return context_resource_geometry_shader;
	}
	virtual void setCode(const char* code)= 0;
	virtual void create(Context* context) = 0;
};

class VertexShader : public ContextResouce {
public:
	context_resouce_t getResouceType() {
		return context_resource_vertex_shader;
	}
};
class ConstBuffer : public ContextResouce {
public:
	context_resouce_t getResouceType() {
		return context_resource_constant_buffer;
	}
};
class BlendState : public ContextResouce {
public:
	virtual void alphaToCoverage(bool enable) = 0;
	virtual void independentBlend(bool enable) = 0;
	virtual void blendEnable(bool enable, int index = 0) = 0;
	virtual void srcBlendRGB(blend_factor_t src, int index = 0) = 0;
	virtual void destBlendRGB(blend_factor_t dest, int index = 0) = 0;
	virtual void blendOpRGB(blend_op_t op, int index = 0) = 0;
	virtual void srcBlendAlpha(blend_factor_t src, int index = 0) = 0;
	virtual void destBlendAlpha(blend_factor_t dest, int index = 0) = 0;
	virtual void blendOpAlpha(blend_op_t op, int index = 0) = 0;
	virtual void writeMask(char mask = 0xf) = 0;// a b g r
	context_resouce_t getResouceType() {
		return context_resource_blend_state;
	}
};

class SamplerState : public ContextResouce {
public:
	context_resouce_t getResouceType() {
		return context_resource_sampler_state;
	}
	virtual void setFilter(texture_filter_t filter) = 0;
	virtual void setAddressU(texture_address_mode_t address) = 0;
	virtual void setAddressV(texture_address_mode_t address) = 0;
	virtual void setAddressW(texture_address_mode_t address) = 0;
	virtual void setMipLODBias(float bias) = 0;
	virtual void setMaxAnisotropy(unsigned int max) = 0;
	virtual void setComparisonFunc(comparison_func_t func) = 0;
	virtual void setMinLod(float min) = 0;
	virtual void setMaxLod(float max) = 0;
	virtual void setBorderColor(Color color) = 0;


};

class RasterizerState : public ContextResouce {
public:
	context_resouce_t getResouceType() {
		return context_resource_rasterizer_state;
	}
	virtual void setCullMode(cull_mode_t mode) = 0;
	virtual void setFillMode(fill_mode_t mode) = 0;
	virtual void setFrontCounterClockwise(bool ccw) = 0;
	virtual void setDepthClipEnable(bool enable) = 0;
	virtual void setDepthBias(float bias) = 0;
	virtual void setDepthBiasClamp(float clamp) = 0;
	virtual void setSlopeScaledDepthBias(float slope) = 0;
	virtual void setScissorEnable(bool enable) = 0;
	virtual void setMultisampleEnable(bool enable) = 0;
	virtual void setAntialiasedLineEnable(bool enable) = 0;
	virtual void create(Context* context) = 0;
};

class DepthStencilState : public ContextResouce {
public:
	context_resouce_t getResouceType() {
		return context_resource_depth_stencil_state;
	}
	virtual void setRefStencil(unsigned char stencil) = 0;
	virtual void setDepthEnable(bool enable) = 0;
	virtual void setDepthWrite(bool write) = 0;
	virtual void setDepthFunc(depth_func_t func) = 0;
	virtual void setStencilEnable(bool enable) = 0;
	virtual void setStencilWriteMask(unsigned mask) = 0;
	virtual void setStencilReadMask(unsigned mask) = 0;
	virtual void setFrontFaceStencilFunc(stencil_func_t func) = 0; 
	virtual void setBackFaceStencilFunc(stencil_func_t func) = 0;
	virtual void setFrontFaceStencilPass(stencil_op_t op) = 0;
	virtual void setBackFaceStencilPass(stencil_op_t op) = 0;
	virtual void setFrontFaceStencilFail(stencil_op_t op) = 0;
	virtual void setBackFaceStencilFail(stencil_op_t op) = 0;
	virtual void setFrontFaceStencilFailDepth(stencil_op_t op) = 0;
	virtual void setBackFaceStencilFailDepth(stencil_op_t op) = 0;
};