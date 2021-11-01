cmake_minimum_required(VERSION 3.10)

# set the project name and version
project(DrIll VERSION 1.0)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(src)
add_subdirectory(src)

# add the executable
add_executable(${PROJECT_NAME} WIN32 main.cpp)

target_link_libraries(${PROJECT_NAME} PUBLIC Modules)

# 折叠ALL_BUILD 和 ZERO_CHECK 项:
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
# VS默认启动项设置:
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})

