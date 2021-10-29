cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

# Define Project ###############################################################
project("NTOU FreeGLUT Beginner Template"
    VERSION 0.2.0
    DESCRIPTION "A quick OpenGL and GLUT setup for beginners."
)


# Create Binary Target #########################################################
add_executable(my-exe-target)


# Compiler Settings ############################################################
## Require C++17.
target_compile_features(my-exe-target PRIVATE cxx_std_17)

## Change the properties of our executable target.
set_target_properties(my-exe-target PROPERTIES
    # Set executable name
    OUTPUT_NAME "glut-example"
    # Turn off compiler extensions for portability
    C_EXTENSIONS   OFF
    CXX_EXTENSIONS OFF
)

## Extra Debug and Release Settings
if (CMAKE_C_COMPILER_ID STREQUAL "GNU")
    list(APPEND CompilerFlags -Wall -Wextra --pedantic-errors)
    list(APPEND CompilerFlags_Debug -ggdb)
    list(APPEND CompilerFlags_Release)
elseif(CMAKE_C_COMPILER_ID STREQUAL "Clang")
    list(APPEND CompilerFlags -Wall -Wextra --pedantic-errors)
    list(APPEND CompilerFlags_Release)
elseif(CMAKE_C_COMPILER_ID STREQUAL "MSVC")
    list(APPEND CompilerFlags /W4)
    list(APPEND CompilerFlags_Debug)
    list(APPEND CompilerFlags_Release)
endif()

target_compile_options(my-exe-target PRIVATE "${CompilerFlags}")
target_compile_options(my-exe-target PRIVATE "$<$<CONFIG:Debug>:${CompilerFlags_Debug}>")
target_compile_options(my-exe-target PRIVATE "$<$<CONFIG:Release>:${CompilerFlags_Release}>")


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
file(GLOB MySourceFiles CONFIGURE_DEPENDS "src/*.cpp")

## Assign source files to the executable target.
target_sources(my-exe-target PRIVATE ${MySourceFiles})


# Link the Libraries ###########################################################
## Link the external libraries
target_link_libraries(my-exe-target PRIVATE
    OpenGL::GL
    OpenGL::GLU
    GLUT::GLUT
    imgui::imgui
    glm::glm
)

if (CMAKE_SYSTEM_NAME STREQUAL "Linux")
    target_link_libraries(my-exe-target PRIVATE X11)
endif()


# CPack ########################################################################
#[[
Package source files of the project with CPack module.

Command:
    cmake --build <build-dir> --target package_source

You'll see a ZIP file named "<project-name>-<version>-Source.zip" in your build directory.
]]
include(CMakeCPack.cmake)
