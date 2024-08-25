#include "hander.h"
namespace FCT {
	class NewCharShape : public Shape {
	public:
		void predraw(Context* context,int x,int y);
		void create(Context* context,stbtt_fontinfo* fontInfo, wchar_t ch);
	private:
		Shape** m_shapes;
		size_t m_shapeNum;

	};
	class NewFont : public RefCounted {
	public:
		NewFont(Context* context);
		void create(const char* fileNameOrPath);
		NewCharShape* getShape(wchar_t ch);
		void createShape(wchar_t ch);
		void createShape(const wchar_t* text);
		void createShape(wchar_t theFirstChar,wchar_t theEndChar);
	private:
		Context* m_context;
		std::map<wchar_t, NewCharShape*> m_charShapes;
		stbtt_fontinfo* m_fontInfo;
		File* m_fontFile;
	};
	NewFont* CreateNewFont(Context* context);
	NewFont* CreateNewFont(Context* context) {
		return FCT_NEW(NewFont,context);
	}

	NewFont::NewFont(Context* context) : m_context(context), m_fontInfo(nullptr), m_fontFile(nullptr)
	{

	}

	void NewFont::create(const char* fileNameOrPath)
	{
		m_fontFile = CreateFile();
		m_fontInfo = FCT_NEW(stbtt_fontinfo);
		m_fontFile->open(fileNameOrPath,"r");
		stbtt_InitFont(m_fontInfo, (const unsigned char*)m_fontFile->getFileStream(), 0);
		return;
	}

	NewCharShape* NewFont::getShape(wchar_t ch)
	{
		auto it = m_charShapes.find(ch);
		if (it != m_charShapes.end()) {
			return it->second;
		}
		createShape(ch);
		return m_charShapes[ch];
	}
	void NewFont::createShape(wchar_t ch)
	{
		if (m_charShapes.find(ch) == m_charShapes.end()) {
			NewCharShape* newShape = FCT_NEW(NewCharShape);
			newShape->create(m_context, m_fontInfo, ch);
			m_charShapes[ch] = newShape;
		}
		return;
	}

	void NewFont::createShape(const wchar_t* text)
	{
		int numChars = wcslen(text);
		for (int i = 0; i < numChars; ++i) {
			createShape(text[i]);
		}
	}

	void NewFont::createShape(wchar_t theFirstChar, wchar_t theEndChar)
	{
		for (wchar_t ch = theFirstChar; ch <= theEndChar; ++ch) {
			createShape(ch);
		}
	}
	class StbNewCharShapeTutorial {
	public:
		StbNewCharShapeTutorial(stbtt_fontinfo* font, wchar_t theChar) : m_char(theChar) {
			m_font = font;
			m_scaleY = 1.0f;
			m_scaleX = 1.0f;
			stbtt_GetFontVMetrics(m_font, &m_ascent, &m_descent, &m_lineGap);
			m_srcHeight = m_ascent - m_descent + m_lineGap;
			stbtt_GetCodepointHMetrics(m_font, m_char, &m_advance, &m_lsb);
			m_srcWidth = m_advance;
			computeDstSize();
		}
		inline void fillVertex(Vertex2d& vertex) {
			vertex.color = { 1,1,1,1 };
			vertex.tex = { -1,-1 };
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
	void NewCharShape::predraw(Context* context, int x, int y)
	{

		DepthStencilState* state = context->createResource->DepthStencilState();
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
		RasterizerState* rasterizerState = context->createResource->RasterizerState();
		rasterizerState->setCullMode(cull_mode_none);
		rasterizerState->create(context);
		BlendState* blendState = context->createResource->BlendState();
		blendState->alphaToCoverage(true);
		context->setDeafultResource(blendState);
		context->setDeafultResource(rasterizerState);
		context->setDeafultResource(state);
		for (int i = 0; i < m_shapeNum; i++) {
			context->draw(m_shapes[i], x, y);
		}
		context->setDeafultResource(rasterizerState->getResouceType(), NULL);
		context->setDeafultResource(state->getResouceType(), NULL);
		context->setDeafultResource(blendState->getResouceType(), NULL);
		state->release();
		rasterizerState->release();
		blendState->release();
	}
	void NewCharShape::create(Context* context, stbtt_fontinfo* font, wchar_t ch)
	{
		stbtt_vertex* stbVertexs = NULL;
		size_t vertexCount = 0;
		vertexCount = stbtt_GetCodepointShape(font, ch, &stbVertexs);
		StbNewCharShapeTutorial tutorial(font, ch);
		m_shapes = FCT_NEWS(Shape*, vertexCount); //最多情况下n个点有 n-1个图形 + 1 额外图形

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
			current = tutorial.translation(current);
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
				triangledVertexs[triangledVertexNums].pos = { triangleFirstVertex.x, triangleFirstVertex.y };
				tutorial.fillVertex(triangledVertexs[triangledVertexNums++]);
				triangledVertexs[triangledVertexNums].pos = { previous.x, previous.y };
				tutorial.fillVertex(triangledVertexs[triangledVertexNums++]);
				triangledVertexs[triangledVertexNums].pos = { current.x, current.y };
				tutorial.fillVertex(triangledVertexs[triangledVertexNums++]);
				Line* line = FCT_NEW(Line);
				line->setOffset(previous.x, previous.y);
				line->setPoint(current.x - previous.x, current.y - previous.y);
				line->setColor({1,1,1,1});
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
				control = tutorial.translation(control);
				triangledVertexs[triangledVertexNums].pos = { triangleFirstVertex.x, triangleFirstVertex.y };
				tutorial.fillVertex(triangledVertexs[triangledVertexNums++]);
				triangledVertexs[triangledVertexNums].pos = { previous.x, previous.y };
				tutorial.fillVertex(triangledVertexs[triangledVertexNums++]);
				triangledVertexs[triangledVertexNums].pos = { current.x, current.y };
				tutorial.fillVertex(triangledVertexs[triangledVertexNums++]);
				TextFullQuadraticBezierCurve2d* curve = FCT_NEW(TextFullQuadraticBezierCurve2d);
				curve->setOffset(previous.x, previous.y);
				curve->setBeginPoint(0, 0);
				curve->setControlPoint(control.x - previous.x, control.y - previous.y);
				curve->setEndPoint(current.x - previous.x, current.y - previous.y);
				curve->setColor({1,1,1,1});
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
		textPolygon->setColor({1,1,1,1});
		textPolygon->create(context);
		m_shapes[m_shapeNum] = textPolygon;
		m_shapeNum++;
		FCT_DELETES(triangledVertexs);
		FCT_DELETES(stbVertexs);
	}
}