
class Mutex : public RefCounted {
public:
	virtual void create() = 0;
	virtual void lock() = 0;
	virtual void unlock() = 0;
private:

};