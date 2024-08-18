#include "hander.h"


namespace FCT {
	class ShapeCommon : public RefCounted {
	public:
		virtual void create(Context* context) = 0;
	private:

	};
	class ShapeBuilder {
	public:
		ShapeBuilder(Context* context);
		template<typename T>
		ShapeCommon* createShapeCommon(const char* shapeName);
		template<typename T>
		T* getShapeCommon(const char* shapeName);
		Context* getContext() { return m_context; }	
	private:
		std::map<const char*, ShapeCommon*> m_shapeCommonMap;
		Context* m_context;
	};
	ShapeBuilder::ShapeBuilder(Context* context)
	{
		m_context = context;
	}
	template<typename T>
	ShapeCommon* ShapeBuilder::createShapeCommon(const char* shapeName)
	{
		ShapeCommon* shapeCommon = FCT_NEW(T);
		shapeCommon->create(m_context);
		m_shapeCommonMap[shapeName] = shapeCommon;
		return shapeCommon;
	}
	template<typename T>
	T* ShapeBuilder::getShapeCommon(const char* shapeName)
	{
		auto it = m_shapeCommonMap.find(shapeName);
		if (it != m_shapeCommonMap.end()) {
			return static_cast<T*>(it->second);
		}
		createShapeCommon<T>(shapeName);
		return getShapeCommon<T>(shapeName);
	}
#define FCT_SHAPE_CREATE_BEGIN(name) name##ShapeCommon* common = builder->getShapeCommon<name##ShapeCommon>(#name);
#define FCT_SHAPE_COMMON_INIT() 
	ShapeBuilder* createShapeBuilder(Context* context) {
		return FCT_NEW(ShapeBuilder,context);
	}
	class NewCircleShapeCommon : public ShapeCommon {
	public:
		void create(Context* context) {
			m_pixelShader = context->createPixelShader(
				"Texture2D texcoord : register(t0);"
				"SamplerState g_sampler : register(s0);"
				"cbuffer VecTexcoord : register(b1)"
				"{"
				"	float2 lt_texcoord;"
				"   float2 rb_texcoord;"
				"}"
				"bool isInside(float2 pos)"
				"{"
				"	float2 delta = pos - lt_texcoord; "
				"   delta.x = delta.x / (rb_texcoord.x - lt_texcoord.x) - 0.5;"
				"   delta.y = delta.y / (rb_texcoord.y - lt_texcoord.y) - 0.5;"
				"   return length(delta) <= 0.5;"
				"}"
				"float4 main(float4 pos : SV_Position,float4 color : Color,float2 tex : Texcoord ) : SV_Target"
				"{"
				"	if (isInside(tex))"
				"   {"
				"		if (!color.w)"
				"		{"		
				"		   return texcoord.Sample(g_sampler, tex);"
				"		}"
				"		return color; "
				"    }"
				"	clip(-1);"
				"   return color; "
				"}"
			);
		}
		PixelShader* m_pixelShader;
	private:

	};
	class NewCircle : public Shape {
	public:
		NewCircle();
		~NewCircle();
		void setRadius(float r);
		void setTex(Texcoord LT, Texcoord RB);
		void setColor(Color color);
		void create(ShapeBuilder* builder);
	private:
		Vertex2d m_vertices[4];

	};
	NewCircle::NewCircle()
	{
		m_vertices[0].tex = { -1,-1 };
		m_vertices[1].tex = { -1,-1 };
		m_vertices[2].tex = { -1,-1 };
		m_vertices[3].tex = { -1,-1 };
		setRadius(50);
		setColor({ 1,1,1,1 });
	}
	NewCircle::~NewCircle()
	{
		for (int i = 0; i < m_resouceNum; i++) {
			m_resouce[i]->release();
			m_resouce[i] = NULL;
		}
		if (m_resouce) {
			FCT_DELETES(m_resouce);
		}
	}
	void NewCircle::setRadius(float r)
	{
		m_vertices[0].pos = { -r, r };
		m_vertices[1].pos = { -r, -r };
		m_vertices[2].pos = { r, r };
		m_vertices[3].pos = { r, -r };
	}
	void NewCircle::setTex(Texcoord LT, Texcoord RB)
	{
		m_vertices[0].tex = {LT.u,RB.v};
		m_vertices[1].tex = LT;
		m_vertices[2].tex = RB;
		m_vertices[3].tex = { RB.u, LT.v };
	}
	void NewCircle::setColor(Color color)
	{
		m_vertices[0].color = color;
		m_vertices[1].color = color;
		m_vertices[2].color = color;
		m_vertices[3].color = color;
	}
	struct new_circle_vertex_tex_cbuffer {
		Texcoord lt_texcoord;
		Texcoord rb_texcoord;
	};
	void NewCircle::create(ShapeBuilder* builder)
	{
		FCT_SHAPE_CREATE_BEGIN(NewCircle);
		if (m_vertices[0].tex.u < 0) {
			setTex({ 0, 0 }, { 1,1 });
		}
		new_circle_vertex_tex_cbuffer constBuffer;
		constBuffer.lt_texcoord = m_vertices[1].tex;
		constBuffer.rb_texcoord = m_vertices[2].tex;
		m_resouceNum = 4;
		m_resouce = FCT_NEWS(ContextResouce*, 4);
		m_resouce[0] = builder->getContext()->createConstBuffer(1, &constBuffer, sizeof(new_circle_vertex_tex_cbuffer),const_buffer_bind_pixel_shader);
		m_resouce[1] = builder->getContext()->createToplogy(shape_primitive_topology_trianglestrip);
		m_resouce[2] = common->m_pixelShader;
		m_resouce[2]->addRef();
		m_resouce[3] = builder->getContext()->createVertex2dBuffer(m_vertices,4);
	}
}