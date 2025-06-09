# Cria o executável principal do seu banco de dados
add_executable(auroradb main.cpp)

# Permite que seu código-fonte encontre os headers na pasta 'include'
target_include_directories(auroradb PUBLIC ../include)