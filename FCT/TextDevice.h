class TextDevice {
private:
	TextDevice() {}
	~TextDevice() {}
	static TextDevice* m_textDevice;
public:
	static void Init();
	static TextDevice* GetTextDevice();
private:

};

inline TextDevice* CreateTextDevice() {
	return TextDevice::GetTextDevice();
}
inline TextDevice* GetTextDevice() {
	return TextDevice::GetTextDevice();
}
