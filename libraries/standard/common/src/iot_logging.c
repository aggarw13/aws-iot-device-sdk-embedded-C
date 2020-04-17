/*
 * IoT Common V1.1.0
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
 * @file iot_logging.c
 * @brief Implementation of the generic logging function.
 */

/* Standard includes. */
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

/* Platform clock include. */
#include "platform/iot_clock.h"

/* Logging includes. */
#include "iot_logging.h"

/*-----------------------------------------------------------*/

/**
 * @def IotLogging_Puts( message )
 * @brief Function the logging library uses to print a line.
 *
 * This function can be set by using a define. By default, the standard library
 * [puts](http://pubs.opengroup.org/onlinepubs/9699919799/functions/puts.html)
 * function is used.
 */
#ifndef IotLogging_Puts
    #define IotLogging_Puts    puts
#endif

/*
 * Provide default values for undefined memory allocation functions based on
 * the usage of dynamic memory allocation.
 */
#if IOT_STATIC_MEMORY_ONLY == 1
    /* Static memory allocation header. */
    #include "iot_static_memory.h"

/**
 * @brief Allocate a new logging buffer. This function must have the same
 * signature as [malloc](http://pubs.opengroup.org/onlinepubs/9699919799/functions/malloc.html).
 */
    #ifndef IotLogging_Malloc
        #define IotLogging_Malloc    Iot_MallocMessageBuffer
    #endif

/**
 * @brief Free a logging buffer. This function must have the same signature
 * as [free](http://pubs.opengroup.org/onlinepubs/9699919799/functions/free.html).
 */
    #ifndef IotLogging_Free
        #define IotLogging_Free    Iot_FreeMessageBuffer
    #endif

/**
 * @brief Get the size of a logging buffer. Statically-allocated buffers
 * should all have the same size.
 */
    #ifndef IotLogging_StaticBufferSize
        #define IotLogging_StaticBufferSize    Iot_MessageBufferSize
    #endif
#else /* if IOT_STATIC_MEMORY_ONLY == 1 */
    #ifndef IotLogging_Malloc
        #include <stdlib.h>
        #define IotLogging_Malloc    malloc
    #endif

    #ifndef IotLogging_Free
        #include <stdlib.h>
        #define IotLogging_Free    free
    #endif
#endif /* if IOT_STATIC_MEMORY_ONLY == 1 */

/**
 * @brief A guess of the maximum length of a timestring.
 *
 * There's no way for this logging library to know the length of a timestring
 * before it's generated. Therefore, the logging library will assume a maximum
 * length of any timestring it may get. This value should be generous enough
 * to accommodate the vast majority of timestrings.
 *
 * @see @ref platform_clock_function_gettimestring
 */
#define MAX_TIMESTRING_LENGTH    ( 64 )

/*-----------------------------------------------------------*/

/**
 * @brief Lookup table for log levels.
 *
 * Converts one of the @ref logging_constants_levels to a string.
 */
static const char * const _pLogLevelStrings[] =
{
    "ERROR", /* IOT_LOG_ERROR */
    "WARN ", /* IOT_LOG_WARN */
    "INFO ", /* IOT_LOG_INFO */
    "DEBUG"  /* IOT_LOG_DEBUG */
};

/*-----------------------------------------------------------*/

#if !defined( IOT_STATIC_MEMORY_ONLY ) || ( IOT_STATIC_MEMORY_ONLY == 0 )
    static bool _reallocLoggingBuffer( void ** pOldBuffer,
                                       size_t newSize,
                                       size_t oldSize )
    {
        bool status = false;

        /* Allocate a new, larger buffer. */
        void * pNewBuffer = IotLogging_Malloc( newSize );

        /* Ensure that memory allocation succeeded. */
        if( pNewBuffer != NULL )
        {
            /* Copy the data from the old buffer to the new buffer. */
            ( void ) memcpy( pNewBuffer, *pOldBuffer, oldSize );

            /* Free the old buffer and update the pointer. */
            IotLogging_Free( *pOldBuffer );
            *pOldBuffer = pNewBuffer;

            status = true;
        }

        return status;
    }
#endif /* if !defined( IOT_STATIC_MEMORY_ONLY ) || ( IOT_STATIC_MEMORY_ONLY == 0 ) */

/*-----------------------------------------------------------*/

