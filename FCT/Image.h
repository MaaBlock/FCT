enum image_t {
    image_type_window = 0x0,
    image_type_default = 0x1
};
class Image : public RefCounted {
public:
	virtual void setSize(unsigned width,unsigned height) = 0;
	//������Ϻ󣬴˺�����Ч
	virtual int msaaEnable(bool enable = true, unsigned count = 2) = 0;
	//ȡ�����������ȡ2��n�η�����0��,��msaaĬ�Ͽ�����������Ⱦ������
	// û����ݵģ�Ҫ���˿���ݣ�׼ȷ��˵�Ƿ����������������ֽ�С����
	//���������С�����־�ȱ���ˣ�����Ĭ�Ͽ�����Ҳ���Ժ������ֵ������
	//������
	virtual int create() = 0;
	virtual int getWidth() = 0;
	virtual int getHeight() = 0;
};
typedef Image Texture;