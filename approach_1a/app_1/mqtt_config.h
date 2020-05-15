#ifndef __MQTT_CONFIG_H__
#define __MQTT_CONFIG_H__

#include "logging_levels.h"

#define LIBRARY_LOG_NAME     "MQTT"
#define LIBRARY_LOG_LEVEL    LOG_DEBUG

/**** NOTE: Include logging stack ONLY after the library name and log level configuration. ******/
#include "logging_stack.h"

#endif /* ifndef __MQTT_CONFIG_H__ */
