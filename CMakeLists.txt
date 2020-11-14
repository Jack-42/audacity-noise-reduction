cmake_minimum_required(VERSION 3.0)

set(CMAKE_C_COMPILER clang)
set(CMAKE_CXX_COMPILER clang++)

project(AudacityNoiseReduction VERSION 1.0.0)

add_compile_options(-std=c++11 -Wall -Wextra -pedantic)

# create core library
set(SRC_FILES
    noisereduction/Utils.cpp
    noisereduction/RealFFTf.cpp
    noisereduction/Extensions.cpp
    noisereduction/NoiseReduction.cpp
    noisereduction/InputTrack.cpp
    noisereduction/OutputTrack.cpp
    noisereduction/TrackUtils.cpp
)

add_library(noisereduction_core STATIC ${SRC_FILES})

find_package(Threads REQUIRED)
find_library(LIBSNDFILE_LIBRARY sndfile REQUIRED)
find_library(DL_LIBRARY dl REQUIRED)

target_link_libraries(noisereduction_core
    PUBLIC
    Threads::Threads
    ${LIBSNDFILE_LIBRARY}
    ${DL_LIBRARY}
)

# create driver executable, link the core library
add_executable(noisereduction_driver
    noisereduction/main.cpp
)
target_link_libraries(noisereduction_driver PRIVATE noisereduction_core)

# create test executable, link the core library
add_executable(test_runner
    noisereduction/tests/test_main.cpp
    noisereduction/tests/test_audacity.cpp
    noisereduction/tests/test_mmap_snd.cpp
)
target_link_libraries(test_runner PRIVATE noisereduction_core)
