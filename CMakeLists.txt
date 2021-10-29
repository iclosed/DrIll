cmake_minimum_required(VERSION 3.10)

# set the project name and version
project(DrIll VERSION 1.0)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# should we use our own math functions
option(USE_MYMATH "Use tutorial provided math implementation" ON)

# configure a header file to pass some of the CMake settings
# to the source code
configure_file(TutorialConfig.h.in TutorialConfig.h)

# add the MathFunctions library
if(USE_MYMATH)
	add_subdirectory(MathFunctions)
	list(APPEND EXTRA_LIBS MathFunctions)
endif()

# add the executable
add_executable(${PROJECT_NAME} WIN32 main.cpp)

# 折叠ALL_BUILD 和 ZERO_CHECK 项:
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
# VS默认启动项设置:
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME} PUBLIC ${EXTRA_LIBS})

# add the binary tree to the search path for include files so that we will find TutorialConfig.h:
target_include_directories(${PROJECT_NAME} PUBLIC "${PROJECT_BINARY_DIR}")