void IotLog_Generic( int32_t messageLevel,
                     const char * const pFormat,
                     ... )
{
    assert( ( messageLevel >= IOT_LOG_NONE ) && ( messageLevel <= IOT_LOG_DEBUG ) );

    int requiredMessageSize = 0;
    size_t bufferSize = 0,
           bufferPosition = 0, timestringLength = 0;
    char * pLoggingBuffer = NULL;
    va_list args;

    /* Add length of log level if requested. */
    bufferSize += MAX_LOG_LEVEL_LENGTH;

    /* Add length of timestring. */
    bufferSize += MAX_TIMESTRING_LENGTH;

    /* Add 64 as an initial (arbitrary) guess for the length of the message. */
    bufferSize += 64;

    /* In static memory mode, check that the log message will fit in the a
     * static buffer. */
    #if IOT_STATIC_MEMORY_ONLY == 1
        if( bufferSize >= IotLogging_StaticBufferSize() )
        {
            /* If the static buffers are likely too small to fit the log message,
             * return. */
            return;
        }

        /* Otherwise, update the buffer size to the size of a static buffer. */
        bufferSize = IotLogging_StaticBufferSize();
    #endif

    /* Allocate memory for the logging buffer. */
    pLoggingBuffer = ( char * ) IotLogging_Malloc( bufferSize );

    if( pLoggingBuffer == NULL )
    {
        return;
    }

    /* Print the message log level. */

    /* Add the log level string to the logging buffer. */
    requiredMessageSize = snprintf( pLoggingBuffer + bufferPosition,
                                    bufferSize - bufferPosition,
                                    "[%s]",
                                    _pLogLevelStrings[ messageLevel ] );

    /* Check for encoding errors. */
    if( requiredMessageSize <= 0 )
    {
        IotLogging_Free( pLoggingBuffer );

        return;
    }

    /* Update the buffer position. */
    bufferPosition += ( size_t ) requiredMessageSize;

    /* Print the timestring if requested. */
    /* Add the opening '[' enclosing the timestring. */
    pLoggingBuffer[ bufferPosition ] = '[';
    bufferPosition++;

    /* Generate the timestring and add it to the buffer. */
    if( IotClock_GetTimestring( pLoggingBuffer + bufferPosition,
                                bufferSize - bufferPosition,
                                &timestringLength ) == true )
    {
        /* If the timestring was successfully generated, add the closing "]". */
        bufferPosition += timestringLength;
        pLoggingBuffer[ bufferPosition ] = ']';
        bufferPosition++;
    }
    else
    {
        /* Sufficient memory for a timestring should have been allocated. A timestring
         * probably failed to generate due to a clock read error; remove the opening '['
         * from the logging buffer. */
        bufferPosition--;
        pLoggingBuffer[ bufferPosition ] = '\0';
    }

    /* Add a padding space between the last closing ']' and the message, unless
     * the logging buffer is empty. */
    if( bufferPosition > 0 )
    {
        pLoggingBuffer[ bufferPosition ] = ' ';
        bufferPosition++;
    }

    va_start( args, pFormat );

    /* Add the log message to the logging buffer. */
    requiredMessageSize = vsnprintf( pLoggingBuffer + bufferPosition,
                                     bufferSize - bufferPosition,
                                     pFormat,
                                     args );

    va_end( args );

    /* If the logging buffer was too small to fit the log message, reallocate
     * a larger logging buffer. */
    if( ( size_t ) requiredMessageSize >= bufferSize - bufferPosition )
    {
        #if IOT_STATIC_MEMORY_ONLY == 1

            /* There's no point trying to allocate a larger static buffer. Return
             * immediately. */
            IotLogging_Free( pLoggingBuffer );

            return;
        #else
            if( _reallocLoggingBuffer( ( void ** ) &pLoggingBuffer,
                                       ( size_t ) requiredMessageSize + bufferPosition + 1,
                                       bufferSize ) == false )
            {
                /* If buffer reallocation failed, return. */
                IotLogging_Free( pLoggingBuffer );

                return;
            }

            /* Reallocation successful, update buffer size. */
            bufferSize = ( size_t ) requiredMessageSize + bufferPosition + 1;

            /* Add the log message to the buffer. Now that the buffer has been
             * reallocated, this should succeed. */
            va_start( args, pFormat );
            requiredMessageSize = vsnprintf( pLoggingBuffer + bufferPosition,
                                             bufferSize - bufferPosition,
                                             pFormat,
                                             args );
            va_end( args );
        #endif /* if IOT_STATIC_MEMORY_ONLY == 1 */
    }

    /* Check for encoding errors. */
    if( requiredMessageSize <= 0 )
    {
        IotLogging_Free( pLoggingBuffer );

        return;
    }

    /* Print the logging buffer to stdout. */
    IotLogging_Puts( pLoggingBuffer );

    /* Free the logging buffer. */
    IotLogging_Free( pLoggingBuffer );
}

/*-----------------------------------------------------------*/
