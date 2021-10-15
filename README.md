# QueryC++ 

QueryC++ is a SQL query builder library for modern C++ supporting multiple SQL dialects. 

*NOTE:* As of version 1.x.x this library is "stable" enough for usage in production with PostgreSQL database but key features still missing and these features are being added a long the way. 

## External Dependencies 

QueryC++ as a library have one external dependency which is [fmtlib](https://github.com/fmtlib/fmt). 
It is the plan to move QueryC++ to follow the C++20 standard as soon as [llvm clang++](https://clang.llvm.org/) fully support [`std::format`](https://en.cppreference.com/w/cpp/utility/format/format) and move to use `std::format` instead of `fmtlib` (although it is the same thing).

For testing we use [Google Test for C++](https://google.github.io/googletest/)



| Dependency  | Link                                 |
| :---:       | :---:                                |
| fmtlib      | https://github.com/fmtlib/fmt        |
| Google Test | https://google.github.io/googletest/ |




# Querry C++ 

Querry C++ is a library for easy SQL query building for modern C++ for multiple SQL dialects. 

*NOTE:* Version 0.0.x is considered alpha and will be subject to breaking changes

*NOTE:* This library is in no way production ready in its current state 

*NOTE:* Right now this library mainly servers as a way to get better at C++ and to build a nifty little tool for me 

## External Dependencies

Querry C++ have one external dependency which is [https://github.com/fmtlib/fmt](fmt) if you build with `CMake` this dependency will be handled by Conan. 
If you build with `make` or `waf.io` you will have to install this dependency on your system. 

# Build 

Query C++ provides `Make`, `CMake`, and `waf.io` as build system options. 

All builds are configured to compile with Clang by default, though can be configured to work with other compiles. 

## Make 

```bash
make
```

## CMake

```bash
mkdir build 
cd build
cmake ..
make 
```

## waf.io

Waf is depended on `python3` and therefore you will need to install this first before utilsing this build option. 

```bash
python waf configure 
python waf build
```

# Usage 





# License 


# Supported Data types

## Common 

### Numerical 

- NUMERICAL
- BITINT
- SMALLINT

### Strings 

- VARCHAR is fully supported. To set the length of a varchar, the first constraint must be the length.  

## PostgreSQL

### Numerical

- SERIAL
- BITSERIAL
- NUMERIC

## MariaDB / MySQL

TBW
