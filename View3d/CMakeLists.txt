CMAKE_MINIMUM_REQUIRED(VERSION 3.26)

PROJECT("3D View" VERSION 1.0.0 LANGUAGES C CXX)

IF (NOT CMAKE_BUILD_TYPE)
    SET(CMAKE_BUILD_TYPE Release)
ENDIF()
MESSAGE("-- Using configuration: " ${CMAKE_BUILD_TYPE})

# Set build options.
SET(CMAKE_CXX_STANDARD 20)
SET(CMAKE_CXX_STANDARD_REQUIRED True)
SET(CMAKE_CXX_FLAGS "-Wpedantic -Wall -Wextra -Werror")
SET(CMAKE_CXX_FLAGS_DEBUG "-g -DDEBUG")
SET(CMAKE_CXX_FLAGS_RELEASE "-O3")
SET(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Source files.
INCLUDE_DIRECTORIES(src)
SET(SRC src/View3D.cpp
        src/App.cpp
        src/Camera.cpp
        src/Cube.cpp
        src/Renderer.cpp
        src/Shader.cpp
        src/ShaderFactory.cpp)

# Add static library for Glad.
ADD_LIBRARY(Glad STATIC src/glad.c)

# Add exe target.
ADD_EXECUTABLE(View3D ${SRC})
TARGET_SOURCES(View3D PUBLIC ${SRC})

TARGET_PRECOMPILE_HEADERS(View3D PUBLIC src/pch.hpp)
TARGET_LINK_LIBRARIES(View3D PUBLIC glfw3 gdi32 Glad)

# Copy shaders.
FILE(COPY ./shaders DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
