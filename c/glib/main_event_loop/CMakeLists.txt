cmake_minimum_required(VERSION 3.0)

set (CMAKE_VERBOSE_MAKEFILE 1)

project (main_event_loop C)

set (CMAKE_BUILD_TYPE Debug)

set (CMAKE_C_FLAGS "-Wall -Werror")

set (TARGET_EXE_NAME main_event_loop)
set (SRCS
    main.c
)

execute_process (
    COMMAND pkg-config --cflags glib-2.0
    OUTPUT_VARIABLE GLIB_CFLAGS
    OUTPUT_STRIP_TRAILING_WHITESPACE
)
message ("GLIB_CFLAGS:" ${GLIB_CFLAGS})

execute_process (
    COMMAND pkg-config --libs glib-2.0
    OUTPUT_VARIABLE GLIB_LIBS
    OUTPUT_STRIP_TRAILING_WHITESPACE
)
message ("GLIB_LIBS:" ${GLIB_LIBS})

set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${GLIB_CFLAGS}")
include_directories ()
link_directories ()

set (LIBS
    ${GLIB_LIBS}
)

add_executable (${TARGET_EXE_NAME} ${SRCS})
target_link_libraries (${TARGET_EXE_NAME} ${LIBS})
