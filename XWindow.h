#pragma once

#include "XID.h"

DEFINE_TYPED_ID(WindowId);

class Window
{
public:
    constexpr explicit Window(WindowId id) : id_{id} {}
    constexpr Window() = default;
    constexpr WindowId getWindowId() const
    {
        return id_;
    }
    constexpr bool isValid() const
    {
        return ID::IsValid(id_);
    }

    void setFullscreen(bool is_fullscreen) const;
    bool isFullscreen() const;
    void *handle() const;
    void setCaption(const wchar_t *caption) const;
    // math::u32v4 size() const;
    void resize(u32 width, u32 height) const;
    u32 width() const;
    u32 height() const;
    bool isClosed() const;
#ifdef __linux__
    void close();
#endif // __linux__
private:
    WindowId id_{ID::Invalid};
};
