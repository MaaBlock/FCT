class Geometry : public RefCounted {
public:
	virtual void traversal(void (*func)(void* param, int x, int y),void* param,int cx,int cy) = 0;
};

class CircleGeometry : public Geometry {
public:
	int r;
	void traversal(void (*func)(void* param, int x, int y), void* param, int cx, int cy);
};

class EllipseGeometry : public Geometry {
public:
	int rx, ry;
	void traversal(void (*func)(void* param, int x, int y), void* param, int cx, int cy);
};


class RectangleGeometry : public Geometry {
public:
	int w;
	int h;
	void traversal(void (*func)(void* param, int x, int y), void* param, int cx, int cy);
};