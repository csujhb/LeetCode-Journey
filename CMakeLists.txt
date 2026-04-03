cmake_minimum_required(VERSION 3.10)
project(MyAlgorithmNotes)

# 支持 C11 和 C++17
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# 【新增核心修复】：强制 MSVC 编译器使用 UTF-8 编码，彻底告别乱码
if(MSVC)
    add_compile_options(/utf-8)
endif()

# 1. 递归搜索所有源码 (.c, .cpp)
file(GLOB_RECURSE SOURCE_FILES "*.c" "*.cpp")

foreach(FILE ${SOURCE_FILES})
    # 生成安全的 MD5 目标名
    string(MD5 TARGET_HASH "${FILE}")
    set(TARGET_NAME "algo_lib_${TARGET_HASH}")
    
    # 使用纯英文的目标名进行编译，文件依然是你的中文路径文件
    add_library(${TARGET_NAME} STATIC ${FILE})
endforeach()