cmake_minimum_required(VERSION 3.0)

set(CMAKE_C_COMPILER clang)
set(CMAKE_CXX_COMPILER clang++)

project(AudacityNoiseReduction VERSION 1.0.0)

add_compile_options(-std=c++11 -Wall -Wextra -pedantic)

set(SRC_FILES
    noisereduction/Utils.cpp
    noisereduction/RealFFTf.cpp
    noisereduction/Extensions.cpp
    noisereduction/NoiseReduction.cpp
    noisereduction/InputTrack.cpp
    noisereduction/OutputTrack.cpp
    noisereduction/TrackUtils.cpp
)

find_package(Threads REQUIRED)
find_library(LIBSNDFILE_LIBRARY sndfile REQUIRED)

add_executable(noisereduction ${SRC_FILES})

target_link_libraries(noisereduction
    Threads::Threads
    ${LIBSNDFILE_LIBRARY}
)

# TODO: add test target
