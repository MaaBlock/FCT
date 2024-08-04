

class Shape : public RefCounted {
public:
	Shape();
	ContextResouce** m_resouce;
	virtual void predraw(Context* context) {

	}
	virtual void setOffset(float x, float y) {
		m_offsetX = x;
		m_offserY = y;
	}
	float getOffsetX() {
		return m_offsetX;
	}
	float getOffsetY() {
		return m_offserY;
	}
	int m_resouceNum;
protected:
	float m_offsetX = 0;
	float m_offserY = 0;
};

class Line : public Shape
{
public:
	Line();
	~Line();
	void setPoint(float x, float y);
	void setColor(Color color);
	void create(Context* context);
private:
	Vertex2d m_vertices[2];
};
class Rectangle : public Shape {
public:
	Rectangle();
	void setWidth(int w);
	void setHeight(int h);
	inline void setColor(Color color) {
		setTLColor(color);
		setBLColor(color);
		setTRColor(color);
		setBRColor(color);
	}
	void setRect(int w, int h) {
		setWidth(w);
		setHeight(h);
	}
	void setTLColor(Color color) { //Top Left
		m_vertexs[1].color = color;
	}
	void setBLColor(Color color) {//Bottom Left
		m_vertexs[0].color = color;
	}
	void setTRColor(Color color) {//Top Right
		m_vertexs[3].color = color;
	}
	void setBRColor(Color color) {//Bottom Right
		m_vertexs[2].color = color;
	}
	void setTexcoord(float u0, float v0, float u1, float v1) {
		m_vertexs[0].tex = { u0 ,v1 };
		m_vertexs[1].tex = { u0 ,v0 };
		m_vertexs[2].tex = { u1 ,v1 };
		m_vertexs[3].tex = { u1 ,v0 };
	}
	void create(Context* context);
private:
	Vertex2d m_vertexs[4];
	float m_w;
	float m_h;
};
class Circle : public Shape {
public:
	Circle();
	void create(Context* context);
	void setR(float r);
	void setColor(Color color);
	void setColor(Color centerColor,Color surroundColor);
	void setTexcoord(float u1, float v1, float u2, float v2);
private:
	float m_r;
	float m_u1, m_v1;
	float m_u2, m_v2;
	Color m_surroundColor;
	Color m_centerColor;
	int m_vertexSize = 720;

};

class QuadraticBezierCurve2d : public Shape {
public:
	QuadraticBezierCurve2d();
	void create(Context* context);
	void setBeginPoint(float x, float y);
	void setEndPoint(float x, float y);
	void setControlPoint(float x, float y);
	inline void setP0(float x, float y) {
		setBeginPoint(x, y);
	}
	inline void setP1(float x, float y) {
		setControlPoint(x, y);
	}
	inline void setP2(float x, float y) {
		setEndPoint(x, y);
	}
	void setColor(Color color);
	void setWidth(float width);
private:
	Vertex2d m_vertex[3];
	float m_width;
};
class TextFullQuadraticBezierCurve2d : public Shape {
public:
	TextFullQuadraticBezierCurve2d();
	void create(Context* context);
	void setBeginPoint(float x, float y);
	void setEndPoint(float x, float y);
	void setControlPoint(float x, float y);
	inline void setP0(float x, float y) {
		setBeginPoint(x, y);
	}
	inline void setP1(float x, float y) {
		setControlPoint(x, y);
	}
	inline void setP2(float x, float y) {
		setEndPoint(x, y);
	}
	void setColor(Color color);
	void setWidth(float width);
private:
	Vertex2d m_vertex[3];
	float m_width;
};

class ComplexShape : public Shape {
public:
	ComplexShape();
	void create(Context* context);
	void add(Shape* shape,int x,int y); 
private:

};
struct Edge4f {
	size_t begin;
	size_t end;
};
//多边形，采用Bowyer-Watson算法进行三角形剖分
class TextPolygon : public Shape {
public:
	void setRect(int w, int h);
	void setColor(Color color);
	void setVertex(Vertex2d* vertexs, size_t vertexNum);
	void create(Context* context);
private:
	Color m_color;
	Vertex2d* m_vertex;
	size_t m_vertexNum;
	float m_w;
	float m_h;
};


