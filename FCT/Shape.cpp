#include "hander.h"
#define FCT_PI 3.14159265358979323846
namespace FCT {
	Line::Line()
	{
		m_vertices[1].tex = {-1,-1};
		m_vertices[0].pos = {0,0};
		m_vertices[0].tex = {-1,-1};
	}

	Line::~Line()
	{
		destoryResouce();
	}
	void Line::setPoint(float x, float y)
	{
		m_vertices[1].pos = {x,y};
	}
	void Line::setColor(Color color)
	{
		m_vertices[0].color = color;
		m_vertices[1].color = color;
	}
	void Line::create(Context* context)
	{
		m_resouce = FCT_NEWS(ContextResouce*,2);
		m_resouce[0] = context->createToplogy(shape_primitive_topology_linelist);
		m_resouce[1] = context->createVertex2dBuffer(m_vertices, 2);
		m_resouceNum = 2;
	}
	Circle::Circle()
	{
		REF_CLASS_BEGIN();
		m_r = 5;
		m_centerColor = {0,0,0,1};
		m_surroundColor = { 0,0,0,1 };
		m_u1 = -1;
		m_v1 = -1;
		m_u2 = -1;
		m_v2 = -1;
	}
	void Circle::create(Context* context)
	{
		const int numSegments = 360;
		const int numSegments_2 = 180;
		const int vertexnum = numSegments * 2 + 1;
		m_vertexSize = vertexnum;
		Vertex2d vertices[vertexnum];
		for (int i = 0; i < numSegments_2; i++) {
			vertices[i * 4].pos = {0 , 0 };
			vertices[i * 4].color = m_centerColor;
			vertices[i * 4].tex = { (m_u1 + m_u2) / 2, (m_v1 + m_v2) / 2 };
			float angle = (float)(3 * i) / numSegments * 2 * FCT_PI;
			vertices[i * 4 + 1].pos = { m_r * cos(angle), m_r * sin(angle) };
			vertices[i * 4 + 1].color = m_surroundColor;
			vertices[i * 4 + 1].tex = { (m_u1 + m_u2) / 2, (m_v1 + m_v2) / 2 };
			angle = (float)(3 * i + 1) / numSegments * 2 * FCT_PI;
			vertices[i * 4 + 2].pos = { m_r * cos(angle), m_r * sin(angle) };
			vertices[i * 4 + 2].color = m_surroundColor;
			vertices[i * 4 + 2].tex = { (m_u1 + m_u2) / 2, (m_v1 + m_v2) / 2 };
			angle = (float)(3 * i + 2) / numSegments * 2 * FCT_PI;
			vertices[i * 4 + 3].pos = { m_r * cos(angle), m_r * sin(angle) };
			vertices[i * 4 + 3].color = m_surroundColor;
			vertices[i * 4 + 3].tex = { (m_u1 + m_u2) / 2, (m_v1 + m_v2) / 2 };
		}
		RasterizerState* cr;
		cr = context->createResouce->RasterizerState();
		cr->setCullMode(cull_mode_none);
		cr->create(context);
		m_resouce = FCT_NEWS(ContextResouce*,3);
		m_resouce[0] = context->createToplogy(shape_primitive_topology_trianglestrip);
		m_resouce[1] = context->createToplogy(shape_primitive_topology_trianglestrip);
		m_resouce[2] = context->createVertex2dBuffer(vertices, vertexnum);
		m_resouceNum = 3;
	}
	void Circle::setR(float r)
	{
		m_r = r;
	}

	void Circle::setColor(Color color)
	{
		setColor(color, color);
	}

	void Circle::setColor(Color centerColor, Color surroundColor)
	{
		m_centerColor = centerColor;
		m_surroundColor = surroundColor;
	}

