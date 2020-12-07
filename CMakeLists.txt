cmake_minimum_required(VERSION 3.10)

project(ArgusInterface CXX)


list(APPEND CMAKE_PREFIX_PATH ${CMAKE_BINARY_DIR})

# Require C++11 compiler
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Visual studio solution directories.
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

if((CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT))
    set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/install" CACHE PATH "Prefix prepended to install directories" FORCE)
    message(STATUS "Setting default CMAKE_INSTALL_PREFIX to: ${CMAKE_INSTALL_PREFIX}")
endif()

# Set the output directories globally
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

####
# Compiler flags
####

if (NOT CMAKE_BUILD_TYPE)
  message(STATUS "No build type selected, default to Release")
  set(CMAKE_BUILD_TYPE "Release")
endif()

if ( "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang" )
  set (CLANG TRUE)
  set( CMAKE_EXPORT_COMPILE_COMMANDS 1 )
elseif( "${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" )
  set (GCC TRUE)
endif()

# Maybe dangerous to set -O3 globally...
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")

if ( GCC OR CLANG )
				SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -std=c++11 " )
				SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-deprecated-declarations " )
				SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Werror " )
				#SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}  -march=native -ffast-math -DEIGEN_NO_DEBUG ")
endif()


set( BOGUS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/extern/so-bogus/bogus )
set( BOGUS_INTERFACE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/interface )

add_subdirectory( ${BOGUS_DIR} )
add_subdirectory( ${BOGUS_INTERFACE_DIR} )
