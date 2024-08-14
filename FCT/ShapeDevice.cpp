#include "hander.h"
namespace FCT {
	class ShapeCommon : public RefCounted {
	public:
		virtual void create(Context* context) = 0;
	private:

	};
	class ShapeBuilder {
	public:
		ShapeBuilder(Context* context);
		template<typename T>
		ShapeCommon* createShapeCommon(const char* shapeName);
		template<typename T>
		T* getShapeCommon(const char* shapeName);

	private:
		std::map<const char*, ShapeCommon*> m_shapeCommonMap;
		Context* m_context;
	};
	ShapeBuilder::ShapeBuilder(Context* context)
	{
		m_context = context;
	}
	template<typename T>
	ShapeCommon* ShapeBuilder::createShapeCommon(const char* shapeName)
	{
		ShapeCommon* shapeCommon = FCT_NEW(T);
		shapeCommon->create(m_context);
		m_shapeCommonMap[shapeName] = shapeCommon;
		return shapeCommon;
	}
	template<typename T>
	T* ShapeBuilder::getShapeCommon(const char* shapeName)
	{
		auto it = m_shapeCommonMap.find(shapeName);
		if (it != m_shapeCommonMap.end()) {
			return static_cast<T*>(it->second);
		}
		createShapeCommon<T>(shapeName);
		return getShapeCommon<T>(shapeName);
	}
#define FCT_SHAPE_CREATE_BEGIN(name) name##ShapeCommon* shapeCommon = buider->getShapeCommon<name##ShapeCommon>(#name);
	class CircleShapeCommon : public ShapeCommon {
	public:
		void create(Context* context) override {

		}
	};
	ShapeBuilder* createShapeBuilder(Context* context) {
		return FCT_NEW(ShapeBuilder,context);
	}
	class NewCircleShape : public CircleShapeCommon {
	
	}
}