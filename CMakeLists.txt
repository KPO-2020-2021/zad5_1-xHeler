cmake_minimum_required(VERSION 3.16)
project(Drone)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(test)
add_subdirectory(lib/googletest)

include_directories(inc)

file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true inc/*.h src/*.cpp)
set(SOURCE ${SOURCES})

add_executable(${CMAKE_PROJECT_NAME}_run ${SOURCES})
add_library(${CMAKE_PROJECT_NAME}_lib STATIC ${SOURCE})

# Doxygen

option(BUILD_DOC "Build documentation" ON)
find_package(Doxygen)
if (DOXYGEN_FOUND)
    set(DOXYGEN_IN ${CMAKE_SOURCE_DIR}/docs/Doxyfile.in)
    set(DOXYGEN_OUT ${CMAKE_BINARY_DIR}/Doxyfile)

    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
    message("Doxygen build started")
    add_custom_target(doc_doxygen ALL COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT} WORKING_DIRECTORY ${CMAKE_BINARY_DIR} COMMENT "Generate doxygen" VERBATIM)
else(DOXYGEN_FOUND)
    message("Doxygen not found, need to be installed to generate the doxygen")
endif()