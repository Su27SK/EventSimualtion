# CMake 最低版本号要求
if(CMAKE_GENERATOR MATCHES Xcode AND XCODE_VERSION VERSION_GREATER 4.3)
  cmake_minimum_required(VERSION 2.8.8)
elseif(IOS)
  cmake_minimum_required(VERSION 2.8.0)
else()
  cmake_minimum_required(VERSION 2.6.3)
endif()

# 项目信息
project (Network)

# 查找当前目录下面的所有源文件
# 并将名称保存到 DIR_SRCS 变量
aux_source_directory(. DIR_LIB_SRCS)

# 添加子目录
add_subdirectory(topology)

add_subdirectory(common)

add_subdirectory(apps)

# 指定生成目标
add_executable(BulkTest BulkTest.c)

# 添加链路库
target_link_libraries(BulkTest apps common topology)
