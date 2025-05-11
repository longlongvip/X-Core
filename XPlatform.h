#include "Internal/XOS.h"

#if defined X_PLATFORM_WINDOWS
    #include "Windows/Core.h"
#elif defined X_PLATFORM_LINUX
    #include "Linux/Core.h"
#endif
