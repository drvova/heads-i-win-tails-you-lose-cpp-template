cmake_minimum_required(VERSION 3.24)

project(heads_i_win_tails_you_lose)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

Include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.8.1
)

FetchContent_MakeAvailable(Catch2)

add_executable(coin_test tests/coin_test.cpp src/coin.cpp)
add_executable(experiment_test tests/experiment_test.cpp src/coin.cpp src/experiment.cpp)
add_executable(main main.cpp src/coin.cpp src/experiment.cpp)

target_link_libraries(coin_test PRIVATE Catch2::Catch2WithMain)
target_link_libraries(experiment_test PRIVATE Catch2::Catch2WithMain)
