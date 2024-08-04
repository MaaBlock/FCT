#include "hander.h"
using Coord = double;
using N = uint32_t;
#include "earcut.hpp"
namespace mapbox {
	namespace util {

		template <>
		struct nth<0, FCT::Pos2f> {
			inline static auto get(const FCT::Pos2f& t) {
				return t.x;
			};
		};
		template <>
		struct nth<1, FCT::Pos2f> {
			inline static auto get(const FCT::Pos2f& t) {
				return t.y;
			};
		};

	} // namespace util
} // namespace mapbox
namespace FCT {
	
	float Cross(Pos2f edgePoint0, Pos2f edgePoint1, Pos2f point) {
		return Determinant4x4(
			edgePoint0.x, edgePoint0.y, 1, 0,
			edgePoint1.x, edgePoint1.y, 1, 0,
			point.x, point.y, 1, 0,
			0, 0, 0, 1
		);
	}
	bool inTriTest(Pos2f tri0,Pos2f tri1, Pos2f tri2,Pos2f point) {
		if (Cross(
			tri0, tri1, point) * Cross(tri0, tri2, point) < 0 &&
			Cross(tri1, tri2, point) * Cross(tri1, tri0, point) < 0) {
			return true;
		}
		return false;
	}
	void TextPolygon::setRect(int w, int h)
	{
		m_w = w;
		m_h = h;
	}
	void TextPolygon::setColor(Color color)
	{
		m_color = color;
	}
	void TextPolygon::setVertex(Vertex2d* vertexs, size_t vertexNum)
	{
		m_vertex = vertexs;
		m_vertexNum = vertexNum;
	}
	float getX(const Pos2f pos) {
		return pos.x;
	}
	float getY(const Pos2f pos) {
		return pos.y;
	}
	size_t getBegin(const Edge4f edge) {
		return edge.begin;
	}
	size_t getEnd(const Edge4f edge) {
		return edge.end;
	}
	void TextPolygon::create(Context* context)
	{
		m_resouce = new ContextResouce * [1 + m_vertexNum / 3];
		m_resouceNum = 1 + m_vertexNum / 3;
		m_resouce[0] = context->createToplogy(shape_primitive_topology_trianglelist);
		for (int i = 1; i < 1 + m_vertexNum / 3; i++) {
			m_resouce[i] = context->createVertex2dBuffer(m_vertex + (i - 1) * 3, 3);
		}
	}
}