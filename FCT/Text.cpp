#define STB_TRUETYPE_IMPLEMENTATION
#include "hander.h"
namespace FCT {
	TextDevice* TextDevice::m_textDevice = NULL;
	void TextDevice::Init()
	{
		m_textDevice = new TextDevice();
	}
	TextDevice* TextDevice::GetTextDevice()
	{
		return m_textDevice;
	}
	Font::Font() : REF_CLASS_INIT()
	{
		m_fontFile = NULL;
	}
	Font::~Font()
	{
		if (m_fontFile) {
			m_fontFile->release();
		}
	}
	void Font::create(const char* PathOrName)
	{
		m_fontFile = CreateFile();
		m_fontinfo = new stbtt_fontinfo;
		m_fontFile->open(PathOrName, "r");
		stbtt_InitFont(m_fontinfo, (const unsigned char*)m_fontFile->getFileStream(), 0);
		return;
	}

	stbtt_fontinfo* Font::getStbFont()
	{
		return m_fontinfo;
	}

	Text::Text()
	{
		m_font = NULL;
		m_shape = NULL;
	}

	Text::~Text()
	{
		FCT_RELEASE(m_font);
	}

	void Text::setColor(Color color, Color backGroundColor)
	{
		m_color = color;
		m_backGroundColor = backGroundColor;
	}

	void Text::setFont(Font* font)
	{
		font->addRef();
		m_font = font;
	}

	void Text::setPosition(float x, float y)
	{
		m_x = x;
		m_y = y;
	}

	void Text::setText(const wchar_t* text)
	{
		m_text = text;
	}

