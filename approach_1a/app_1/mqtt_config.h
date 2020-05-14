#ifndef __MQTT_CONFIG_H__
#define __MQTT_CONFIG_H__

#include "logging_stack.h"

#define LIBRARY_LOG_NAME    "MQTT"

#define LogError( message )                                              \
    do                                                                   \
    {                                                                    \
        CommonLog( ( "[ERROR] [MQTT] [%s] [%s]", __FILE__, __LINE__ ) ); \
        CommonLog( message );                                            \
    } while( 0 )

#define LogWarn( message )                                              \
    do                                                                  \
    {                                                                   \
        CommonLog( ( "[WARN] [MQTT] [%s] [%s]", __FILE__, __LINE__ ) ); \
        CommonLog( message );                                           \
    } while( 0 )
#define LogInfo( message )                                              \
    do                                                                  \
    {                                                                   \
        CommonLog( ( "[INFO] [MQTT] [%s] [%s]", __FILE__, __LINE__ ) ); \
        CommonLog( message );                                           \
    } while( 0 )
#define LogDebug( message )                                              \
    do                                                                   \
    {                                                                    \
        CommonLog( ( "[DEBUG] [MQTT] [%s] [%s]", __FILE__, __LINE__ ) ); \
        CommonLog( message );                                            \
    } while( 0 )


#endif /* ifndef __MQTT_CONFIG_H__ */
