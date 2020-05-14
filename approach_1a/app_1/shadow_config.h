#ifndef __SHADOW_CONFIG_H__
#define __SHADOW_CONFIG_H__

#include "logging_stack.h"

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

#define LogInfo( message )

#define LogDebug( message )


#endif /* ifndef __SHADOW_CONFIG_H__ */
