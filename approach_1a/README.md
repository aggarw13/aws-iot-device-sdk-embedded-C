## Build Information for App_1 and App_2
Each of the apps only calls the `MQTT_PublishMessage` and `Shadow_Get` function, and specifies configuration for both MQTT and Shadow libraries.

### App_1 
<b>Logging level Configuration:</b>
* Debug for MQTT
* Warning for Shadow

`gcc -I app_1 -I logging-stack -I mqtt -I mqtt/private -I shadow -I shadow/private app_1/main.c mqtt/mqtt_client.c shadow/shadow_client.c -o build_1`