/*
 * Logging Stack Implementation V1.1.0
 * Copyright (C) 2018 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
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
 * @file logging.h
 * @brief Generic logging function header file.
 *
 * Declares the generic logging function.
 */

#ifndef LOGGING_H_
#define LOGGING_H_

/* Standard includes. */
#include <stddef.h>
#include <stdint.h>

/**
 * @brief Generic logging function that prints a single message.
 *
 * @param[in] addTimeStamp Flag to indicate whether a timestamp string
 * should be added at the beginning of the log message.
 * @param[in] pFormat Format string for the log message.
 * @param[in] ... Arguments for format specification.
 *
 * @return No return value. On errors, it prints nothing.
 */
/* @[declare_logging_generic] */
void SdkLogGeneric( const char * const pFormat,
                    ... );

/**
 * @brief Generic logging function that prints a single message.
 *
 * @param[in] addTimeStamp Flag to indicate whether a timestamp string
 * should be added at the beginning of the log message.
 * @param[in] pFormat Format string for the log message.
 * @param[in] ... Arguments for format specification.
 *
 * @return No return value. On errors, it prints nothing.
 */
/* @[declare_logging_generic] */
void SdkLogGenericWithTimestring( const char * const pFormat,
                                  ... );
/* @[declare_logging_generic] */


#endif /* ifndef IOT_LOGGING_H_ */
