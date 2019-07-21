# Pyspot<img align="right" alt="Pyspot" width="300" height="300" src="https://upload.wikimedia.org/wikipedia/commons/thumb/9/95/PEO-snake_alt.svg/2000px-PEO-snake_alt.svg.png" />

Pyspot is a Python scripting library, developed as a module for [SunSpot](https://github.com/Fahien/sunspot).

Please visit the [wiki](https://github.com/Fahien/pyspot/wiki) for more information.

## Prerequisites

In order to build Pyspot, you will need the following dependencies:
- [CMake](https://cmake.org), Cross-Platform Make;
- [Python 3.7.+](https://www.python.org/downloads/), header files and a static library;
- [Pywrap](https://github.com/Fahien/pywrap), Clang tool you can clone and build to automatically generate Python bindings (remember to add its directory to system *path*).

## Build

Generate a project for your platform with cmake.
```bash
cmake -H. -Bbuild -DCMAKE_BUILD_TYPE=Release
```

Compile it.
```bash
cmake --build build --config Release
```

If you want, you can run the tests.
```bash
cd build
ctest -C Release -T test
```

## License

The MIT License © 2017-2019 [Antonio Caggiano](https://www.fahien.me)
