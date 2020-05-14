#include "mqtt_client.h"
#include "shadow_client.h"

int main( void )
{
    MQTT_PublishMessage();

    Shadow_Get();

    return 0;
}
