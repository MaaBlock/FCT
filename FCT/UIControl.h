
class Label : public UIControlBase {
public:

private:
	const wchar_t* m_data;

};


class Edit : public UIControlBase {
public:
	Edit();
	~Edit();
	void setFont(Font* font);
	void pos(int x, int y);
	void size(int width,int height);
	void setColor(Color textColor, Color bkColor);

	void setText(const wchar_t* text);
	void onChar(wchar_t ch);
	void create();
	void updata();
	void flush();
private:
	Color m_color = { 0,0,0,1 };
	Color m_bkColor = { 1,1,1,1 };
	int m_x, m_y, m_width, m_height;
	Font* m_font;
	ComplexShape* m_bufferShape;
	std::wstring m_data;
};

class CodeEdit {

};

