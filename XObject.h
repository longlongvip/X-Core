#pragma once

#include "XAtomicInteger.h"

class Object
{
public:
    Object() = default;
    virtual ~Object();

    Object(const Object &) : Object() {}
    Object(Object &&) : Object() {}
    Object &operator=(const Object &) { return *this; }
    Object &operator=(Object &&) { return *this; }

    void incRef()
    {
        ai.inc();
    }

    void decRef()
    {
        ai.dec();
    }

private:
    AtomicInt ai;
};

template <typename T>
class Ref
{
public:
    Ref() {}
    explicit Ref(T *ptr) : ptr_(ptr)
    {
        if (ptr_)
        {
            reinterpret_cast<AtomicInt *>(ptr_)->inc();
        }
    }

    Ref(const Ref &Ref) : ptr_(Ref.ptr_)
    {
        if (ptr_)
        {
            reinterpret_cast<AtomicInt *>(ptr_)->inc();
        }
    }

    Ref(Ref &&ref) : ptr_(ref.ptr_)
    {
        ref.ptr_ = nullptr;
    }

    ~Ref()
    {
        if (ptr_)
        {
            reinterpret_cast<AtomicInt *>(ptr_)->dec();
        }
    }

    /// Move another Reference into the current one
    Ref &operator=(Ref &&ref) noexcept
    {
        if (&ref != this)
        {
            if (ptr_)
            {
                reinterpret_cast<AtomicInt *>(ptr_)->dec();
            }
            ptr_ = ref.ptr_;
            ref.ptr_ = nullptr;
        }
        return *this;
    }

    /// Overwrite this Reference with another Reference
    Ref &operator=(const Ref &ref) noexcept
    {
        if (ptr_ != ref.ptr_)
        {
            if (ref.ptr_)
            {
                reinterpret_cast<AtomicInt *>(ref.ptr_)->inc();
            }
            if (ptr_)
            {
                reinterpret_cast<AtomicInt *>(ptr_)->dec();
            }

            ptr_ = ref.ptr_;
        }
        return *this;
    }

    /// Overwrite this Reference with a pointer to another AtomicInt
    Ref &operator=(T *ptr) noexcept
    {
        if (ptr_ != ptr)
        {
            if (ptr)
            {
                reinterpret_cast<AtomicInt *>(ptr)->inc();
            }
            if (ptr_)
            {
                reinterpret_cast<AtomicInt *>(ptr_)->dec();
            }
            ptr_ = ptr;
        }
        return *this;
    }

    /// Compare this reference with another reference
    bool operator==(const Ref &ref) const { return ptr_ == ref.ptr_; }

    /// Compare this reference with another reference
    bool operator!=(const Ref &ref) const { return ptr_ != ref.ptr_; }

    /// Compare this reference with a pointer
    bool operator==(const T *ptr) const { return ptr_ == ptr; }

    /// Compare this reference with a pointer
    bool operator!=(const T *ptr) const { return ptr_ != ptr; }

    /// Access the AtomicInt referenced by this reference
    T *operator->() { return ptr_; }

    /// Access the AtomicInt referenced by this reference
    const T *operator->() const { return ptr_; }

    /// Return a C++ reference to the referenced AtomicInt
    T &operator*() { return *ptr_; }

    /// Return a const C++ reference to the referenced AtomicInt
    const T &operator*() const { return *ptr_; }

    /// Return a pointer to the referenced AtomicInt
    operator T *() { return ptr_; }

    /// Return a const pointer to the referenced AtomicInt
    T *get() { return ptr_; }

    /// Return a pointer to the referenced AtomicInt
    const T *get() const { return ptr_; }

    /// Check if the AtomicInt is defined
    operator bool() const { return ptr_ != nullptr; }

private:
    T *ptr_ = nullptr;
};
