#CMake 最低版本号要求
cmake_minimum_required (VERSION 2.8)

#项目信息
project (Network)

#Process subdirectories
add_subdirectory(apps)

add_subdirectory(common)

add_subdirectory(lib)

add_subdirectory(topology)

#寻找当前目录下的所有源文件
#并将名称保存到 DIR_SRCS 变量
aux_source_directory(. DIR_SRCS)

MESSAGE(STATUS "This is BINARY dir:" ${PROJECT_BINARY_DIR})
MESSAGE(STATUS "Project SOURCE directory:" ${PROJECT_SOURCE_DIR})

#指定生成目标
add_executable()
