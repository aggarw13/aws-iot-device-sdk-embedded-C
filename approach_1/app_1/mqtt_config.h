#ifndef __MQTT_CONFIG_H__
#define __MQTT_CONFIG_H__

#include <stdio.h>

#define CommonLog( message )    printf message

#define LogError( message )     CommonLog( ( "[ERROR] [MQTT] [%s] [%s]", __FILE__, __LINE__ ) ); CommonLog( message );
#define LogWarn( message )      CommonLog( ( "[WARN] [MQTT] [%s] [%s]", __FILE__, __LINE__ ) ); CommonLog( message );
#define LogInfo( message )      CommonLog( ( "[INFO] [MQTT] [%s] [%s]", __FILE__, __LINE__ ) ); CommonLog( message );
#define LogDebug( message )     CommonLog( ( "[DEBUG] [MQTT] [%s] [%s]", __FILE__, __LINE__ ) ); CommonLog( message );


#endif /* ifndef __MQTT_CONFIG_H__ */
