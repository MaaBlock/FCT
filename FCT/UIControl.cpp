#include "hander.h"

namespace FCT {
	Edit::Edit()
	{
		m_shape = FCT_NEW(ComplexShape);
		m_bufferShape = FCT_NEW(ComplexShape);
	}
	void Edit::setFont(Font* font)
	{
		m_font = font;
	}
	void Edit::pos(int x, int y)
	{
		m_x = x;
		m_y = y;
	}
	void Edit::size(int width, int height)
	{
		m_width = width;
		m_height = height;
	}
	void Edit::setColor(Color textColor, Color bkColor)
	{
		m_color = textColor;
		m_bkColor = bkColor;
	}
	void Edit::setText(const wchar_t* text)
	{
		m_data = text;
	}
	void Edit::onChar(wchar_t ch)
	{
		m_data += ch;
		updata();
		flush();
	}
	void Edit::create()
	{
		RectangleGeometry* rectangleGeometry = FCT_NEW(RectangleGeometry);
		rectangleGeometry->w = (float)(m_width);
		rectangleGeometry->h = (float)(m_height);
		setInputShape(rectangleGeometry);
	}
	void Edit::updata()
	{
		m_bufferShape->allDelete();
		Rectangle* rect = FCT_NEW(Rectangle);
		rect->setWidth(m_width);
		rect->setHeight(m_height);
		rect->setColor(m_bkColor);
		rect->create(m_UIManager->getCreateContext());
		m_bufferShape->add(rect, 0, 0);
		Text* text = FCT_NEW(Text);
		text->setText(m_data.c_str());
		text->setFont(m_font);
		text->setColor(m_color, m_bkColor);
		text->setPixelSize(18);
		text->create(m_UIManager->getCreateContext());
		m_bufferShape->add(text, 0, 0);
	}
	void Edit::flush()
	{
		m_mutex->lock();
		Shape* temp;
		temp = m_shape;
		m_shape = m_bufferShape;
		m_bufferShape = (ComplexShape*)temp;
		m_mutex->unlock();
	}
}

