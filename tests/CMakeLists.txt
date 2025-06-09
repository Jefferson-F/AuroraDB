# Inclui a funcionalidade para baixar dependências
include(FetchContent)

# Declara o GoogleTest, com a correção que descobrimos (GIT_SHALLOW FALSE)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.14.0 # Uma versão estável do GoogleTest
  GIT_SHALLOW    FALSE
)

# Torna o GoogleTest disponível para ser usado pelos seus testes
FetchContent_MakeAvailable(googletest)

# Exemplo de como você criará um executável de teste
# add_executable(meu_teste_de_parser parser_tests.cpp)
# target_link_libraries(meu_teste_de_parser PRIVATE GTest::gtest_main)
# ...