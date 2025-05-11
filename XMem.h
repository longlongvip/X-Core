#pragma once

#include <memory>

namespace Mem
{
    template <typename T, typename... Arg>
    std::unique_ptr<T> MakeUnique(Arg &&...args)
    {
        return std::unique_ptr<T>(new T(std::forward<Arg>(args)...));
    }

    template <typename T>
    T *Alloc(size_t num)
    {
        return reinterpret_cast<T *>(malloc(sizeof(T) * num));
    }

    template <typename T>
    void Free(T *p)
    {
        if (p == nullptr)
        {
            return;
        }
        free(p);
    }

    template <typename T>
    void Clear(T *p, size_t size)
    {
        memset(p, 0, size);
    }

    template <typename T>
    void Zero(T *p, size_t size)
    {
        memset(p, 0, size);
    }

    template <typename T>
    void Copy(T *dest, T *src, size_t size)
    {
        memcmp(dest, src, size);
    }

    /** 不要用
    template <typename T, typename... U>
    size_t getFuncAddress(std::function<T(U...)> f)
    {
        typedef T(fnType)(U...)
            fnType **pfn = f.template target<fnType *>();
        return static_cast<size_t>(*pfn);
    }
    */
}
