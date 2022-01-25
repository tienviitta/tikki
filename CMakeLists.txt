cmake_minimum_required(VERSION 3.16.3)

project(
    tikki 
    VERSION 0.1.0
    DESCRIPTION "Tikki card game"
    LANGUAGES CXX
)

include(CTest)
enable_testing()

Include(FetchContent)
FetchContent_Declare(
    spdlog
    GIT_REPOSITORY https://github.com/gabime/spdlog.git
    GIT_TAG v1.9.2
)
FetchContent_Declare(
    cxxopts
    GIT_REPOSITORY https://github.com/jarro2783/cxxopts.git
    GIT_TAG v3.0.0
)
FetchContent_MakeAvailable(spdlog cxxopts)

add_executable(
    tikki 
    main.cpp 
    src/tikki.cpp 
    src/deck.cpp 
    src/hand.cpp 
    src/card.cpp 
    inc/tikki/tikki.h 
    inc/tikki/deck.h 
    inc/tikki/hand.h 
    inc/tikki/card.h
)
target_compile_features(tikki PUBLIC cxx_std_17)
set_target_properties(tikki PROPERTIES CXX_EXTENSIONS OFF)
target_include_directories(tikki PRIVATE inc/tikki)
target_link_libraries(tikki PRIVATE spdlog::spdlog cxxopts::cxxopts)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
