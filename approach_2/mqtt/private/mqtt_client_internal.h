#ifndef MQTT_CLIENT_INTERNAL_H
#define MQTT_CLIENT_INTERNAL_H

#include "config.h"

#ifdef ENABLE_LOGGING
    #ifdef MQTT_LOG_LEVEL
        #define LIBRARY_LOG_LEVEL        MQTT_LOG_LEVEL
    #else
        #ifdef GLOBAL_LOG_LEVEL
            #define LIBRARY_LOG_LEVEL    GLOBAL_LOG_LEVEL
        #else
            #define LIBRARY_LOG_LEVEL    LOG_NONE
        #endif
    #endif

    #define LIBRARY_LOG_NAME            "MQTT"
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

#endif /* MQTT_CLIENT_INTERNAL_H */
