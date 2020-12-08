mkdir build
cd build
cmake ..
cmake --build . --target test_runner
cd ..\samples
..\build\Debug\test_runner.exe
PAUSE
