#include "mqtt_client.h"
#include "mqtt_client_internal.h"

void MQTT_PublishMessage( void )
{
    LogError( ( "Error log string.\n" ) );
    LogError( ( "Error log with one arg: %d.\n", 1 ) );
    LogWarn( ( "Warning log string.\n" ) );
    LogWarn( ( "Warning log with one arg: %d.\n", 1 ) );
    LogInfo( ( "Info log string.\n" ) );
    LogInfo( ( "Info log with one arg: %d.\n", 1 ) );
    LogDebug( ( "Debug log string.\n" ) );
    LogDebug( ( "Debug log with one arg: %d.\n", 1 ) );
}
