#pragma once

class Copyable
{
protected:
    Copyable() = default;
    ~Copyable() = default;
};

class NonCopyable
{
public:
    NonCopyable(const NonCopyable&) = delete;
    void operator=(const NonCopyable&) = delete;

protected:
    NonCopyable() = default;
    ~NonCopyable() = default;
};

class StaticClass
{
public:
    StaticClass() = delete;
    StaticClass(const StaticClass&) = delete;
    void operator=(const StaticClass&) = delete;

protected:
    ~StaticClass() = default;
};
