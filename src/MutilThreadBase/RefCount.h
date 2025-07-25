#pragma once
#include<atomic>
#include "../DebugTools/MemoryCheak.h"
namespace FCT {
	class RefCount {
	public:
		RefCount() : m_refCount(1) {}
		RefCount(size_t refCount) : m_refCount(refCount) {}
		virtual ~RefCount() {};
		void addRef() {
			++m_refCount;
		}
		void release() {
			--m_refCount;
			if (m_refCount)
				return;
			deleteThis();
		}
		size_t count() {
			return m_refCount;
		}
		operator bool() const
		{
			return m_refCount > 0;
		}
	protected:
		virtual void deleteThis() {
			FCT_DELETE(this);
		}
		std::atomic<size_t> m_refCount;
	};

	/**
	 * @cond CHINESE
	 * @brief 用于自定义对象销毁行为
	 * @note 对于继承了DeletableTrait和引用计数类的 添加该函数
	 * @code
     *  void deleteThis() override {
	 *		if (!applyDeleter(this)) {
	 *			FCT_DELETE(this);
	 *		}
	 *  }
	 * @endcode
	 * 使得其可以自定义删除时的 操作，
	 * 主要用于实现对象池
	 * @tparam T 子类类型
	 * @endcond
	 */
	template<typename T>
	class DeletableTrait {
	public:
		using DeleterType = std::function<void(T*)>;

		void setDeleter(DeleterType deleter) {
			m_deleter = std::move(deleter);
		}

		template<typename Func>
		void setDeleterFunc(Func&& func) {
			m_deleter = [f = std::forward<Func>(func)](T* ptr) { f(ptr); };
		}

	protected:
		bool applyDeleter(T* ptr) {
			if (m_deleter) {
				m_deleter(ptr);
				return true;
			}
			return false;
		}

	private:
		DeleterType m_deleter;
	};

	/**
	 * @cond CHINESE
	 * @tparam T 被检测的类型
	 * @tparam U
	 * @endcond
	 */
	template<typename T, typename U = T>
	struct IsDeletableTrait : std::is_base_of<DeletableTrait<U>, T> {};
	inline void safeAddRef(RefCount* obj) {
		if (obj) obj->addRef();
	}
	inline void safeRelease(RefCount*& obj) {
		if (obj) obj->release();
        obj = nullptr;
	}
#define FCT_SAFE_RELEASE(obj) if (obj) obj->release(); obj = nullptr;
#define FCT_SAFE_ADDREF(p) if (p) { p->addRef(); }
}