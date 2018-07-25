[![Build Status](https://travis-ci.org/niXman/yas.svg?branch=master)](https://travis-ci.org/niXman/yas) [![Build status](https://ci.appveyor.com/api/projects/status/55v27uvryu0qh8mc/branch/master?svg=true)](https://ci.appveyor.com/project/niXman/yas/branch/master)

# YAS
Yet Another Serialization

-![Time](https://github.com/thekvs/cpp-serializers/raw/master/images/time.png)

* YAS is created as a replacement of [boost.serialization](https://www.boost.org/doc/libs/1_67_0/libs/serialization/doc/index.html) because of its insufficient speed of serialization
* YAS is header only library
* YAS does not depend on third-party libraries or boost
* YAS require C++11 support
* YAS binary archives is endian independent

## Supported the following types of archives:
 - binary
 - text
 - json (not fully comply)

## Supported the following compilers:
 - GCC  : 4.8.5, ... - 32/64 bit
 - MinGW: 4.8.5, ... - 32/64 bit
 - Clang: 3.5, ... - 32/64 bit
 - Intel: (untested)
 - MSVC : 2017(in c++14 mode), ... - 32/64 bit

## Samples
The easiest way to save and load some object or vars is to use the `yas::save()` and `yas::load()` functions like this:
```cpp
#include <yas/serialize.hpp>
#include <yas/std_types.hpp>

int main() {
    int a = 3, aa{};
    short b = 4, bb{};
    float c = 3.14, cc{};
    
    constexpr std::size_t flags = 
         yas::mem // IO type
        |yas::json; // IO format
    
    auto buf = yas::save<flags>(
        YAS_OBJECT(nullptr, a, b, c)
    );
    
    // buf = {"a":3,"b":4,"c":3.14}
    
    yas::load<flags>(buf,
        YAS_OBJECT_NVP(nullptr
            ,("a", aa)
            ,("b", bb)
            ,("c", cc)
        )
    );
    // a == aa && b == bb && c == cc;
}
```
The IO type can be one of `yas::mem` or `yas::file`.
The IO format can be one of `yas::binary` or `yas::text` or `yas::json`.

The `YAS_OBJECT()`/`YAS_OBJECT_NVP()`/`YAS_OBJECT_STRUCT()`/`YAS_OBJECT_STRUCT_NVP()` macro are declared [here](https://github.com/niXman/yas/blob/master/include/yas/object.hpp), example use is [here](https://github.com/niXman/yas/blob/master/tests/base/include/yas_object.hpp).

More examples you can see [here](https://github.com/niXman/yas/blob/master/tests/base/include/serialize.hpp).

## TODO:
* YASOBJ (the new structured text archive format)
* limits
* message versioning

## Serialization for the following types is supported:
 - [std::array](http://en.cppreference.com/w/cpp/container/array)
 - [std::bitset](http://en.cppreference.com/w/cpp/utility/bitset)
 - [std::chrono::duration](http://en.cppreference.com/w/cpp/chrono/duration)
 - [std::chrono::time_point](http://en.cppreference.com/w/cpp/chrono/time_point)
 - [std::complex](http://en.cppreference.com/w/cpp/numeric/complex)
 - [std::deque](http://en.cppreference.com/w/cpp/container/deque)
 - [std::forward_list](http://en.cppreference.com/w/cpp/container/forward_list)
 - [std::list](http://en.cppreference.com/w/cpp/container/list)
 - [std::map](http://en.cppreference.com/w/cpp/container/map)
 - [std::multimap](http://en.cppreference.com/w/cpp/container/multimap)
 - [std::multiset](http://en.cppreference.com/w/cpp/container/multiset)
 - [std::optional](http://en.cppreference.com/w/cpp/utility/optional)
 - [std::pair](http://en.cppreference.com/w/cpp/utility/pair)
 - [std::set](http://en.cppreference.com/w/cpp/container/set)
 - [std::string](http://en.cppreference.com/w/cpp/string/basic_string)
 - [std::tuple](http://en.cppreference.com/w/cpp/utility/tuple)
 - [std::unordered_map](http://en.cppreference.com/w/cpp/container/unordered_map)
 - [std::unordered_multimap](http://en.cppreference.com/w/cpp/container/unordered_multimap)
 - [std::unordered_multiset](http://en.cppreference.com/w/cpp/container/unordered_multiset)
 - [std::unordered_set](http://en.cppreference.com/w/cpp/container/unordered_set)
 - [std::vector](http://en.cppreference.com/w/cpp/container/vector)
 - [std::wstring](http://en.cppreference.com/w/cpp/string/basic_string)
 - [boost::array](http://www.boost.org/doc/libs/1_64_0/doc/html/array.html)
 - [boost::chrono::duration](http://www.boost.org/doc/libs/1_64_0/doc/html/chrono/reference.html#chrono.reference.cpp0x.duration_hpp.duration)
 - [boost::chrono::time_point](http://www.boost.org/doc/libs/1_64_0/doc/html/chrono/reference.html#chrono.reference.cpp0x.time_point_hpp.time_point)
 - [boost::optional](http://www.boost.org/doc/libs/1_64_0/libs/optional/doc/html/index.html)
 - [boost::variant](http://www.boost.org/doc/libs/1_64_0/doc/html/variant.html)
 - [boost::container::deque](http://www.boost.org/doc/libs/1_64_0/doc/html/boost/container/deque.html)
 - [boost::container::string](http://www.boost.org/doc/libs/1_64_0/doc/html/boost/container/basic_string.html)
 - [boost::container::wstring](http://www.boost.org/doc/libs/1_64_0/doc/html/boost/container/basic_string.html)
 - [boost::container::vector](http://www.boost.org/doc/libs/1_64_0/doc/html/boost/container/vector.html)
 - [boost::container::static_vector](http://www.boost.org/doc/libs/1_64_0/doc/html/boost/container/static_vector.html)
 - [boost::container::stable_vector](http://www.boost.org/doc/libs/1_64_0/doc/html/boost/container/stable_vector.html)
 - [boost::container::list](http://www.boost.org/doc/libs/1_64_0/doc/html/boost/container/list.html)
 - [boost::container::slist](http://www.boost.org/doc/libs/1_64_0/doc/html/boost/container/slist.html)
 - [boost::container::map](http://www.boost.org/doc/libs/1_64_0/doc/html/boost/container/map.html)
 - [boost::container::multimap](http://www.boost.org/doc/libs/1_64_0/doc/html/boost/container/multimap.html)
 - [boost::container::set](http://www.boost.org/doc/libs/1_64_0/doc/html/boost/container/set.html)
 - [boost::container::multiset](http://www.boost.org/doc/libs/1_64_0/doc/html/boost/container/multiset.html)
 - [boost::container::flat_map](http://www.boost.org/doc/libs/1_64_0/doc/html/boost/container/flat_map.html)
 - [boost::container::flat_multimap](http://www.boost.org/doc/libs/1_64_0/doc/html/boost/container/flat_multimap.html)
 - [boost::container::flat_set](http://www.boost.org/doc/libs/1_64_0/doc/html/boost/container/flat_set.html)
 - [boost::container::flat_multiset](http://www.boost.org/doc/libs/1_64_0/doc/html/boost/container/flat_multiset.html)
 - [boost::unordered_map](http://www.boost.org/doc/libs/1_64_0/doc/html/boost/unordered_map.html)
 - [boost::unordered_multimap](http://www.boost.org/doc/libs/1_64_0/doc/html/boost/unordered_multimap.html)
 - [boost::unordered_set](http://www.boost.org/doc/libs/1_64_0/doc/html/boost/unordered_set.html)
 - [boost::unordered_multiset](http://www.boost.org/doc/libs/1_64_0/doc/html/boost/unordered_multiset.html)
 - [boost::fusion::pair](http://www.boost.org/doc/libs/1_64_0/libs/fusion/doc/html/fusion/support/pair.html)
 - [boost::fusion::tuple](http://www.boost.org/doc/libs/1_64_0/libs/fusion/doc/html/fusion/container/tuple.html)
 - [boost::fusion::vector](http://www.boost.org/doc/libs/1_64_0/libs/fusion/doc/html/fusion/container/vector.html)
 - [boost::fusion::list](http://www.boost.org/doc/libs/1_64_0/libs/fusion/doc/html/fusion/container/list.html)
 - [boost::fusion::map](http://www.boost.org/doc/libs/1_64_0/libs/fusion/doc/html/fusion/container/map.html)
 - [boost::fusion::set](http://www.boost.org/doc/libs/1_64_0/libs/fusion/doc/html/fusion/container/set.html)
 - [yas::intrusive_buffer](https://github.com/niXman/yas/blob/master/include/yas/buffers.hpp#L48) (only save)
 - [yas::shared_buffer](https://github.com/niXman/yas/blob/master/include/yas/buffers.hpp#L67)

## Projects using this library
* [K3](https://github.com/DaMSL/K3): K3 is a programming language for building large-scale data systems
* [cppan](https://github.com/tarasko/cppan): Class members annotations for C++
* [iris-crypt](https://github.com/aspectron/iris-crypt): Store Node.js modules encrypted in a package file
* [GeekSys company](http://www.geeksysgroup.com/en/): GeekSys is using YAS to serialize features from images
