=============
Query C++
=============

Query C++ is a library for easy SQL query building for modern C++ for multiple SQL dialects.

**NOTE:** This library is not in a production ready state

=============
Setup And Build
=============

If you want to build Query C++ from source, we provide three different options for this; 1) CMake, 2) Make, and 3) waf.io.
In the following we will explain how to setup and build using the three methods. 

-------------
External dependencies
-------------

Query C++ dependes on fmt (https://github.com/fmtlib/fmt).
If you use CMake and Conan this dependency is handled for you.

If you use `waf` or `cmake` it is not handled for you and you must install it manually, in the current setup.

-------------
CMake
-------------

**TBW**

-------------
Make
-------------

**TBW**

-------------
waf.io
-------------

To utilise waf.io for building you will ned to install python3+.
Change working directory to the Query C++ and we can start.
First you will need to configure the project:


    python waf configure



=============
Suported Data Types
=============

In this section we list all data types supported.
In the header ``include/database_data_type.hpp`` you will find the string literal definition of the data types supported. 

-----------
Common
-----------

Data types shown in this section is shared between at least two different data base systems

Numerical
===========

- ``NUMBER``
- ``SMALLINT``
- ``BIGINT``

String 
===========  

- ``VARCHAR``

-----------
PostgreSQL
-----------

Numerical
===========

- ``SMALLSERIAL``
- ``SERIAL``
- ``BIGSERIAL``
- ``NUMERIC``
- ``INTEGER``
- ``DECIMAL``
- ``REAL``
- ``DOUBLE PRECISION``