	void Circle::setTexcoord(float u1, float v1, float u2, float v2)
	{
		m_u1 = u1;
		m_v1 = v1;
		m_u2 = u2;
		m_v2 = v2;
	}
	struct QuadraticBezierCurve2dConstBuffer {
		Pos2f vertex[3];
		float width;
		float place;//多一个占位，必须为16的倍数
	};
	QuadraticBezierCurve2d::QuadraticBezierCurve2d()
	{
		REF_CLASS_BEGIN();
		m_vertex[0].tex = { 0,0 };
		m_vertex[1].tex = { 0.5f,0 };
		m_vertex[2].tex = { 1,1 };
		m_width = 2;
	}
	void QuadraticBezierCurve2d::create(Context* context)
	{
		m_resouceNum = 5;
		m_resouce = FCT_NEWS(ContextResouce*, 5);
		QuadraticBezierCurve2dConstBuffer constBuffer;
		constBuffer.vertex[0] = m_vertex[0].pos;
		constBuffer.vertex[1] = m_vertex[1].pos;
		constBuffer.vertex[2] = m_vertex[2].pos;
		constBuffer.width = m_width;
		m_resouce[0] = context->createConstBuffer(1, &constBuffer, sizeof(QuadraticBezierCurve2dConstBuffer), const_buffer_bind_vertex_shader | const_buffer_bind_pixel_shader | const_buffer_bind_geometry_shader);
		m_resouce[1] = context->createToplogy(shape_primitive_topology_trianglelist);
		m_resouce[2] = context->createPixelShader(
			"Texture2D texcoord : register(t0);\n"
			"SamplerState g_sampler : register(s0);\n"
			"cbuffer Bezier : register(b1)"
			"{"
			"	float2 srcBeginPoint;\n"
			"	float2 srcControlPoint;\n"
			"	float2 srcEndPoint;\n"
			"	float width;"	
			"}"
			"struct Bezier"
			"{"
			"	float2 beginPoint;\n"
			"	float2 controlPoint;\n"
			"	float2 endPoint;\n"
			"};"															 
			"float aastep(float edge, float v)								 "
			"{																	 "
			"	float fwidth = 0.7 * length(float2(ddx(v), ddy(v)));			 "
			"	return smoothstep(edge - fwidth, edge + fwidth, v);				 "
			"}																	 "
			"float4 main(float4 pos : SV_Position,float4 color : Color,float2 tex : Texcoord,Bezier bez : Bezier ) : SV_Target\n"
			"{\n"
			"   float d = (tex.x * tex.x - tex.y);"
			"	float2 grad = float2(ddx(d), ddy(d));"
			"	d /= length(grad);												 "
			"	return float4(color.x, color.y, color.z, 1.0f - aastep(width / 2, abs(d)));		 "
			"}"
		);
		m_resouce[3] = context->createVertexShader(

			"cbuffer TargetSize : register(b0)"
			"{"
			"float2 WindowSize;"
			"float2 ShapePos;"
			"}"
			"cbuffer BezierData : register(b1)\n"
			"{\n"
			"float2 beginPoint;\n"
			"float2 controlPoint;\n"
			"float2 endPoint;\n"
			"float width;"
			"}\n"
			"Texture2D texcoord : register(t0);"
			"struct Bezier"
			"{"
			"	float2 beginPoint;\n"
			"	float2 controlPoint;\n"
			"	float2 endPoint;\n"
			"};"
			"struct TransVer"
			"{"
			"float4 pos : SV_Position;"
			"float4 color : Color;"
			"float2 tex : Texcoord;"
			"Bezier bez : Bezier;"
			"};"
			"float toWorldX(float x) "
			"{"
			"	return (x + ShapePos.x) / WindowSize.x * 2 - 1;"
			"}"
			"float toWorldY(float y)"
			"{"
			"	return -((y + ShapePos.y) / WindowSize.y * 2) + 1;"
			"}"
			"float2 toWorld(float2 pos)"
			"{"
			"	return float2(toWorldX(pos.x),toWorldY(pos.y));"
			"}"
			"TransVer main(float4 color : Color,float2 pos : Position,float2 tex : Texcoord)"
			"{"
			"	TransVer ret;"
			"	ret.pos = float4(toWorldX(pos.x),toWorldY(pos.y),0,1.0f);"
			"	ret.color = color;"
			"	ret.tex = tex;"
			"	ret.bez.beginPoint	 = toWorld(beginPoint);"
			"	ret.bez.controlPoint = toWorld(controlPoint);"
			"	ret.bez.endPoint	 = toWorld(endPoint);"
			"	return ret;"
			"}"
		);
		/**
		m_resouce[4] = context->createResouce->GeometryShader();

		((GeometryShader*)m_resouce[4])->setCode(
		"struct Bezier"
		"{"
		"	float2 beginPoint;\n"
		"	float2 controlPoint;\n"
		"	float2 endPoint;\n"
		"};"
		"struct TransVer"
		"{"
		"float4 pos : SV_Position;"
		"float4 color : Color;"
		"float2 tex : Texcoord;"
		"Bezier bez : Bezier;"
		"};"
		"cbuffer BezierData : register(b1)"
		"{"
		"	float2 srcBeginPoint;\n"
		"	float2 srcControlPoint;\n"
		"	float2 srcEndPoint;\n"
		"	float width;"
		"}"
		"[maxvertexcount(21)]"
		"void main(triangle TransVer input[3],inout TriangleStream<TransVer> output)"
		"{"
		"	for (int i = 0;i < 3;i++){\n"
		"		output.Append(input[i]);\n"
		"	}\n"
		"	TransVer vertex[3];\n"
		"	float4 g_pos = (input[0].pos + input[1].pos + input[2].pos)/3;\n"
		"	float2 g_tex = (input[0].tex + input[1].tex + input[2].tex)/3;\n"
		"	float4 direction = input[0].pos - input[1].pos;\n"
		"	vertex[0].color = input[0].color;\n"
		"	vertex[1].color = input[1].color;\n"
		"	vertex[2].color = input[2].color;\n"
		"	vertex[0].bez =input[0].bez; "
		"	vertex[1].bez =input[0].bez; "
		"	vertex[2].bez =input[0].bez; "
		"	vertex[0].pos = width *input[0].pos - width*g_pos + g_pos;"
		"	vertex[1].pos = width *input[1].pos - width*g_pos + g_pos;"
		"	vertex[2].pos = width *input[2].pos - width*g_pos + g_pos;"
		"	vertex[0].tex = 3*input[0].tex -2*g_tex;"
		"	vertex[1].tex = 3*input[1].tex -2*g_tex;"
		"	vertex[2].tex = 3*input[2].tex -2*g_tex;"
		"	output.Append(vertex[0]);"
		"	output.Append(input[0]);"
		"	output.Append(input[1]);"
		"   output.RestartStrip();"
		"	output.Append(vertex[0]);"
		"	output.Append(input[0]);"
		"	output.Append(input[2]);"
		"   output.RestartStrip();"
		"	output.Append(vertex[1]);"
		"	output.Append(input[1]);"
		"	output.Append(input[2]);"
		"   output.RestartStrip();"
		"	output.Append(vertex[1]);"
		"	output.Append(input[1]);"
		"	output.Append(input[0]);"
		"   output.RestartStrip();"
		"	output.Append(vertex[2]);"
		"	output.Append(input[2]);"
		"	output.Append(input[0]);"
		"   output.RestartStrip();"
		"	output.Append(vertex[2]);"
		"	output.Append(input[2]);"
		"	output.Append(input[1]);"
		"   output.RestartStrip();"
		"	"
		"}");
		((GeometryShader*)m_resouce[4])->create(context);
		*/
		m_resouce[4] = context->createVertex2dBuffer(m_vertex, 3);
	}
	void QuadraticBezierCurve2d::setBeginPoint(float x, float y)
	{
		m_vertex[0].pos = { x,y };
	}
	void QuadraticBezierCurve2d::setEndPoint(float x, float y)
	{
		m_vertex[2].pos = { x,y };
	}
	void QuadraticBezierCurve2d::setControlPoint(float x, float y)
	{
		m_vertex[1].pos = { x,y };
	}
	void QuadraticBezierCurve2d::setColor(Color color)
	{
		for (int i = 0; i < 3; i++) {
			m_vertex[i].color = color;
		}
	}
	void QuadraticBezierCurve2d::setWidth(float width)
	{
		m_width = width;
	}
	Shape::Shape()
	{
		m_resouce = NULL;
		m_resouceNum = NULL;
	}
	TextFullQuadraticBezierCurve2d::TextFullQuadraticBezierCurve2d()
	{
		REF_CLASS_BEGIN();
		m_vertex[0].tex = { 0,0 };
		m_vertex[1].tex = { 0.5f,0 };
		m_vertex[2].tex = { 1,1 };
		m_width = 2;
	}
	TextFullQuadraticBezierCurve2d::~TextFullQuadraticBezierCurve2d()
	{
		destoryResouce();
	}
	void TextFullQuadraticBezierCurve2d::create(Context* context)
	{
		m_resouceNum = 5;
		m_resouce = FCT_NEWS(ContextResouce * ,5);
		QuadraticBezierCurve2dConstBuffer constBuffer;
		constBuffer.vertex[0] = m_vertex[0].pos;
		constBuffer.vertex[1] = m_vertex[1].pos;
		constBuffer.vertex[2] = m_vertex[2].pos;
		constBuffer.width = m_width;
		m_resouce[0] = context->createConstBuffer(1, &constBuffer, sizeof(QuadraticBezierCurve2dConstBuffer), const_buffer_bind_vertex_shader | const_buffer_bind_pixel_shader | const_buffer_bind_geometry_shader);
		m_resouce[1] = context->createToplogy(shape_primitive_topology_trianglelist);
		m_resouce[2] = Directx11_TextBezierPixelShader;
		Directx11_TextBezierPixelShader->addRef();
		m_resouce[3] = Directx11_TextBezierVertexShader;
		Directx11_TextBezierVertexShader->addRef();
		m_resouce[4] = context->createVertex2dBuffer(m_vertex, 3);
	}
	void TextFullQuadraticBezierCurve2d::setBeginPoint(float x, float y)
	{
		m_vertex[0].pos = { x,y };
	}
	void TextFullQuadraticBezierCurve2d::setEndPoint(float x, float y)
	{
		m_vertex[2].pos = { x,y };
	}
	void TextFullQuadraticBezierCurve2d::setControlPoint(float x, float y)
	{
		m_vertex[1].pos = { x,y };
	}
	void TextFullQuadraticBezierCurve2d::setColor(Color color)
	{
		for (int i = 0; i < 3; i++) {
			m_vertex[i].color = color;
		}
	}
	void TextFullQuadraticBezierCurve2d::Init(Context* context)
	{
		if (!Directx11_TextBezierPixelShader) {
			Directx11_TextBezierPixelShader = context->createPixelShader(
				"Texture2D texcoord : register(t0);\n"
				"SamplerState g_sampler : register(s0);\n"
				"cbuffer Bezier : register(b1)"
				"{"
				"	float2 srcBeginPoint;\n"
				"	float2 srcControlPoint;\n"
				"	float2 srcEndPoint;\n"
				"	float width;"
				"}"
				"struct Bezier"
				"{"
				"	float2 beginPoint;\n"
				"	float2 controlPoint;\n"
				"	float2 endPoint;\n"
				"};"
				"float aastep(float edge, float v)								 "
				"{																	 "
				"	float fwidth = 0.7 * length(float2(ddx(v), ddy(v)));			 "
				"	return smoothstep(edge - fwidth, edge + fwidth, v);				 "
				"}																	 "
				"float4 main(float4 pos : SV_Position,float4 color : Color,float2 tex : Texcoord,Bezier bez : Bezier ) : SV_Target\n"
				"{\n"
				"   float d = (tex.x * tex.x - tex.y);"
				"	return float4(color.x, color.y, color.z,d <= 0 ? 1 :0);"
				//"	if (determinant(float4x4("
				//"bez.beginPoint.x	,bez.beginPoint.y	,1,0,"
				//"bez.controlPoint.x	,bez.controlPoint.y	,1,0,"
				//"bez.endPoint.x		,bez.endPoint.y		,1,0,"
				//"0,0,0,1"
				//")) > 0) {"
				//"		return float4(color.x, color.y, color.z,d >= 0 ? 1 :0);		 "
				//"	}"
				//"	return float4(color.x, color.y, color.z,d <= 0 ? 1 : 0);		 "
				"}"
			);
		}
		if (!Directx11_TextBezierVertexShader) {
			Directx11_TextBezierVertexShader = context->createVertexShader(
				"cbuffer TargetSize : register(b0)"
				"{"
				"float2 WindowSize;"
				"float2 ShapePos;"
				"}"
				"cbuffer BezierData : register(b1)\n"
				"{\n"
				"float2 beginPoint;\n"
				"float2 controlPoint;\n"
				"float2 endPoint;\n"
				"float width;"
				"}\n"
				"Texture2D texcoord : register(t0);"
				"struct Bezier"
				"{"
				"	float2 beginPoint;\n"
				"	float2 controlPoint;\n"
				"	float2 endPoint;\n"
				"};"
				"struct TransVer"
				"{"
				"float4 pos : SV_Position;"
				"float4 color : Color;"
				"float2 tex : Texcoord;"
				"Bezier bez : Bezier;"
				"};"
				"float toWorldX(float x) "
				"{"
				"	return (x + ShapePos.x) / WindowSize.x * 2 - 1;"
				"}"
				"float toWorldY(float y)"
				"{"
				"	return -((y + ShapePos.y) / WindowSize.y * 2) + 1;"
				"}"
				"float2 toWorld(float2 pos)"
				"{"
				"	return float2(toWorldX(pos.x),toWorldY(pos.y));"
				"}"
				"TransVer main(float4 color : Color,float2 pos : Position,float2 tex : Texcoord)"
				"{"
				"	TransVer ret;"
				"	ret.pos = float4(toWorldX(pos.x),toWorldY(pos.y),0,1.0f);"
				"	ret.color = color;"
				"	ret.tex = tex;"
				"	ret.bez.beginPoint	 = toWorld(beginPoint);"
				"	ret.bez.controlPoint = toWorld(controlPoint);"
				"	ret.bez.endPoint	 = toWorld(endPoint);"
				"	return ret;"
				"}"
			);
		}
	}
	Rectangle::Rectangle()
	{
		m_vertexs[0].color = { 1,1,1,1 };
		m_vertexs[1].color = { 1,1,1,1 };
		m_vertexs[2].color = { 1,1,1,1 };
		m_vertexs[3].color = { 1,1,1,1 };
		m_vertexs[0].tex = { -1,-1 };
		m_vertexs[1].tex = { -1,-1 };
		m_vertexs[2].tex = { -1,-1 };
		m_vertexs[3].tex = { -1,-1 };
		m_vertexs[0].pos = { 0,50 };
		m_vertexs[1].pos = { 50,50 };
		m_vertexs[2].pos = { 0,0 };
		m_vertexs[3].pos = { 50,0 };
		m_w = 50;
		m_h = 50;
	}
	Rectangle::~Rectangle()
	{
		destoryResouce();
	}
	void Rectangle::setWidth(int w)
	{
		m_w = w;
	}
	void Rectangle::setHeight(int h)
	{
		m_h = h;
	}
	void Rectangle::create(Context* context)
	{
		m_vertexs[0].pos = { 0,m_h };
		m_vertexs[1].pos = { 0,0 };
		m_vertexs[2].pos = { m_w,m_h };
		m_vertexs[3].pos = { m_w,0 };
		m_resouceNum = 2;
		m_resouce = FCT_NEWS(ContextResouce * ,2);
		m_resouce[0] = context->createToplogy(shape_primitive_topology_trianglestrip);
		m_resouce[1] = context->createVertex2dBuffer(m_vertexs, 4);
	}

