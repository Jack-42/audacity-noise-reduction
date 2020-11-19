cmake_minimum_required(VERSION 3.1)

# TODO: dirty, is ignored on Windows anyway, uses MSCV with default generator (which is Visual Studio)
set(CMAKE_C_COMPILER clang)
set(CMAKE_CXX_COMPILER clang++)

project(AudacityNoiseReduction VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_EXTENSIONS OFF) # disable compiler-specific extensions

################################################################################
# Create core library
set(CORE_SRC_FILES
    noisereduction/Utils.cpp
    noisereduction/RealFFTf.cpp
    noisereduction/Extensions.cpp
    noisereduction/NoiseReduction.cpp
    noisereduction/InputTrack.cpp
    noisereduction/OutputTrack.cpp
    noisereduction/TrackUtils.cpp
)

add_library(noisereduction_core STATIC ${CORE_SRC_FILES})

find_package(Threads REQUIRED)
find_library(LIBSNDFILE_LIBRARY sndfile REQUIRED
	# need this name to find it on Windows
	NAMES libsndfile-1
	# default installation path on windows, cannot find it without path
	HINTS "C:\\Program Files\\Mega-Nerd\\libsndfile\\lib"
)
# TODO: find fix for Windows
#find_library(DL_LIBRARY dl REQUIRED)

set(CORE_LIBRARIES
    Threads::Threads
    ${LIBSNDFILE_LIBRARY}
    #${DL_LIBRARY}
)

# must add include dir on Windows
if(WIN32)
	target_include_directories(noisereduction_core PUBLIC "C:\\Program Files\\Mega-Nerd\\libsndfile\\include")
endif()

target_link_libraries(noisereduction_core PUBLIC ${CORE_LIBRARIES})

################################################################################
# Create driver executable
add_executable(noisereduction_driver noisereduction/main.cpp)

target_link_libraries(noisereduction_driver PRIVATE noisereduction_core)

################################################################################
# Create test executable
set(TEST_SRC_FILES
    noisereduction/tests/test_main.cpp
    noisereduction/tests/test_audacity.cpp
    noisereduction/tests/test_mmap_snd.cpp
)

add_executable(test_runner ${TEST_SRC_FILES})

target_link_libraries(test_runner PRIVATE noisereduction_core)
