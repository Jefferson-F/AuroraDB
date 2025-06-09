# Versão e nome do projeto AuroraDB
cmake_minimum_required(VERSION 3.16)
project(AuroraDB LANGUAGES CXX)

# Define o padrão C++17, conforme seu PRD 
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Adiciona o diretório com o código-fonte principal
add_subdirectory(src)

# Habilita e adiciona o diretório de testes
#enable_testing()
#add_subdirectory(tests)