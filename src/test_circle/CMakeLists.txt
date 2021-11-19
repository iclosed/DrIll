# 获取当前文件夹名称 -> CURRENT_FOLDER
string(REGEX REPLACE "/$" "" CURRENT_FOLDER_ABS ${CMAKE_CURRENT_SOURCE_DIR})
string(REGEX REPLACE ".*/(.*)" "\\1" CURRENT_FOLDER ${CURRENT_FOLDER_ABS})

# Source Files 源文件添加 -> SRC_LIST
aux_source_directory(. SRC_LIST)

# Head Files 头文件添加 -> HEAD_LIST
file(GLOB_RECURSE HEAD_LIST  *.h *.hpp)

#生成应用程序 hello (在windows下会自动生成hello.exe)
add_library(${CURRENT_FOLDER} ${SRC_LIST} ${HEAD_LIST})

