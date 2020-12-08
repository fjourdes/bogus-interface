cmake_minimum_required(VERSION 3.10)

project(ArgusInterface)

SET( ARGUS_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/.. )

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

add_library(interface SHARED ${SRC_LIST})
target_include_directories(interface PUBLIC 
                           $<INSTALL_INTERFACE:include>
                           $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src> )

target_link_libraries(interface PUBLIC Bogus::bogus )
target_compile_options(interface PRIVATE -DBUILD_ARGUS)

add_library(Argus::interface ALIAS interface)

# Friction problem loader
add_executable(loader ${CMAKE_CURRENT_SOURCE_DIR}/test/loader.cpp )
target_link_libraries(loader interface )

add_executable(Argus::loader ALIAS loader)

include(GNUInstallDirs)

# Install
install( FILES ${HEADERS} DESTINATION include/${ARGUS_INTERFACE_LIBNAME})

install(TARGETS interface loader
        EXPORT ArgusTargets
        INCLUDES DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
        RUNTIME DESTINATION  "${CMAKE_INSTALL_BINDIR}"
        LIBRARY DESTINATION  "${CMAKE_INSTALL_LIBDIR}"
        ARCHIVE DESTINATION  "${CMAKE_INSTALL_LIBDIR}"
)

include(CMakePackageConfigHelpers)

configure_package_config_file(ArgusConfig.cmake.in
    ${CMAKE_BINARY_DIR}/Bogus/ArgusConfig.cmake
    INSTALL_DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/Argus"
)

install(FILES ${CMAKE_BINARY_DIR}/Argus/ArgusConfig.cmake
    DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/Argus")

install( EXPORT ArgusTargets
        NAMESPACE "Argus::"
        DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/Argus")
