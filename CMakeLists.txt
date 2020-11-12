cmake_minimum_required(VERSION 3.0)

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

add_executable(noisereduction ${SRC_FILES})


# TODO: add libaries (libsndfile, pthread)

# TODO: add test target
