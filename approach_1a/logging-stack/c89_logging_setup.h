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
 * @file c89_logging_setup.h
 * @brief Defines the common logging framework that calls #Log interface.
 */

#ifndef C89_LOGGING_SETUP_H_
#define C89_LOGGING_SETUP_H_

#include "logging.h"

/**
 * @functionpage{Log,logging,log}
 */

/**
 * @def LogErrorC89( message  )
 * @brief Abbreviated logging macro for stand-alone message strings at level #LOG_ERROR.
 *
 * Equivalent to:
 * @code{c}
 * Log( LOG_ERROR, "%s" , message )
 * @endcode
 */

/**
 * @def LogWarnC89( message  )
 * @brief Abbreviated logging macro for stand-alone message strings at level #LOG_WARN.
 *
 * Equivalent to:
 * @code{c}
 * Log( LOG_WARN, "%s" , message )
 * @endcode
 */

/**
 * @def LogInfoC89( message  )
 * @brief Abbreviated logging macro for stand-alone message strings at level #LOG_INFO.
 *
 * Equivalent to:
 * @code{c}
 * Log( LOG_INFO, "%s" , message )
 * @endcode
 */

/**
 * @def LogDebugC89( message  )
 * @brief Abbreviated logging macro for stand-alone message strings at level #LOG_DEBUG.
 *
 * Equivalent to:
 * @code{c}
 * Log( LOG_DEBUG, "%s" , message )
 * @endcode
 */

#define LogErrorC89( message )    Log_Error message
#define LogWarnC89( message )     Log_Warn message
#define LogInfoC89( message )     Log_Info message
#define LogDebugC89( message )    Log_Debug message


#endif /* ifndef C89_LOGGING_SETUP_H_ */
