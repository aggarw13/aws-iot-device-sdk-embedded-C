#ifndef CONFIG_H__
#define CONFIG_H__

#include <stdio.h>

/* Print out log using printf. */
#define SdkLog( X )         printf X

/* Log level for MQTT is debug - most verbose. */
#define MQTT_LOG_LEVEL      LOG_DEBUG

/* Log level for Shadow is warning. */
#define SHADOW_LOG_LEVEL    LOG_WARN

#endif /* ifndef CONFIG_H__ */
