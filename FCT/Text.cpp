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
		m_fontinfo = NULL;
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
		destoryShape();
	}

	void Text::setPixelSize(int height)
	{
		m_size = height;
	}

	void Text::setalphaToCoverage(bool enable)
	{
		m_alphaToCoverage = enable;
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

	void Text::predraw(Context* context,int x,int y)
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
		BlendState* blendState = context->createResouce->BlendState();
		blendState->alphaToCoverage(m_alphaToCoverage);
		context->setDeafultResouce(blendState);	
		context->setDeafultResouce(rasterizerState);
		context->setDeafultResouce(state);
		for (int i = 0; i < m_charShapesNum; i++) {
			for (int j = 0; j < m_shapeNum[i] - 1; j++) {
				context->draw(m_shape[i][j], x, y);
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
		for (int i = 0; i < m_charShapesNum; i++) {
			if (m_shape[i]) {
				context->draw(m_shape[i][m_shapeNum[i] - 1], x, y);
			}
		}
		context->setDeafultResouce(rasterizerState->getResouceType(), NULL);
		context->setDeafultResouce(state->getResouceType(), NULL);
		context->setDeafultResouce(blendState->getResouceType(), NULL);
		fillState->release();
		state->release();
		rasterizerState->release();
		blendState->release();
	}

	struct text_offset_src_t {
		int ascent;
		int descent;
		int lineGap;
		int linehight;
	};
	enum text_offset_predraw_ret_t {
		text_offset_predraw_ret_skip
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
			textSize(15);
		}
		void offsetText(size_t index, float& offsetX, float& offsetY) {
			offsetX = m_offsetX + scaleSrcX(offsetX);
			offsetY = m_offsetY + scaleMovY(m_src.linehight) - scaleSrcY(offsetY)
				+ scaleSrcY(m_src.descent);
		}
		void textSize(int pixelHeight) {
			m_scaleY = stbtt_ScaleForPixelHeight(m_font, pixelHeight);
			m_scaleX = m_scaleY;
			return;
		}
		void setRect(int w, int h) {

		}
		void offsetFillRect(size_t index, Rectangle*& rectangle) {
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
		void nextLine() {
			m_offsetX = 0;
			m_offsetY += scaleMovY(m_src.linehight);
			m_line++;
			return;
		}
		text_offset_predraw_ret_t predraw(size_t index) {
			if (m_text[index] == '\r') {
				nextLine();
				return text_offset_predraw_ret_skip;
			}
		}
	private:
		float m_dstWidth;
		float m_dstHeight;
		float m_scaleX = 1.0f;
		float m_scaleY = 1.0f;
		text_offset_src_t m_src;
		float m_offsetX;
		float m_offsetY;
		unsigned m_line = 0;
		const wchar_t* m_text;
		stbtt_fontinfo* m_font;
	};
	void Text::create(Context* context)
	{
		stbtt_fontinfo* font = m_font->getStbFont();
		Offset* offset = FCT_NEW(Offset,m_text);
		offset->setStbFont(font);
		offset->textSize(m_size);
		m_charShapesNum = wcslen(m_text);
		m_shape = FCT_NEWS(Shape * *,m_charShapesNum);
		m_shapeNum = FCT_NEWS (int,m_charShapesNum);
		int chId = 0;
		for (int i = 0; i < m_charShapesNum; i++) {
			m_shapeNum[i] = 0;
		}
		Vertex2d* TriangledVertexs;
		Pos2f TriangleFirstVertex;
		size_t TriangledVertexNums;
		for (const wchar_t* ch = m_text; *ch != L'\0'; ch++, chId++) {
			switch (offset->predraw(chId))
			{
			case text_offset_predraw_ret_skip:
				m_shape[chId] = NULL;
				continue;
			default:
				break;
			}
			stbtt_vertex* stbVertex = NULL;
			int verCount = 0;
			verCount = stbtt_GetCodepointShape(font, *ch, &stbVertex);
			TriangledVertexs = FCT_NEWS(Vertex2d,verCount * 3);//精确值:3 * (verCount - moveNum * 2)
			TriangledVertexNums = 0;
			m_shape[chId] = FCT_NEWS(Shape *,verCount + 2);
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
					m_shape[chId][m_shapeNum[chId]] = FCT_NEW(Line);
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
					control.x = stbVer->cx;
					control.y = stbVer->cy;
					offset->offsetText(chId,control.x, control.y);
					m_shape[chId][m_shapeNum[chId]] = FCT_NEW(TextFullQuadraticBezierCurve2d);
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
			m_shape[chId][m_shapeNum[chId]] = FCT_NEW(TextPolygon);
			TextPolygon* polygon = (TextPolygon*)m_shape[chId][m_shapeNum[chId]];
			polygon->setColor(m_color);
			polygon->setVertices(TriangledVertexs, TriangledVertexNums);
			polygon->create(context);
			m_shapeNum[chId]++;
			Rectangle* rectangle = FCT_NEW(Rectangle);
			offset->offsetFillRect(chId, rectangle);
			rectangle->setColor(m_backGroundColor);
			rectangle->create(context);
			m_shape[chId][m_shapeNum[chId]] = rectangle;
			m_shapeNum[chId]++;
			delete[] stbVertex;
			FCT_DELETES(TriangledVertexs);
		}
		offset->release();
		m_resouceNum = 0;
	}
	void Text::destoryShape()
	{
		for (int i = 0; i < m_charShapesNum; i++) {
			for (int j = 0; j < m_shapeNum[i]; j++) {
				FCT_RELEASE(m_shape[i][j]);
			}
			FCT_DELETES(m_shape[i]);
			m_shape[i] = nullptr;
			m_shapeNum[i] = 0;
		}
		FCT_DELETES(m_shapeNum);
		m_shapeNum = nullptr;
		FCT_DELETES(m_shape);
		m_shape = nullptr;
		m_charShapesNum = NULL;
	}

	class StbTextPosTranslator {
	public:
		StbTextPosTranslator(stbtt_fontinfo* font, wchar_t theChar) : m_char(theChar) {
			m_font = font; 
			m_scaleY = 1.0f;
			m_scaleX = 1.0f;
			stbtt_GetFontVMetrics(m_font, &m_ascent, &m_descent, &m_lineGap);
			m_srcHeight =  m_ascent - m_descent + m_lineGap;
			stbtt_GetCodepointHMetrics(m_font,m_char,&m_advance,&m_lsb);
			m_srcWidth = m_advance;
			computeDstSize();
		}
		inline void computeScaleFromPixelHight(float pixelHight) {
			m_dstHeight = pixelHight;
			m_scaleY = stbtt_ScaleForPixelHeight(m_font, pixelHight);
			m_scaleX = m_scaleY;
			computeDstSize();
		}
		inline void computeDstSize() {
			m_dstWidth = m_srcWidth * m_scaleX;
			m_dstHeight = m_srcHeight * m_scaleY;
		}
		inline float moveX(float srcX) {
			return srcX;
		}
		inline float moveY(float srcY) {
			return srcY - m_descent;
		}
		inline float scaleX(float srcX) {
			return m_scaleX * srcX;
		}
		inline float scaleY(float srcY) {
			return m_scaleY * srcY;
		}
		inline Pos2f translation(Pos2f pos) {
			return { scaleX(moveX(pos.x)),
				scaleY(moveY(pos.y)) };
		}
		inline float getWidth() {
			return m_dstWidth;
		}
		inline float getHeight() {
			return m_dstHeight;
		}
	private:
		stbtt_fontinfo* m_font;
		wchar_t m_char;
		float m_dstHeight;
		float m_dstWidth;
		float m_scaleX;
		float m_scaleY;
		unsigned m_srcWidth;
		unsigned m_srcHeight;
		int m_ascent;
		int m_descent;
		int m_lineGap;
		int m_advance;
		int m_lsb;
	};
	Stencil_CharShape::Stencil_CharShape()
	{
		m_font = NULL;
		m_resouce = NULL;
		m_resouceNum = 0;
		m_shapes = NULL;
		m_shapeNum = 0;
		m_translator = NULL;
		m_char = 0;
		m_color = {1,1,1,1};
	}
	Stencil_CharShape::~Stencil_CharShape()
	{
		FCT_RELEASE(m_font); 
		if (m_resouce) {
			for (int i = 0; i < m_resouceNum; i++) {
				FCT_RELEASE(m_resouce[i]);
			}
			FCT_DELETES(m_resouce);
			m_resouce = nullptr;
			m_resouceNum = 0;
		}
	}
	void Stencil_CharShape::setFont(Font* font)
	{
		if (m_font) {
			m_font->release();
		}
		m_font = font;
		m_font->addRef();
	}
	void Stencil_CharShape::destroy()
	{
		destroyShapes();
		destroyCharInfo();
	}
	void Stencil_CharShape::destroyShapes()
	{
		for (int i = 0; i < m_shapeNum; i++) {
			FCT_RELEASE(m_shapes[i]);
		}
		FCT_DELETES(m_shapes);
		m_shapes = NULL;
		m_shapeNum = 0;
	}
	void Stencil_CharShape::createCharInfo()
	{
		m_translator = FCT_NEW(StbTextPosTranslator, m_font->getStbFont(), m_char);
	}
	void Stencil_CharShape::destroyCharInfo()
	{
		FCT_DELETES(m_translator);
		m_translator = nullptr;
	}
	void Stencil_CharShape::setColor(Color color)
	{
		m_color = color;
	}
	void Stencil_CharShape::predraw(Context* context, int x, int y)
	{
		for (int i = 0; i < m_shapeNum; i++) {
			context->draw(m_shapes[i], x, y);
		}
	}
	void Stencil_CharShape::create(Context* context)
	{
		if (!m_translator) {
			createCharInfo();
		}
		stbtt_fontinfo* font = m_font->getStbFont();
		stbtt_vertex* stbVertexs = NULL;
		size_t vertexCount = 0;
		vertexCount = stbtt_GetCodepointShape(font, m_char, &stbVertexs);
		StbTextPosTranslator scale(font, m_char);

		m_shapes = FCT_NEWS(Shape*, vertexCount + 1); //最多情况下n个点有 n-1个图形 + 2 额外图形

		Vertex2d* triangledVertexs;
		Pos2f triangleFirstVertex;
		size_t triangledVertexNums;
		triangledVertexs = FCT_NEWS(Vertex2d, vertexCount * 3);
		triangledVertexNums = 0;

		Pos2f current;
		Pos2f previous;
		Pos2f control;

		for (size_t i = 0; i < vertexCount; i++) {
			stbtt_vertex* stbVer = stbVertexs + i;
			current.x = stbVer->x;
			current.y = stbVer->y;
			current = scale.translation(current);
			switch (stbVer->type)
			{
			case STBTT_vmove:
			{
				triangleFirstVertex = current;
				previous = current;
				break;
			}
			case STBTT_vline:
			{
				triangledVertexs[triangledVertexNums++] = { triangleFirstVertex.x, triangleFirstVertex.y };
				triangledVertexs[triangledVertexNums++] = { previous.x, previous.y };
				triangledVertexs[triangledVertexNums++] = { current.x, current.y };
				Line* line = FCT_NEW(Line);
				line->setOffset(previous.x, previous.y);
				line->setPoint(current.x - previous.x, current.y - previous.y);
				line->setColor(m_color);
				line->create(context);
				m_shapes[m_shapeNum] = line;
				m_shapeNum++;
				previous = current;
				break;
			}
			case STBTT_vcurve:
			{
				control.x = stbVer->cx;
				control.y = stbVer->cy;
				control = scale.translation(control);
				triangledVertexs[triangledVertexNums++] = { triangleFirstVertex.x, triangleFirstVertex.y };
				triangledVertexs[triangledVertexNums++] = { previous.x, previous.y };
				triangledVertexs[triangledVertexNums++] = { control.x, control.y };
				triangledVertexs[triangledVertexNums++] = { triangleFirstVertex.x, triangleFirstVertex.y };
				triangledVertexs[triangledVertexNums++] = { control.x, control.y };
				triangledVertexs[triangledVertexNums++] = { current.x, current.y };
				TextFullQuadraticBezierCurve2d* curve = FCT_NEW(TextFullQuadraticBezierCurve2d);
				curve->setOffset(previous.x, previous.y);
				curve->setBeginPoint(0, 0);
				curve->setControlPoint(control.x - previous.x, control.y - previous.y);
				curve->setEndPoint(current.x - previous.x, current.y - previous.y);
				curve->setColor(m_color);
				curve->create(context);
				m_shapes[m_shapeNum] = curve;
				m_shapeNum++;
				previous = current;
				break;
			}
			case STBTT_vcubic:
				break;
			default:
				break;
			}
		}
		TextPolygon* textPolygon = FCT_NEW(TextPolygon);
		textPolygon->setVertices(triangledVertexs, triangledVertexNums);
		textPolygon->setColor(m_color);
		textPolygon->create(context);
		m_shapes[m_shapeNum] = textPolygon;
		m_shapeNum++;
		Rectangle* rectangle = FCT_NEW(Rectangle);
		//rectangle->setRect(m)
		rectangle->setColor(m_color);
		rectangle->create(context);
		m_shapes[m_shapeNum] = rectangle;
		m_shapeNum++;
		FCT_DELETES(triangledVertexs);
	}
}
