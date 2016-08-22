# CMake 最低版本号要求
if(CMAKE_GENERATOR MATCHES Xcode AND XCODE_VERSION VERSION_GREATER 4.3)
  cmake_minimum_required(VERSION 2.8.8)
elseif(IOS)
  cmake_minimum_required(VERSION 2.8.0)
else()
  cmake_minimum_required(VERSION 2.6.3)
endif()

# 找到头文件
include_directories(../common)
include_directories(../topology)
include_directories(../lib)
include_directories(../exception)

# 查找当前目录下面的所有源文件
# 并将名称保存到 DIR_SRCS 变量
aux_source_directory(. DIR_LIB_SRCS)

# 生成链接库
add_library(apps ${DIR_LIB_SRCS})

set (CMAKE_CXX_FLAGS "-g")
set (CMAKE_CXX_FLAGS "-Wall")
set (CMAKE_CXX_FLAGS "-I/usr/local/include")
#set (CMAKE_CXX_FLAGS "-L/usr/local/lib")

if (APPLE) 
	set (CMAKE_CXX_FLAGS "-stdlib=libstdc++") 
endif()
