cmake_minimum_required(VERSION 3.10)

project(ArgusInterface)

SET( ARGUS_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/.. )
SET( ARGUS_INTERFACE_LIBNAME ${PROJECT_NAME}_bogus )
SET( ARGUS_LOADER_NAME       ${PROJECT_NAME}_bogusLoader )


####
# Libraries
####
find_package(Bogus REQUIRED)

####
# Sources and targets
####

#Lib 
file(GLOB SRC_LIST src/*.hh src/*.cc)
file(GLOB HEADERS src/*.hh)

add_library(${ARGUS_INTERFACE_LIBNAME} SHARED ${SRC_LIST})
target_include_directories(${ARGUS_INTERFACE_LIBNAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src )
target_link_libraries(${ARGUS_INTERFACE_LIBNAME} PUBLIC Bogus::bogus )
target_compile_options(${ARGUS_INTERFACE_LIBNAME} PRIVATE -DBUILD_ARGUS)


# Install
INSTALL( FILES ${HEADERS} DESTINATION include/${ARGUS_INTERFACE_LIBNAME})
INSTALL( TARGETS ${ARGUS_INTERFACE_LIBNAME}
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION lib
  ARCHIVE DESTINATION lib )

# Friction problem loader
add_executable(${ARGUS_LOADER_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/test/loader.cpp )
target_link_libraries(${ARGUS_LOADER_NAME} ${ARGUS_INTERFACE_LIBNAME} )


