#include "hander.h"
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
	TextPolygon::~TextPolygon()
	{
		destoryResouce();
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
	void TextPolygon::setVertices(Vertex2d* vertexs, size_t vertexNum)
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
		m_resouce = FCT_NEWS(ContextResouce * ,2);
		m_resouceNum = 2;
		m_resouce[0] = context->createToplogy(shape_primitive_topology_trianglelist);
		m_resouce[1] = context->createVertex2dBuffer(m_vertex, m_vertexNum);
	}	
}