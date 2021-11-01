cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

# Define Project ###############################################################
project("NTOU FreeGLUT Beginner Template"
    VERSION 0.2.0
    DESCRIPTION "A quick OpenGL and GLUT setup for beginners."
)


# Create Binary Target #########################################################
add_executable(glut-example)


# Compiler Settings ############################################################
## Require C++17.
target_compile_features(glut-example PRIVATE cxx_std_17)

## Change the properties of our executable target.
set_target_properties(glut-example PROPERTIES
    # Turn off compiler extensions for cross-platform portability
    C_EXTENSIONS   OFF
    CXX_EXTENSIONS OFF
)

## Compiler flags for different compilers and different build configurations.
if (CMAKE_C_COMPILER_ID STREQUAL "GNU")
    list(APPEND CompileOptions "-Wall" "-Wextra" --pedantic-errors)
    list(APPEND CompileOptions_Debug -ggdb)
    list(APPEND CompileOptions_Release)
    target_compile_definitions(glut-example PRIVATE $<$<CONFIG:Debug>:_GLIBCXX_DEBUG>)
elseif(CMAKE_C_COMPILER_ID STREQUAL "Clang")
    list(APPEND CompileOptions -Wall -Wextra --pedantic-errors)
    list(APPEND CompileOptions_Debug)
    list(APPEND CompileOptions_Release)
elseif(CMAKE_C_COMPILER_ID STREQUAL "MSVC")
    list(APPEND CompileOptions /W4)
    list(APPEND CompileOptions_Debug)
    list(APPEND CompileOptions_Release)
endif()

## Set the compile options of targets according to the "build configuration".
#[[
    $<CONFIG:cfgs>
        1 if config is any one of the entries in comma-separated list cfgs.

    $<CONFIG:Debug>
        Evaluates to 1 if the build configuration is "Debug", or else it evaluates to 0.

    $<CONFIG:Release>
        Evaluates to 1 if the build configuration is "Release", or else it evaluates to 0.

    $<$<CONFIG:Debug>:"Debug Mode">
        Expands to "Debug Mode" when the "Debug" configuration is used, or else expands to an empty string.

    $<$<CONFIG:Release>:"Release Mode">
        Expands to "Release Mode" when the "Release" configuration is used, or else expands to an empty string.

    See details about generator-expressions at
        https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html
]]
target_compile_options(glut-example PRIVATE "${CompileOptions}")
target_compile_options(glut-example PRIVATE "$<$<CONFIG:Debug>:${CompileOptions_Debug}>")
target_compile_options(glut-example PRIVATE "$<$<CONFIG:Release>:${CompileOptions_Release}>")


# Build Information ############################################################
message(STATUS)
message(STATUS "Build Information")
message(STATUS "\tHost System Name:       ${CMAKE_HOST_SYSTEM_NAME}" )
message(STATUS "\tHost System Version:    ${CMAKE_HOST_SYSTEM_VERSION}" )
message(STATUS "\tHost System Processor:  ${CMAKE_HOST_SYSTEM_PROCESSOR}" )
message(STATUS)
message(STATUS "\tC Compiler:             ${CMAKE_C_COMPILER_ID} ${CMAKE_C_COMPILER_VERSION}")
message(STATUS "\tC Compiler Path:        ${CMAKE_C_COMPILER}")
message(STATUS)
message(STATUS "\tC++ Compiler:           ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}")
message(STATUS "\tC++ Compiler Path:      ${CMAKE_CXX_COMPILER}")
message(STATUS)

if(MSVC)
  message(STATUS "\tMSVC Version: ${MSVC_VERSION}")
  message(STATUS "\tMSVC Toolset: ${MSVC_TOOLSET_VERSION}")
endif()

if(CMAKE_GENERATOR MATCHES "Xcode")
  message( STATUS "\tXcode Version: ${XCODE_VERSION}" )
endif()

if(CMAKE_SYSTEM_NAME MATCHES "Darwin")
  message(STATUS "\tMacOS SDK: ${CMAKE_OSX_SYSROOT}")
endif()


# Find External Libraries ######################################################
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(imgui REQUIRED)
find_package(glm REQUIRED)


# Source Files #################################################################
## Collect source files and assign them to a variable
file(GLOB My_Source CONFIGURE_DEPENDS "src/*.cpp")

## Assign source files to the executable target.
target_sources(glut-example PRIVATE ${My_Source})


# Link the Libraries ###########################################################
## Link the external libraries
target_link_libraries(glut-example PRIVATE
    OpenGL::GL
    OpenGL::GLU
    GLUT::GLUT
    imgui::imgui
    glm::glm
)

if (CMAKE_SYSTEM_NAME STREQUAL "Linux")
    target_link_libraries(glut-example PRIVATE X11)
endif()


# CPack ########################################################################
#[[
Package source files of the project with CPack module.

Command:
    cmake --build <build-dir> --target package_source

You'll see a ZIP file named "<project-name>-<version>-Source.zip" in your build directory.
]]
include(CMakeCPack.cmake)
