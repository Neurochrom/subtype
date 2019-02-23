# Subtype - a simple stronger typing lib for C++

C++ has a quiet strong type system. However, originally numerical types were differentiated by how they represent the
numerical value. So if we have int, unsigned int, float, and so on. What we often want though, is for the type system
to describe actual utility. For example if you have two integers, one being the index of a table, and another being
a counter you might want them to be a different type, so that compiler prevents you from mixing them up accidentally.

One solution would be to use the excellent Boost.Units. However that library is quiet heavy and designed well
for physical units where dimensional analysis might come in handy. 

Subtype is a header only super simple library that allows you to very easily define new (sub)types. A subtype
is similar to a typedef and behaves the same way as the underlying type, but there is no automatic conversion to other
subtypes built on to top of the same base type or even to the base type itself.

Of course it all only matters in compile time - there should be no run-time penalty with any modern compiler.

## Usage

The simplest way to define a subtype is by using the SUBTYPE_FULL_DEF marco:

```C++
#include "subtype/Subtype.hpp"

// Define a new type called PubIndex based on an int
SUBTYPE_FULL_DEF(int, PubIndex);
// Define another type called PrivIndex also based on an int
SUBTYPE_FULL_DEF(int, PrivIndex);
```

You can later use the defined subtypes

```C++
PubIndex pub = 0;
PubIndex pub2 = 10;
PrivIndex priv = 7;

// This will not compile:
// pub = priv;

// This is fine
pub = pub2;
```

If you want to have ostream << operators for your subtypes please include SubtypeStream.hpp.

For more guidance please see ```test.cpp``` and the library headers themselves.

## Additional code

The assertnc.hpp header contains macros for testing something will not compile based on the SFINAE C++ trick.
See ```test.cpp``` for example usage.

## Building

Just include Subtype.hpp and optionally SubtypeStream.hpp headers in your project.
A sample is provided in test.cpp.

To build the sample on unixish systems:

```bash
clang++ -std=c++1z -O3 test.cpp -Wall -o builds/subtypeTest.out
```

You can use g++ instead of clang++ if you so choose.

A MSVS project to build the sample is provided under the ```winBuild``` directory.

## Contributing

Just submit a pull request on gitlab or github

https://gitlab.com/Neurochrom/subtype

https://github.com/Neurochrom/subtype

## License

This library is **licensed under the (permissive) [MIT](https://opensource.org/licenses/MIT) license**.

Copyright (c) 2015-2019 Paweł Cichocki

Enjoy ;)
