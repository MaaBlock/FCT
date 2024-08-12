

class TextDevice {
private:
	TextDevice() {}
	~TextDevice() {}
	static TextDevice* m_textDevice;
public:
	static void Init();
	static TextDevice* GetTextDevice();
private:

};

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

inline TextDevice* CreateTextDevice() {
	return TextDevice::GetTextDevice();
}
inline TextDevice* GetTextDevice() {
	return TextDevice::GetTextDevice();
}

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
private:
	bool m_alphaToCoverage = false;
	int m_size;
	const wchar_t* m_text;
	Color m_color;
	Color m_backGroundColor;
	Shape*** m_shape;
	int* m_shapeNum;
	size_t m_textLen;
	Font* m_font;
	float m_x;
	float m_y;
};
class TextOffseter : public RefCounted {
public:
	void setReversal(bool x, bool y);
	void nextLine();
private:
	bool m_xReversal = false;
	//m_xReversal不实现，仅提供该接口，不计划实现
	bool m_yReversal = true;
	float m_offsexX = 0;
	float m_offsexY = 0;
	float scale = 1.0;
};

//ToDo:重构:重写
//ToDo:自己实现读取.ttf和.ttc
