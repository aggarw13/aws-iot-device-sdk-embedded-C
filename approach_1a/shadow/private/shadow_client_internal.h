#ifndef SHADOW_CLIENT_INTERNAL
#define SHADOW_CLIENT_INTERNAL

#include "shadow_config.h"

#ifndef LogError
    #define LogError( message )
#endif

#ifndef LogErrorWithArgs
    #define LogErrorWithArgs( formatAndStrings )
#endif

#ifndef LogWarn
    #define LogWarn( message )
#endif

#ifndef LogWarnWithArgs
    #define LogWarnWithArgs( formatAndStrings )
#endif

#ifndef LogInfo
    #define LogInfo( message )
#endif

#ifndef LogInfoWithArgs
    #define LogInfoWithArgs( formatAndStrings )
#endif

#ifndef LogDebug
    #define LogDebug( message )
#endif

#ifndef LogDebugWithArgs
    #define LogDebugWithArgs( formatAndStrings )
#endif

#endif /* SHADOW_CLIENT_INTERNAL */
