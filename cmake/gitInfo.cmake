#--------------------------------------------------------------------------------------------------
#
#   GIT INFO
#
# --------------------------------------------------------------------------------------------------
#
#  The MIT License (MIT)
#
#  Permission is hereby granted, free of charge, to any person obtaining a copy of this software
#  and associated documentation files (the "Software"), to deal in the Software without
#  restriction, including without limitation the rights to use, copy, modify, merge, publish,
#  distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
#  Software is furnished to do so, subject to the following conditions:
#
#  The above copyright notice and this permission notice shall be included in all copies or
#  substantial portions of the Software.
#
#  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
#  BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
#  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
#  DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
#  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
#
# --------------------------------------------------------------------------------------------------
#
#  Copyright (c) 2020 Nic Holthaus
#
# --------------------------------------------------------------------------------------------------

if(GIT_FOUND)

    set(GIT_BRANCH "N/A")
    set(GIT_COMMIT_SHORT "N/A")
    set(GIT_COMMIT_LONG "N/A")
    set(GIT_TAG "N/A")
    set(GIT_ORIGIN "N/A")
    set(GIT_DIRECTORY "N/A")
    set(GIT_REPO "N/A")
    set(GIT_USER "N/A")
    set(GIT_EMAIL "N/A")

    execute_process(
            COMMAND ${GIT_EXECUTABLE} rev-parse --abbrev-ref HEAD
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
            OUTPUT_VARIABLE GIT_BRANCH
            OUTPUT_STRIP_TRAILING_WHITESPACE
    )
    execute_process(
            COMMAND ${GIT_EXECUTABLE} rev-parse --short HEAD
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
            OUTPUT_VARIABLE GIT_COMMIT_SHORT
            OUTPUT_STRIP_TRAILING_WHITESPACE
    )
    execute_process(
            COMMAND ${GIT_EXECUTABLE} rev-parse HEAD
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
            OUTPUT_VARIABLE GIT_COMMIT_LONG
            OUTPUT_STRIP_TRAILING_WHITESPACE
    )
    execute_process(
            COMMAND ${GIT_EXECUTABLE} describe --abbrev=0 --tags
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
            OUTPUT_VARIABLE GIT_TAG
            OUTPUT_STRIP_TRAILING_WHITESPACE
    )
    execute_process(
            COMMAND ${GIT_EXECUTABLE} config --get remote.origin.url
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
            OUTPUT_VARIABLE GIT_ORIGIN
            OUTPUT_STRIP_TRAILING_WHITESPACE
    )
    execute_process(
            COMMAND ${GIT_EXECUTABLE} rev-parse --show-toplevel
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
            OUTPUT_VARIABLE GIT_DIRECTORY
            OUTPUT_STRIP_TRAILING_WHITESPACE
    )
    execute_process(
            COMMAND basename ${GIT_DIRECTORY}
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
            OUTPUT_VARIABLE GIT_REPO
            OUTPUT_STRIP_TRAILING_WHITESPACE
    )
    execute_process(
            COMMAND ${GIT_EXECUTABLE} config --get user.name
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
            OUTPUT_VARIABLE GIT_USER
            OUTPUT_STRIP_TRAILING_WHITESPACE
    )
    execute_process(
            COMMAND ${GIT_EXECUTABLE} config --get user.email
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
            OUTPUT_VARIABLE GIT_EMAIL
            OUTPUT_STRIP_TRAILING_WHITESPACE
    )
    execute_process(
            COMMAND ${GIT_EXECUTABLE} status --porcelain
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
            OUTPUT_VARIABLE GIT_DIRTY
            OUTPUT_STRIP_TRAILING_WHITESPACE
    )

    set(APP_NAME ${GIT_REPO})
    set(APP_VERSION ${GIT_TAG})

    if("${GIT_DIRTY}" STREQUAL "")
        set(GIT_DIRTY_STRING "")
        set(GIT_DIRTY_FLAG "no")

    else()
        set(GIT_DIRTY_STRING " (dirty)")
        set(GIT_DIRTY_FLAG "yes")
    endif()

    message(STATUS "---------  GIT INFO  ---------")
    message(STATUS "REPO:          " ${GIT_REPO})
    message(STATUS "BRANCH:        " ${GIT_BRANCH})
    message(STATUS "TAG:           " ${GIT_TAG})
    message(STATUS "LOCAL CHANGES: " ${GIT_DIRTY_FLAG})
    message(STATUS "------------------------------")
else()
    set(GIT_BRANCH "N/A")
    set(GIT_COMMIT_SHORT "N/A")
    set(GIT_COMMIT_LONG "N/A")
    set(GIT_TAG "N/A")
    set(GIT_ORIGIN "N/A")
    set(GIT_DIRECTORY "N/A")
    set(GIT_REPO "N/A")
    set(GIT_USER "N/A")
    set(GIT_EMAIL "N/A")
endif()

