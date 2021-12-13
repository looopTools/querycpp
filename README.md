# Query C++ 

Query C++ is a library for easy construction of SQL queries for C++ for various SQL dialects. 
The purpose of Query C++ is to remove the need of having raw SQL strings in your code but have it as functions calls.
It is important for us to note that Query C++ is not an ORM and is not intended as such. 

Query C++ has been considered production ready since version 1.1.0 all though only simple queries are support and more complex query options will be added a long the way. 

## License 

Query C++ is open source under the BSD v3 license, for more information see the LICENSE file.

## Dependencies and Build

### External Dependencies

Querry C++ have one external dependency which is [https://github.com/fmtlib/fmt](fmt) if you build with `CMake` this dependency will be handled by Conan. 
If you build with `make` or `waf.io` you will have to install this dependency on your system. 

### Build 

Query C++ provides `Make`, `CMake`, and `waf.io` as build system options. 

All builds are configured to compile with Clang by default, though can be configured to work with other compiles. 

#### Make 

```bash
make
```

#### CMake

```bash
mkdir build 
cd build
cmake ..
make 
```

#### waf.io

Waf is depended on `python3` and therefore you will need to install this first before utilsing this build option. 

```bash
python waf configure 
python waf build
```
