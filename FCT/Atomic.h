#pragma once
template <typename T>
class Atomic {
public:
    Atomic(T value = 0) : m_value(value) {}
    T operator++() {
        if constexpr (std::is_pointer_v<T>) {
#ifdef _WIN64
            return InterlockedIncrement64(reinterpret_cast<volatile LONGLONG*>(&m_value));
#else
            return InterlockedIncrement(reinterpret_cast<volatile LONG*>(&value_));
#endif
        }
        else {
            return InterlockedIncrement(reinterpret_cast<volatile LONG*>(&m_value));
        }
    }
    T operator--() {
        if constexpr (std::is_pointer_v<T>) {
#ifdef _WIN64
            return InterlockedDecrement64(reinterpret_cast<volatile LONGLONG*>(&m_value));
#else
            return InterlockedDecrement(reinterpret_cast<volatile LONG*>(&value_));
#endif
        }
        else {
            return InterlockedDecrement(reinterpret_cast<volatile LONG*>(&m_value));
        }
    }
    T operator=(T newValue) {
        if constexpr (std::is_pointer_v<T>) {
#ifdef _WIN64
            return InterlockedExchange64(reinterpret_cast<volatile LONGLONG*>(&m_value), reinterpret_cast<LONGLONG>(newValue));
#else
            return InterlockedExchange(reinterpret_cast<volatile LONG*>(&value_), reinterpret_cast<LONG>(newValue));
#endif
        }
        else {
            return InterlockedExchange(reinterpret_cast<volatile LONG*>(&m_value), static_cast<LONG>(newValue));
        }
    }
    T ifEqualThenAssign(T newValue, T comparand) {
        if constexpr (std::is_pointer_v<T>) {
#ifdef _WIN64
            return InterlockedCompareExchange64(reinterpret_cast<volatile LONGLONG*>(&m_value), reinterpret_cast<LONGLONG>(newValue), reinterpret_cast<LONGLONG>(comparand));
#else
            return InterlockedCompareExchange(reinterpret_cast<volatile LONG*>(&value_), reinterpret_cast<LONG>(newValue), reinterpret_cast<LONG>(comparand));
#endif
        }
        else {
            return InterlockedCompareExchange(reinterpret_cast<volatile LONG*>(&m_value), static_cast<LONG>(newValue), static_cast<LONG>(comparand));
        }
    }
    T value() {
        return m_value;
    }

private:
    volatile T m_value;
};
