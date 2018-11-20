# PySpoT<img align="right" alt="PySpoT" width="300" height="300" src="https://upload.wikimedia.org/wikipedia/commons/thumb/9/95/PEO-snake_alt.svg/2000px-PEO-snake_alt.svg.png" />

PySpoT is a Python scripting library, developed as a module for [SunSpoT](https://github.com/Fahien/sunspot).

Please visit the [wiki](https://github.com/Fahien/pyspot/wiki) for more information.

## Prerequisites

In order to build PySpoT, you will need the following dependencies:
- [CMake](https://cmake.org), Cross-Platform Make;
- [Python 3.6.+](https://www.python.org/downloads/), header files and a static library;
- [Pywrap](), tool you can find as a release artifact.

## Build

Generate a project for your platform with cmake.
```bash
cmake -H. -Bbuild
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

The MIT License © 2017 [Antonio Caggiano](http://www.fahien.me)
