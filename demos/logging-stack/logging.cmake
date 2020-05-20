# Configuration for logging.
set( LOGGING_INCLUDE_DIRS
     ${CMAKE_CURRENT_LIST_DIR} )

set( LOGGING_SOURCES
     ${CMAKE_CURRENT_LIST_DIR}/clock_posix.c 
     ${CMAKE_CURRENT_LIST_DIR}/logging_function_posix.c )