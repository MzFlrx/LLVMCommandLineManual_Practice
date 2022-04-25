cmake_minimum_required(VERSION 3.10)

project(test)


SET(clang_llvm_dir /home/mzflrx/Downloads/clang+llvm-8.0.0-x86_64-linux-gnu-ubuntu-18.04)
set(CMAKE_C_COMPILER ${clang_llvm_dir}/bin/clang)
set(CMAKE_CXX_COMPILER ${clang_llvm_dir}/bin/clang++)
SET(LLVM_DIR ${clang_llvm_dir}/lib/cmake/llvm)
SET(CMAKE_PREFIX_PATH  /${clang_llvm_dir}/lib/cmake)
set(CMAKE_CXX_STANDARD 14)

include_directories(${clang_llvm_dir}/include)
link_directories(${clang_llvm_dir}/lib)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-rtti -std=c++14 -g")

# Now build our tools
find_package(LLVM REQUIRED CONFIG)

add_executable(test
    test.cpp)

target_link_libraries(test ${llvm_libs})

add_dependencies(test intrinsics_gen)

target_link_libraries(test
    LLVMSupport)