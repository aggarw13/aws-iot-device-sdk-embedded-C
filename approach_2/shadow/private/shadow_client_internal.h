#ifndef SHADOW_CLIENT_INTERNAL
#define SHADOW_CLIENT_INTERNAL

#include "config.h"

#ifdef ENABLE_LOGGING
    #ifdef SHADOW_LOG_LEVEL
        #define LIBRARY_LOG_LEVEL        SHADOW_LOG_LEVEL
    #else
        #ifdef GLOBAL_LOG_LEVEL
            #define LIBRARY_LOG_LEVEL    GLOBAL_LOG_LEVEL
        #else
            #define LIBRARY_LOG_LEVEL    LOG_NONE
        #endif
    #endif

    #define LIBRARY_LOG_NAME            "Shadow"
    #include "logging_setup.h"
#else

    #ifndef LogError
        #define LogError( message )
    #endif

    #ifndef LogWarn
        #define LogWarn( message )
    #endif

    #ifndef LogInfo
        #define LogInfo( message )
    #endif

    #ifndef LogDebug
        #define LogDebug( message )
    #endif

#endif /* ENABLE_LOGGING */

#endif /* SHADOW_CLIENT_INTERNAL */
