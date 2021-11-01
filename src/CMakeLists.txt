#aux_source_directory(. DIR_SRCS)
#add_library(Modules ${DIR_SRCS})


file(GLOB_RECURSE CURRENT_HEADERS  *.h *.hpp)
#source_group("Include" FILES ${CURRENT_HEADERS})

#把当前目录(.)下所有源代码文件和头文件加入变量SRC_LIST
aux_source_directory(. SRC_LIST)
#生成应用程序 hello (在windows下会自动生成hello.exe)
add_library(Modules ${SRC_LIST} ${CURRENT_HEADERS})
