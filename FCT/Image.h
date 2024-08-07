enum image_t {
    image_type_window = 0x0,
    image_type_default = 0x1
};
class Image : public RefCounted {
public:
	virtual int getWidth() = 0;
	virtual int getHeight() = 0;
};