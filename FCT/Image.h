class Image : public RefCounted {
public:
	virtual int getWidth() = 0;
	virtual int getHeight() = 0;
};