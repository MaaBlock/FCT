enum nctest_result_t {
	nctest_clent,
	nctest_caption,
	nctest_size_top_left,
	nctest_size_top,
	nctest_size_top_right,
	nctest_size_right,
	nctest_size_bottom_right,
	nctest_size_bottom,
	nctest_size_bottom_left,
	nctest_size_left,
};
class InputCallBack : public RefCounted {
public:
	virtual ~InputCallBack()
	{

	}
	virtual void onMouseLButtonDown(int x,int y) {
		
	}
	virtual void onMouseLButtonUp(int x, int y) {

	}
	virtual void onMouseRButtonDown(int x, int y) {

	}
	virtual void onMouseRButtonUp(int x, int y) {

	}
	virtual void onMouseMove(int x, int y) {
	
	}
	virtual void onMouseWheel(int x, int y, int delta) {}
	virtual void onChar(wchar_t ch) {

	}
	virtual void onKeyDown(int key) {

	}
	virtual void onKeyUp(int key) {

	}
	virtual nctest_result_t onNCTest(int x, int y) {
		return nctest_clent;
	}
	virtual void onPaint() {
		
	}
};
class Input : public RefCounted {
public:
	virtual void registerInputCallBack(InputCallBack* callback) = 0;
private:

};