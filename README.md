# Mintty

## Build with CMake

Install CMake and a C++ compiler, then run these commands from the repository
root:

```sh
cmake -S . -B build
cmake --build build
```

Run the executable with `./build/helloWorld` (or `build/Debug/helloWorld.exe`
with a multi-configuration generator on Windows).
