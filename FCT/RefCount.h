#define CLASS_DESTORY(param) if(param) {param->release(); param = NULL;}
#define REF_CLASS_BEGIN() this->userdata = __func__
#define REF_CLASS_INIT() RefCounted(__func__)
class RefCounted {
public:
#ifdef FCT_MEMORY_CHEAK

#endif
	static unsigned nextId;
	unsigned uid;
	const char* userdata = "no userdata!";
	RefCounted() : refCounter(1) {
		uid = nextId;
		nextId++;
		//outputDebug();
	}
	RefCounted(const char* userdata) : refCounter(1),userdata(userdata) {
		uid = nextId;
		nextId++;
		outputDebug();
	}
	virtual void outputDebug() {
		//std::cout << "ID:" << uid << " ����:" << refCounter << "ʹ����Ϣ" << userdata << std::endl;
	}
	virtual ~RefCounted() {}
	virtual void addRef() {
		refCounter++;
		outputDebug();
	}
	virtual void release() {
		refCounter--;
		outputDebug();
		if (refCounter < 0) {
			std::cout << "���ּ���С��0" << std::endl;
		}
		if (refCounter == 0) {
			FCT_DELETE(this);
		}
	}
	int refCount() {
		return refCounter;
	}
private:
	int refCounter;
};

//ToDo:�������ü�����,������ʼ����