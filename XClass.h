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
    NonCopyable(const NonCopyable &) = delete;
    void operator=(const NonCopyable &) = delete;

protected:
    NonCopyable() = default;
    ~NonCopyable() = default;
};

class StaticClass
{
public:
    StaticClass() = delete;
    StaticClass(const StaticClass &) = delete;
    void operator=(const StaticClass &) = delete;

protected:
    ~StaticClass() = default;
};

class ScopeClass
{
public:
    ScopeClass() = delete;
    ScopeClass(const ScopeClass &) = delete;
    ScopeClass &operator=(const ScopeClass &) = delete;
    ScopeClass(ScopeClass &&) = delete;
    ScopeClass &operator=(ScopeClass &&) = delete;
};
