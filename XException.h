#pragma once

#include <stdexcept>
#include <string>
#include <array>

class Exception : public std::runtime_error
{
public:
    enum class ExceptionCode
    {
        Unspecified,
        Unknown,
        CorruptedValue,
        LogicError,
        RuntimeError,
        DuplicateItem,
        BadParameters,
        NotImplemented,
        InvalidState,
        SystemError,
        NotFound,
        Count
    };

    enum class ExceptionMode
    {
        Exception,
        Error
    };

    struct ExceptionArgs
    {
        ExceptionCode errorCode{};
        std::wstring description;
        std::wstring systemErrorMessage;
        //PlatformUtility::StackTrace stackTrace;
        std::wstring functionName;
        ExceptionMode exceptionmode{};
    };

    static std::wstring ExceptionCodeToString(ExceptionCode code)
    {
        static std::array<std::wstring, SizeT(ExceptionCode::Count)> ExceptionCodeToString =
        {
            {
                L"Unspecified",
                L"Unknown", 
                L"Corrupted value",
                L"Logic error",
                L"Runtime error", 
                L"Duplicate item", 
                L"Bad parameters", 
                L"Missing implmentation", 
                L"System error"
            }
        };

        int exception_code_idx = Int(code);

        if (exception_code_idx < SafeSizeToInt(ExceptionCodeToString.size()))
        {
            return ExceptionCodeToString[exception_code_idx];
        }
        else
        {
            return L"Unspecified";
        }
            
    }
    static inline bool is_show_ = true;

    void setShowException(bool is_show)
    {
        is_show_ = is_show;
    }
};
