cmake_minimum_required(VERSION 3.10)

# set the project name and version
project(DrIll VERSION 1.0)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(OpenCV_DIR "../opencv")


add_executable(${PROJECT_NAME} WIN32 main.cpp)

# 3rd party libs:
find_package(OpenCV REQUIRED)
#message(STATUS "config: ${OpenCV_DIR}")
#message(STATUS "version: ${OpenCV_VERSION}")
#message(STATUS "libraries: ${OpenCV_LIBS}")
#message(STATUS "include path: ${OpenCV_INCLUDE_DIRS}")
target_link_libraries(${PROJECT_NAME} PRIVATE ${OpenCV_LIBS})
include_directories(${OpenCV_INCLUDE_DIRS})

# modules to import:
list(APPEND EXTRA_LIBS _m_example)
list(APPEND EXTRA_LIBS img_proc)
list(APPEND EXTRA_LIBS windows_api)
target_link_libraries(${PROJECT_NAME} PRIVATE ${EXTRA_LIBS})
#message(STATUS "~~~ Extra libs are: ${EXTRA_LIBS}")
foreach(LETTER IN LISTS EXTRA_LIBS)
	include_directories(${LETTER})
	add_subdirectory(${LETTER})
endforeach()

# 折叠ALL_BUILD 和 ZERO_CHECK 项:
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
# VS默认启动项设置:
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})

