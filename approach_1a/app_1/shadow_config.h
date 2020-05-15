#ifndef __SHADOW_CONFIG_H__
#define __SHADOW_CONFIG_H__

#include "logging_levels.h"

#define LIBRARY_LOG_NAME     "SHADOW"
#define LIBRARY_LOG_LEVEL    LOG_WARN

/**** NOTE: Include logging stack ONLY after the library name and log level configuration. ******/
#include "logging_stack.h"

#endif /* ifndef __SHADOW_CONFIG_H__ */
