=============
Query C++
=============

Query C++ is a library for easy SQL query building for modern C++ for multiple SQL dialects.

**NOTE:** This library is not in a production ready state

=============
License
=============

Query C++ is licensed under the BSD v3 license, for more information see the LICENSE file.  

=============
Setup And Build
=============

If you want to build Query C++ from source, we provide three different options for this; 1) `cmake` 2) `make`, and 3) `waf.io`.
In the following we will explain how to setup and build using the three methods. 

-------------
External dependencies
-------------

Query C++ dependes on `fmt` (https://github.com/fmtlib/fmt).
If you use `cmake` and Conan this dependency is handled for you.

If you use `waf` or `make` it is not handled for you and you must install it manually, in the current setup.

For test we depend on `gtest` (https://github.com/google/googletest) for both CMake and Waf this dependency is automactically handled.
For `make` you will need to handle this depedency. 

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

After this you can build the system by executing

    python waf build 

=============
Documentation
=============

*NOTE:* Documentation is still a work in progress. But we believe in documentation and aim to fully document Query C++

API Documentation can be generate by run `make documentation` or `python waf documentation`.
The documentation will be generate in the folder `build/docs`.

In addition to API documentation a manual can be found here: https://github.com/looopTools/querycpp-docs

=============
Examples
=============

Examples will be added to this project later

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


=============
Supported by
=============  

This project has recieved support from Aarhus Univeristy Centre for Digitalisation, Big Data, and Data Analytics `(DIGIT) <https://digit.au.dk/>`_.
