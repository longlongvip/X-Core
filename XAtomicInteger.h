#pragma once

#include <atomic>

#include "XClass.h"

template <typename T>
class AtomicInteger : public NonCopyable
{
public:
    AtomicInteger() = default;

    T get()
    {
        return value_.load(std::memory_order_relaxed);
    }

    T getInc()
    {
        return value_.fetch_add(1, std::memory_order_relaxed);
    }

    void inc()
    {
        value_.fetch_add(1, std::memory_order_relaxed);
    }

    void inc(T x)
    {
        value_.fetch_add(x, std::memory_order_relaxed);
    }

    void dec()
    {
        value_.fetch_sub(1, std::memory_order_relaxed);
    }

    void dec(T x)
    {
        value_.fetch_sub(x, std::memory_order_relaxed);
    }

    void set(T value)
    {
        value_.store(value);
    }

private:
    std::atomic<T> value_ = 0;
};

using AtomicInt = AtomicInteger<int>;
using AtomicInt64 = AtomicInteger<int64_t>;
