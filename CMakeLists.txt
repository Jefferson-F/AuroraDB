cmake_minimum_required(VERSION 4.0)
project(AuroraDB)

set(CMAKE_CXX_STANDARD 17)

add_executable(AuroraDB main.cpp
        src/storage/include/PageManager.h
        src/storage/PageManager.cpp
        src/storage/include/Registro.h
        src/storage/include/Page.h
        src/storage/BufferPoolManager.cpp
        src/storage/include/BufferPoolManager.h
        src/storage/include/FullTableScan.h
        src/storage/FullTableScan.cpp
)
