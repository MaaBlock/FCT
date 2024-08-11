enum image_t {
    image_type_window = 0x0,
    image_type_default = 0x1
};
class Image : public RefCounted {
public:
	virtual void setSize(unsigned width,unsigned height) = 0;
	//创建完毕后，此函数无效
	virtual int msaaEnable(bool enable = true, unsigned count = 2) = 0;
	//取样点个数仅能取2的n次方（含0）,且msaa默认开启（文字渲染本身是
	// 没抗锯齿的，要开了抗锯齿（准确点说是反走样），当你文字较小，才
	//不会出现你小了文字就缺损了，所以默认开启，也许以后会给文字单独添加
	//反走样
	virtual int create() = 0;
	virtual int getWidth() = 0;
	virtual int getHeight() = 0;
};
typedef Image Texture;