	ComplexShape::ComplexShape()
	{

	}

	ComplexShape::~ComplexShape()
	{
		allDelete();
	}

	void ComplexShape::predraw(Context* context,int x,int y)
	{
		for (auto i = m_shapes.begin(); i != m_shapes.end(); i++) {
			context->draw((*i)->shape, x + (*i)->x,y + (*i)->y);
		}
	}

	void ComplexShape::create(Context* context)
	{

	}
	void ComplexShape::add(Shape* shape, int x, int y)
	{
		ComplexShapeNode* shape_node = FCT_NEW(ComplexShapeNode);
		shape->addRef();
		shape_node->shape = shape;
		shape_node->x = x;
		shape_node->y = y;
		m_shapes.push_back(shape_node);
	}
	void ComplexShape::remove(Shape* shape)
	{

	}
	void ComplexShape::allDelete()
	{
		for (auto i = m_shapes.begin(); i != m_shapes.end(); i++) {
			ComplexShapeNode* shapeNode = *i;
			shapeNode->shape->release();
			FCT_DELETE(shapeNode);
		}
		m_shapes.clear();
	}
	VertexShader* TextFullQuadraticBezierCurve2d::Directx11_TextBezierVertexShader = NULL;
	PixelShader* TextFullQuadraticBezierCurve2d::Directx11_TextBezierPixelShader = NULL;
	void InitShapeModule(Context* context)
	{
		TextFullQuadraticBezierCurve2d::Init(context);
	}
}