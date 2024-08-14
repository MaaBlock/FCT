class Font : public RefCounted {
public:
	Font();
	~Font();
	void create(const char* PathOrName);
	stbtt_fontinfo* getStbFont();
private:
	stbtt_fontinfo* m_fontinfo;
	File* m_fontFile;
};
class Text : public Shape {
public:
	Text();
	~Text();
	void setPixelSize(int height);
	void setalphaToCoverage(bool enable);
	void setColor(Color color,Color backGroundColor);
	void setFont(Font* font);
	void setPosition(float x, float y);
	void setText(const wchar_t* text);
	void predraw(Context* context,int x,int y);
	void create(Context* context);
	void destoryShape();
private:
	bool m_alphaToCoverage = false;
	int m_size;
	const wchar_t* m_text;
	Color m_color;
	Color m_backGroundColor;
	Shape*** m_shape;
	int* m_shapeNum;
	size_t m_charShapesNum = 0;
	Font* m_font;
	float m_x;
	float m_y;
};

class CharShape : public Shape {
public:

private:

};
class StbTextPosTranslator;
class Stencil_CharShape :public CharShape {
public:
	Stencil_CharShape();
	~Stencil_CharShape();
	void setFont(Font* font);
	void destroy();
	void destroyShapes();
	void createCharInfo();
	void destroyCharInfo();
	void setColor(Color color);
	void predraw(Context* context,int x, int y);
	void create(Context* context);
private:
	DepthStencilState* m_depthStencilState;
	RasterizerState* m_rasterizerState;
	BlendState* m_blendState;
	Color m_color;
	Font* m_font;
	Shape** m_shapes;
	size_t m_shapeNum;
	wchar_t m_char;
	StbTextPosTranslator* m_translator;
};
//ToDo:重构:重写
//ToDo:自己实现读取.ttf和.ttc
