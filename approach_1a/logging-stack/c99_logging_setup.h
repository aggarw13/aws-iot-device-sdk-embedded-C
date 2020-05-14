/*
 * Common Logging Framework
 * Copyright (C) 2020 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/**
 * @file c99_logging_setup.h
 * @brief Defines the common logging framework that calls #Log interface.
 */

#ifndef C99_LOGGING_SETUP_H_
#define C99_LOGGING_SETUP_H_

/* Include header for logging level macros. */
#include "logging_levels.h"

#include "logging.h"

/**
 * @functionpage{Log,logging,log}
 */

/**
 * @def Log( messageLevel, pFormat, ... )
 * @brief The common logging interface for all libraries.
 *
 * This acts as a hook for supplying a logging implementation stack
 * for all libraries that log through this macro interface.
 * This macro should be mapped to the platform's logging library.
 *
 * @param[in] messageLevel The integer code for the log level of the message.
 * Must be one of #LOG_ERROR, #LOG_WARN, #LOG_INFO or #LOG_DEBUG.
 * Must not be #LOG_NONE.
 * @param[in] pFormat The format string for the log message.
 * @param[in] ... The variadic argument list for the format string.
 *
 * @return No return value.
 */

/**
 * @def LogError( message  )
 * @brief Abbreviated logging macro for stand-alone message strings at level #LOG_ERROR.
 *
 * Equivalent to:
 * @code{c}
 * Log( LOG_ERROR, "%s" , message )
 * @endcode
 */

/**
 * @def LogErrorWithArgs( pFormat, ...  )
 * @brief Abbreviated logging macro for messages with arguments at level #LOG_ERROR.
 *
 * Equivalent to:
 * @code{c}
 * Log( LOG_ERROR, pFormat, ... )
 * @endcode
 */

/**
 * @def LogWarn( message  )
 * @brief Abbreviated logging macro for stand-alone message strings at level #LOG_WARN.
 *
 * Equivalent to:
 * @code{c}
 * Log( LOG_WARN, "%s" , message )
 * @endcode
 */

/**
 * @def LogWarnWithArgs( pFormat, ...  )
 * @brief Abbreviated logging macro for messages with arguments at level #LOG_WARN.
 *
 * Equivalent to:
 * @code{c}
 * Log( LOG_WARN, pFormat, ... )
 * @endcode
 */

/**
 * @def LogInfo( message  )
 * @brief Abbreviated logging macro for stand-alone message strings at level #LOG_INFO.
 *
 * Equivalent to:
 * @code{c}
 * Log( LOG_INFO, "%s" , message )
 * @endcode
 */

/**
 * @def LogInfoWithArgs( pFormat, ...  )
 * @brief Abbreviated logging macro for messages with arguments at level #LOG_INFO.
 *
 * Equivalent to:
 * @code{c}
 * Log( LOG_INFO, pFormat, ... )
 * @endcode
 */

/**
 * @def LogDebug( message  )
 * @brief Abbreviated logging macro for stand-alone message strings at level #LOG_DEBUG.
 *
 * Equivalent to:
 * @code{c}
 * Log( LOG_DEBUG, "%s" , message )
 * @endcode
 */

/**
 * @def LogDebugWithArgs( pFormat, ...  )
 * @brief Abbreviated logging macro for messages with arguments at level #LOG_DEBUG.
 *
 * Equivalent to:
 * @code{c}
 * Log( LOG_DEBUG, pFormat, ... )
 * @endcode
 */

#define parseFormatString( format, ... )    format
#define parseFormatArgs( format, ... )      __VA_ARGS__

/* Define the IotLog logging interface to enabling logging.
 * This demo maps the macro to the reference POSIX implementation for logging.
 * Note: @ref LIBRARY_LOG_NAME adds the name of the library, that produces the
 * log, as metadata in each log message. */
#define CommonLog99( libraryName, messageLevel, format, ... ) \
    Log_Generic( messageLevel,                                \
                 "[%s:%d] [%s] "format,                       \
                 __FILE__,                                    \
                 __LINE__,                                    \
                 libraryName,                                 \
                 __VA_ARGS__ )

#define LogWithArgs( libraryName, messageLevel, formatAndString ) \
    CommonLog99( libraryName, messageLevel, parseFormatString formatAndString, parseFormatArgs formatAndString )

#define Log( libraryName, messageLevel, message ) \
    CommonLog99( libraryName, messageLevel, "%s", parseFormatString message )

#endif /* ifndef C99_LOGGING_SETUP_H_ */
