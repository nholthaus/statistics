#-------------------------------------------------------------------------------
#	CMAKE SETTINGS
#-------------------------------------------------------------------------------

cmake_minimum_required(VERSION 3.7)

#-------------------------------------------------------------------------------
#	PROJECT SETTINGS
#-------------------------------------------------------------------------------

PROJECT(statisticsTest CXX)

#-------------------------------------------------------------------------------
#	3rd Party
#-------------------------------------------------------------------------------

find_package(Threads)
add_subdirectory(googletest-1.10.0)

#-------------------------------------------------------------------------------
#	SOURCE CODE
#-------------------------------------------------------------------------------

# .h files
list(APPEND HEADER_FILES
        ../include/statistics.h
        units.h
    )

# .cpp files
list(APPEND SOURCE_FILES
        main.cpp
    )

if(MSVC)
    list(APPEND SOURCE_FILES ${HEADER_FILES})
endif()

#-------------------------------------------------------------------------------
#	INCLUDE DIRECTORIES
#-------------------------------------------------------------------------------

include_directories(${CMAKE_SOURCE_DIR}/include)

#-------------------------------------------------------------------------------
#	ADDITIONAL LIBRARIES
#-------------------------------------------------------------------------------

list(APPEND LIBRARIES
        googletest
    )

# Remove duplicate library dependencies.
list(REMOVE_DUPLICATES LIBRARIES)

#-------------------------------------------------------------------------------
#	GENERATE TEST EXECUTABLE
#-------------------------------------------------------------------------------

include(GoogleTest)

# Generate the executable
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

# link libraries
target_link_libraries(${PROJECT_NAME} ${LIBRARIES})

# Use the automatically determined RPATH values
set_target_properties(${PROJECT_NAME} PROPERTIES INSTALL_RPATH_USE_LINK_PATH TRUE)

gtest_add_tests(TARGET ${PROJECT_NAME} AUTO)

INSTALL(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION tests)