	void Text::predraw(Context* context)
	{

		DepthStencilState* state = context->createResouce->DepthStencilState();
		state->setDepthEnable(false);
		state->setBackFaceStencilFail(stencil_op_invert);
		state->setBackFaceStencilPass(stencil_op_invert);
		state->setBackFaceStencilFailDepth(stencil_op_invert);
		state->setFrontFaceStencilFail(stencil_op_invert);
		state->setFrontFaceStencilPass(stencil_op_invert);
		state->setFrontFaceStencilFailDepth(stencil_op_invert);
		state->setBackFaceStencilFunc(stencil_func_equal);
		state->setFrontFaceStencilFunc(stencil_func_equal);
		state->setRefStencil(0);
		RasterizerState* rasterizerState = context->createResouce->RasterizerState();
		rasterizerState->setCullMode(cull_mode_none);
		rasterizerState->create(context);
		context->setDeafultResouce(rasterizerState);
		context->setDeafultResouce(state);
		for (int i = 0; i < m_textLen; i++) {
			for (int j = 0; j < m_shapeNum[i] - 1; j++) {
				context->draw(m_shape[i][j], m_x, m_y);
			}
		}
		DepthStencilState* fillState = context->createResouce->DepthStencilState();
		fillState->setRefStencil(255);
		fillState->setDepthEnable(false);
		fillState->setStencilEnable(true);
		fillState->setBackFaceStencilFunc(stencil_func_notequal);
		fillState->setFrontFaceStencilFunc(stencil_func_notequal);
		fillState->setBackFaceStencilFail(stencil_op_keep);
		fillState->setBackFaceStencilPass(stencil_op_keep);
		fillState->setFrontFaceStencilFail(stencil_op_keep);
		fillState->setFrontFaceStencilPass(stencil_op_keep);
		context->setDeafultResouce(fillState);
		for (int i = 0; i < m_textLen; i++) {
			context->draw(m_shape[i][m_shapeNum[i] - 1], m_x, m_y);
		}
		context->setDeafultResouce(rasterizerState->getResouceType(), NULL);
		context->setDeafultResouce(state->getResouceType(), NULL);

	}
	struct text_offset_src_t {
		int ascent;
		int descent;
		int lineGap;
		int linehight;
	};
	class Offset : public RefCounted {
	public:
		Offset(const wchar_t* text) : m_text(text) {
		}
		float scaleSrcX(float srcX) { 
			float originX = 0;
			float originY = m_src.descent;
			return (srcX - originX) * m_scaleX + originX;
		}
		float scaleSrcY(float srcY) { 
			float originX = 0;
			float originY = m_src.descent;
			return (srcY - originY) * m_scaleY + originY;
		}
		float scaleMovX(float srcX) {
			return srcX * m_scaleX;
		}
		float scaleMovY(float srcY) {
			return srcY * m_scaleY;
		}
		void setStbFont(stbtt_fontinfo* font) {
			m_font = font;
			stbtt_GetFontVMetrics(font, &m_src.ascent, 
				&m_src.descent, &m_src.lineGap);
			m_src.linehight = m_src.ascent - 
				m_src.descent + m_src.lineGap;
			textSize(30);
		}
		void offsetText(size_t index,float& offsetX, float& offsetY) {
			offsetX = m_offsetX + scaleSrcX(offsetX);
			offsetY = scaleMovY(m_src.linehight) - scaleSrcY(offsetY)
				+ scaleSrcY(m_src.descent);
		}
		void textSize(int pixelHeight) {
			m_scaleY = stbtt_ScaleForPixelHeight(m_font, pixelHeight);
			m_scaleX = m_scaleY;
			return;
		}
		void setRect(int w,int h) {
			
		}
		void offsetFillRect(size_t index,Rectangle*& rectangle) {
			int advance, lsb;
			stbtt_GetCodepointHMetrics(m_font, m_text[index], &advance, &lsb);
			//处理rectangle
			rectangle->setRect(scaleSrcX(advance), scaleMovY(m_src.linehight));
			rectangle->setOffset(m_offsetX, m_offsetY);
			//finsh;
			m_offsetX += scaleSrcX(advance);
			if (false/*换行*/) {
				m_offsetX = 0;
				m_offsetY += m_src.linehight;
			}
		}
	private:
		int m_dstWidth;
		int m_dstHeight;
		float m_scaleX = 1.0f;
		float m_scaleY = 1.0f;
		text_offset_src_t m_src;
		int m_offsetX;
		int m_offsetY;
		unsigned m_line = 0;
		const wchar_t* m_text;
		stbtt_fontinfo* m_font;
	};
	void Text::create(Context* context)
	{
		stbtt_fontinfo* font = m_font->getStbFont();
		Offset* offset = new Offset(m_text);
		offset->setStbFont(font);
		m_textLen = wcslen(m_text);
		m_shape = new Shape * *[m_textLen];
		m_shapeNum = new int[m_textLen];
		int chId = 0;
		for (int i = 0; i < m_textLen; i++) {
			m_shapeNum[i] = 0;
		}
		Vertex2d* TriangledVertexs;
		Pos2f TriangleFirstVertex;
		size_t TriangledVertexNums;
		for (const wchar_t* ch = m_text; *ch != L'\0'; ch++, chId++) {
			stbtt_vertex* stbVertex = NULL;
			int verCount = 0;
			verCount = stbtt_GetCodepointShape(font, *ch, &stbVertex);
			TriangledVertexs = new Vertex2d[verCount * 3];//精确值:3 * (verCount - moveNum * 2)
			TriangledVertexNums = 0;
			m_shape[chId] = new Shape * [verCount + 2];
			std::wcout << L"开始处理 [" << *ch << L"]" << std::endl;
			Pos2f current;
			Pos2f previous;
			Pos2f control;
			for (int i = 0; i < verCount; i++) {
				stbtt_vertex* stbVer = ((stbtt_vertex*)stbVertex + i);
				switch (stbVer->type)
				{
				case STBTT_vmove: {
					previous.x = stbVer->x;
					previous.y = stbVer->y;
					offset->offsetText(chId,previous.x, previous.y);
					if (previous.y < 0) {
						std::cout << " < 0 :" << previous.y;
						std::cout << std::endl;
					}
					TriangleFirstVertex = previous;
					break;
				}
				case STBTT_vline: {
					current.x = stbVer->x;
					current.y = stbVer->y;
					offset->offsetText(chId,current.x, current.y);
					if (previous.y < 0) {
						std::cout << " < 0 :" << previous.y;
						std::cout << std::endl;
					}
					m_shape[chId][m_shapeNum[chId]] = new Line;
					Line* line = (Line*)m_shape[chId][m_shapeNum[chId]];
					line->setOffset(previous.x, previous.y);
					line->setPoint(current.x - previous.x, current.y - previous.y);
					line->setColor(m_color);
					line->create(context);
					m_shapeNum[chId]++;
					if (previous == TriangleFirstVertex) {
						previous = current;
						break;
					}
					TriangledVertexs[TriangledVertexNums].set(TriangleFirstVertex, m_color
						, { -1,-1 });
					TriangledVertexNums++;
					TriangledVertexs[TriangledVertexNums].set(previous, m_color
						, { -1,-1 });
					TriangledVertexNums++;
					TriangledVertexs[TriangledVertexNums].set(current, m_color
						, { -1,-1 });
					TriangledVertexNums++;
					previous = current;
					break;
				}
				case STBTT_vcurve: {
					current.x = stbVer->x;
					current.y = stbVer->y;
					offset->offsetText(chId,current.x, current.y);
					control.x = stbVer->x;
					control.y = stbVer->y;
					offset->offsetText(chId,control.x, control.y);
					m_shape[chId][m_shapeNum[chId]] = new TextFullQuadraticBezierCurve2d;
					TextFullQuadraticBezierCurve2d* bezier = (TextFullQuadraticBezierCurve2d*)m_shape[chId][m_shapeNum[chId]];
					bezier->setOffset(previous.x, previous.y);
					bezier->setBeginPoint(0, 0);
					bezier->setControlPoint(control.x - previous.x, control.y - previous.y);
					bezier->setEndPoint(current.x - previous.x, current.y - previous.y);
					bezier->setColor(m_color);
					bezier->create(context);
					m_shapeNum[chId]++;
					if (previous == TriangleFirstVertex) {
						previous = current;
						break;
					}
					TriangledVertexs[TriangledVertexNums].set(TriangleFirstVertex, m_color
						, { -1,-1 });
					TriangledVertexNums++;
					TriangledVertexs[TriangledVertexNums].set(previous, m_color
						, { -1,-1 });
					TriangledVertexNums++;
					TriangledVertexs[TriangledVertexNums].set(current, m_color
						, { -1,-1 });
					TriangledVertexNums++;
					previous = current;
					break;
				}
				case STBTT_vcubic:
					std::wcout << L"warning: there is cubic when draw " << *ch << std::endl;
					break;
				default:
					break;
				}
			}
			m_shape[chId][m_shapeNum[chId]] = new TextPolygon;
			TextPolygon* polygon = (TextPolygon*)m_shape[chId][m_shapeNum[chId]];
			polygon->setColor(m_color);
			polygon->setVertex(TriangledVertexs, TriangledVertexNums);
			polygon->create(context);
			m_shapeNum[chId]++;
			Rectangle* rectangle = new Rectangle;
			offset->offsetFillRect(chId, rectangle);
			rectangle->setColor(m_backGroundColor);
			rectangle->create(context);
			m_shape[chId][m_shapeNum[chId]] = rectangle;
			m_shapeNum[chId]++;
			delete[] stbVertex;
			delete[] TriangledVertexs;
		}
		m_resouceNum = 0;
	}
}
