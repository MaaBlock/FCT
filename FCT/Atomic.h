#ifdef _WIN32
template <typename T>
class Atomic {
public:
    Atomic(T value = 0) : m_value(value) {}
    T operator++() {
#ifdef _WIN64
        if (sizeof(T) == sizeof(void*)) {
            return reinterpret_cast<T>(InterlockedIncrement64(reinterpret_cast<volatile LONGLONG*>(&m_value)));
        }
        else {
            return reinterpret_cast<T>(InterlockedIncrement(reinterpret_cast<volatile LONG*>(&m_value)));
        }
#else
        return reinterpret_cast<T>(InterlockedIncrement(reinterpret_cast<volatile LONG*>(&m_value)));
#endif
    }
    T operator--() {
#ifdef _WIN64
        if (sizeof(T) == sizeof(void*)) {
            return reinterpret_cast<T>(InterlockedDecrement64(reinterpret_cast<volatile LONGLONG*>(&m_value)));
        }
        else {
            return reinterpret_cast<T>(InterlockedDecrement(reinterpret_cast<volatile LONG*>(&m_value)));
        }
#else
        return reinterpret_cast<T>(InterlockedDecrement(reinterpret_cast<volatile LONG*>(&m_value)));
#endif
    }
    T operator=(T newValue) {
#ifdef _WIN64
        if (sizeof(T) == sizeof(void*)) {
            return (T)(InterlockedExchange64(reinterpret_cast<volatile LONGLONG*>(&m_value), reinterpret_cast<LONGLONG>(newValue)));
        }
        else {
            return (T)(InterlockedExchange(reinterpret_cast<volatile LONG*>(&m_value), reinterpret_cast<LONG>(newValue)));
        }
#else
        return reinterpret_cast<T>(InterlockedExchange(reinterpret_cast<volatile LONG*>(&m_value), reinterpret_cast<LONG>(newValue)));
#endif
    }
    T ifEqualThenAssign(T newValue, T comparand) {
#ifdef _WIN64
        if (sizeof(T) == sizeof(void*)) {
            return reinterpret_cast<T>(InterlockedCompareExchange64(reinterpret_cast<volatile LONGLONG*>(&m_value), reinterpret_cast<LONGLONG>(newValue), reinterpret_cast<LONGLONG>(comparand)));
        }
        else {
            return reinterpret_cast<T>(InterlockedCompareExchange(reinterpret_cast<volatile LONG*>(&m_value), reinterpret_cast<LONG>(newValue), reinterpret_cast<LONG>(comparand)));
        }
#else
        return reinterpret_cast<T>(InterlockedCompareExchange(reinterpret_cast<volatile LONG*>(&m_value), reinterpret_cast<LONG>(newValue), reinterpret_cast<LONG>(comparand)));
#endif
    }
    T value() {
        return m_value;
    }
private:
    volatile T m_value;
};
template <>
class Atomic<bool> {
public:
    Atomic(bool value = false) : m_value(static_cast<LONG>(value)) {}
    bool value() const {
        return m_value != 0;
    }
    void operator=(bool value) {
        m_value = static_cast<LONG>(value);
    }
    bool ifEqualThenAssign(bool newValue, bool expectedValue) {
        return InterlockedCompareExchange(
            const_cast<LONG*>(&m_value),
            static_cast<LONG>(newValue),
            static_cast<LONG>(expectedValue)
        ) == static_cast<LONG>(expectedValue);
    }
private:
    volatile LONG m_value;
};
#endif