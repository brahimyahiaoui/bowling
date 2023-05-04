# How to build

First, extract the Google Test archive in-place (directly in 3rdparty/gtest), so that a googletest-master/ folder is available. You need to have a structure like the following:
```
<project root>/
  3rdparty/
    gtest/
      googletest-master/
        googlemock/
          ...
        googletest/
          ...
  include/
    ...
  src/
    ...
  ...
```

To build this project, you will need CMake. To download it, head to https://cmake.org/download/#latest. Under Linux, you can most likely download it from your package manager.

Once you have installed it, the following commands should suffice to create a compilable project; execute them from the project's root directory:
```bash
mkdir build && cd build
cmake ..
cmake --build .
```

This will by default generate under Windows a Visual Studio solution (if installed), or under Linux a Makefile project.

To run the tests, simply launch the produced executable:
```bash
# Under Windows with Visual Studio:
Debug\BowlingKata_Tests.exe

# Under Linux:
./BowlingKata_Tests
```
