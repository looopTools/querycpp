=============
Query C++
=============

Query C++ is a library for easy SQL query building for modern C++ for multiple SQL dialects.

**NOTE:** This library is not in a production ready state

=============
Setup And Build
=============

-------------
External dependencies
-------------

Query C++ dependes on fmt (https://github.com/fmtlib/fmt).
If you use CMake and Conan this dependency is handled for you.

If you use `waf` or `cmake` it is not handled for you and you must install it manually, in the current setup. 


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
