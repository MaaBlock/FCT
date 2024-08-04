struct Pos3f {
	float x;
	float y;
	float z;
}; 
struct Pos2f {
	float x;
	float y;
	bool operator==(const Pos2f pos) {
		return (pos.x == x && pos.y == y);
	}
};
struct Pos2d {
	int x;
	int y;
};
struct Color {
	float r;
	float g;
	float b;
	float a;
};
struct Texcoord {
	float u;
	float v;
};
struct Vertex {
	Pos3f pos;
	Color color;
	Texcoord tex;
};
struct Vertex2d {
	Pos2f pos;
	Color color;
	Texcoord tex;
	void set(Pos2f pos, Color color, Texcoord tex) {
		this->pos = pos;
		this->color = color;
		this->tex = tex;
	}
};
Vertex2d setVertex2d(Vertex2d& vertex,Pos2f pos, Color color, Texcoord tex);