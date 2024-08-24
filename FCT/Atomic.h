template <typename T>
class Atomic {
public:
    Atomic(T value = 0) : m_value(value) {}
    T operator++() {
#ifdef _WIN64
        if (sizeof(T) == sizeof(void*)) {
            return InterlockedIncrement64(reinterpret_cast<volatile LONGLONG*>(&m_value));
        }
        else {
            return InterlockedIncrement(reinterpret_cast<volatile LONG*>(&m_value));
        }
#else
        return InterlockedIncrement(reinterpret_cast<volatile LONG*>(&m_value));
#endif
    }
    T operator--() {
#ifdef _WIN64
        if (sizeof(T) == sizeof(void*)) {
            return InterlockedDecrement64(reinterpret_cast<volatile LONGLONG*>(&m_value));
        }
        else {
            return InterlockedDecrement(reinterpret_cast<volatile LONG*>(&m_value));
        }
#else
        return InterlockedDecrement(reinterpret_cast<volatile LONG*>(&m_value));
#endif
    }
    T operator=(T newValue) {
#ifdef _WIN64
        if (sizeof(T) == sizeof(void*)) {
            return InterlockedExchange64(reinterpret_cast<volatile LONGLONG*>(&m_value), reinterpret_cast<LONGLONG>(newValue));
        }
        else {
            return InterlockedExchange(reinterpret_cast<volatile LONG*>(&m_value), reinterpret_cast<LONG>(newValue));
        }
#else
        return InterlockedExchange(reinterpret_cast<volatile LONG*>(&m_value), static_cast<LONG>(newValue));
#endif
    }
    T ifEqualThenAssign(T newValue, T comparand) {
#ifdef _WIN64
        if (sizeof(T) == sizeof(void*)) {
            return InterlockedCompareExchange64(reinterpret_cast<volatile LONGLONG*>(&m_value), reinterpret_cast<LONGLONG>(newValue), reinterpret_cast<LONGLONG>(comparand));
        }
        else {
            return InterlockedCompareExchange(reinterpret_cast<volatile LONG*>(&m_value), reinterpret_cast<LONG>(newValue), reinterpret_cast<LONG>(comparand));
        }
#else
        return InterlockedCompareExchange(reinterpret_cast<volatile LONG*>(&m_value), static_cast<LONG>(newValue), static_cast<LONG>(comparand));
#endif
    }
    T value() {
        return m_value;
    }
private:
    volatile T m_value;
};