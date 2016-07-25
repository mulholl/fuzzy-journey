cmake_minimum_required (VERSION 2.6)
project (fuzzy_journey)

SET (CMAKE_C_COMPILER             "/usr/bin/clang")
SET (CMAKE_C_FLAGS                "-Wall -std=c99")
SET (CMAKE_C_FLAGS_DEBUG          "-g")
SET (CMAKE_C_FLAGS_MINSIZEREL     "-Os -DNDEBUG")
SET (CMAKE_C_FLAGS_RELEASE        "-O4 -DNDEBUG")
SET (CMAKE_C_FLAGS_RELWITHDEBINFO "-O2 -g")

SET (CMAKE_CXX_COMPILER             "/usr/bin/clang++")
SET (CMAKE_CXX_FLAGS                "-Wall")
SET (CMAKE_CXX_FLAGS_DEBUG          "-g")
SET (CMAKE_CXX_FLAGS_MINSIZEREL     "-Os -DNDEBUG")
SET (CMAKE_CXX_FLAGS_RELEASE        "-O4 -DNDEBUG")
SET (CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O2 -g")

# The version number.
set (FUZZY_JOURNEY_VERSION_MAJOR 0)
set (FUZZY_JOURNEY_VERSION_MINOR 1)

find_package(OpenSSL REQUIRED)

message("OpenSSL include dir: ${OPENSSL_INCLUDE_DIR}")
message("OpenSSL libraries: ${OPENSSL_LIBRARIES}")

include_directories(${OPENSSL_INCLUDE_DIR})
#list(APPEND LIB_LIST ${OPENSSL_LIBRARIES})
set(FANTASTIC_TRAIN_LIBS ${FANTASTIC_TRAIN_LIBS} ${OPENSSL_LIBRARIES})

# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
  "${PROJECT_SOURCE_DIR}/fuzzy-journey-config.hpp.in"
  "${PROJECT_BINARY_DIR}/fuzzy-journey-config.hpp"
  )

# add the binary tree to the search path for include files
# so that we will find configured header files
include_directories("${PROJECT_BINARY_DIR}")

# Add the directory for our input argument parsing library
set (INP_OPTS_SOURCE_DIR "${PROJECT_SOURCE_DIR}/InpOpts/")
include_directories(${INP_OPTS_SOURCE_DIR})
add_subdirectory(InpOpts)
set (FANTASTIC_TRAIN_LIBS ${FANTASTIC_TRAIN_LIBS} InpOpts)

# add the binary tree to the search path for include files
# so that we will find configured header files
#include_directories("${PROJECT_BINARY_DIR}")
include_directories("${PROJECT_BINARY_DIR}/InpOpts/")

# Add the executables
add_executable (fuzzy_journey FuzzyJourney.cpp FuzzyJourneyFunctions.cpp Diceware.cpp)
target_link_libraries (fuzzy_journey ${FANTASTIC_TRAIN_LIBS})

add_definitions(-std=c++11)

# Use the C++ '11 standard
set_property(TARGET fuzzy_journey PROPERTY CXX_STANDARD_REQUIRED 11)