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
 * @file logging.c
 * @brief Implementation of the generic logging function.
 */

/* Standard includes. */
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <mqueue.h>
#include <pthread.h>
#include <signal.h>

/* Platform clock include. */
#include "clock.h"

/* Include headers for logging files. */
#include "logging_levels.h"
#include "logging_function.h"

/*-----------------------------------------------------------*/

/**
 * @brief A guess of the maximum length of a timestring.
 *
 * There's no way for this logging library to know the length of a timestring
 * before it's generated. Therefore, the logging library will assume a maximum
 * length of any timestring it may get. This value should be generous enough
 * to accommodate the vast majority of timestrings.
 */
#define MAX_TIMESTRING_LENGTH    ( 64 )

#define LOGGING_QUEUE_NAME       "/logging-queue1"
#define QUEUE_PERMISSIONS        0660
#define MAX_MESSAGES             10
#define MAX_MSG_SIZE             256
#define MSG_BUFFER_SIZE          MAX_MSG_SIZE + 10

static pthread_t loggingThread;

typedef struct message
{
    char logBuffer[ MAX_MSG_SIZE - 1 ];
    uint8_t numOfBytes;
} message;

/*-----------------------------------------------------------*/

static bool _reallocLoggingBuffer( void ** pOldBuffer,
                                   size_t newSize,
                                   size_t oldSize )
{
    bool status = false;

    /* Allocate a new, larger buffer. */
    void * pNewBuffer = malloc( newSize );

    /* Ensure that memory allocation succeeded. */
    if( pNewBuffer != NULL )
    {
        /* Copy the data from the old buffer to the new buffer. */
        ( void ) memcpy( pNewBuffer, *pOldBuffer, oldSize );

        /* Free the old buffer and update the pointer. */
        free( *pOldBuffer );
        *pOldBuffer = pNewBuffer;

        status = true;
    }

    return status;
}

/*-----------------------------------------------------------*/

void sig_handler( int signo )
{
    if( signo == SIGINT )
    {
        pthread_exit( NULL );
    }
}


void loggingService( void * arg )
{
    mqd_t logging_qd; /* queue descriptors */
    struct mq_attr attr;
    message recvMessage;

    attr.mq_flags = 0;
    attr.mq_maxmsg = MAX_MESSAGES;
    attr.mq_msgsize = MAX_MSG_SIZE;
    attr.mq_curmsgs = 0;

    logging_qd = mq_open( LOGGING_QUEUE_NAME, O_RDONLY | O_CREAT, QUEUE_PERMISSIONS, &attr );
    printf( "Testing print from thread\n" );

    if( logging_qd == -1 )
    {
        printf( "ERROR in logging service: Queue creation failed.\n" );
    }

    /* Register signal handler for thread termination. */
    if( signal( SIGINT, sig_handler ) == SIG_ERR )
    {
        printf( "ERROR in logging service: Failed to register signal handler.\n" );
    }

    for( ; ; )
    {
        /* Dequeue log message string. */
        if( mq_receive( logging_qd, &recvMessage, MAX_MSG_SIZE, NULL ) == -1 )
        {
            printf( "ERROR in logging service: Failed to read from queue!\n" );
        }
        else
        {
            recvMessage.logBuffer[ recvMessage.numOfBytes ] = '\0';

            printf( "%s", recvMessage.logBuffer );
        }
    }
}


void initializeLogging()
{
    pthread_create( &loggingThread, NULL, loggingService, NULL );
}

void terminateLogging()
{
    pthread_kill( loggingThread, SIGINT );
    pthread_join( loggingThread, NULL );
}

void sdkLogGeneric( const char * const pFormat,
                    ... )
{
    int requiredMessageSize = 0;
    message messageInfo;
    va_list args;

    va_start( args, pFormat );

    /* Add the log message to the logging buffer. */
    requiredMessageSize = vsnprintf( messageInfo.logBuffer,
                                     sizeof( messageInfo.logBuffer ),
                                     pFormat,
                                     args );

    if( requiredMessageSize < sizeof( messageInfo.logBuffer ) )
    {
        messageInfo.numOfBytes = requiredMessageSize;

        va_end( args );

        mqd_t logging_qd; /* queue descriptors */

        logging_qd = mq_open( LOGGING_QUEUE_NAME, O_WRONLY );

        if( logging_qd == -1 )
        {
            printf( "ERROR in logging: queue cannot be created\n" );
        }

        /* Enqueue the buffer. */
        if( mq_send( logging_qd, &messageInfo, MAX_MSG_SIZE, 0 ) == -1 )
        {
            printf( "ERROR in logging: Logging buffer cannot be queued!\n" );
        }
    }
}

void sdkLogGenericWithTimestring( const char * const pFormat,
                                  ... )
{
    int requiredMessageSize = 0;
    size_t bufferSize = 0,
           bufferPosition = 0, timestringLength = 0;
    char * pLoggingBuffer = NULL;
    va_list args;

    /* Add length of timestring. */
    bufferSize += MAX_TIMESTRING_LENGTH;

    /* Add 64 as an initial (arbitrary) guess for the length of the message. */
    bufferSize += 64;

    /* Allocate memory for the logging buffer. */
    pLoggingBuffer = ( char * ) malloc( bufferSize );

    if( pLoggingBuffer == NULL )
    {
        return;
    }

    /* Print the timestring if requested. */
    /* Add the opening '[' enclosing the timestring. */
    pLoggingBuffer[ bufferPosition ] = '[';
    bufferPosition++;

    /* Generate the timestring and add it to the buffer. */
    if( Clock_GetTimestring( pLoggingBuffer,
                             bufferSize,
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
        if( _reallocLoggingBuffer( ( void ** ) &pLoggingBuffer,
                                   ( size_t ) requiredMessageSize + bufferPosition + 1,
                                   bufferSize ) == false )
        {
            /* If buffer reallocation failed, return. */
            free( pLoggingBuffer );

            return;
        }

        /* Reallocation successful, update buffer size. */
        bufferSize = ( size_t ) requiredMessageSize + bufferPosition + 1;

        /* Add the log message to the buffer. Now that the buffer has been
         * reallocated, this should succeed. */
        requiredMessageSize = vsnprintf( pLoggingBuffer + bufferPosition,
                                         bufferSize - bufferPosition,
                                         pFormat,
                                         args );
    }

    /* Check for encoding errors. */
    if( requiredMessageSize <= 0 )
    {
        free( pLoggingBuffer );

        return;
    }

    /* Print the logging buffer to stdout. */
    puts( pLoggingBuffer );

    /* Free the logging buffer. */
    free( pLoggingBuffer );
}

/*-----------------------------------------------------------*/
