# enum_class_stringify

[![tests](https://github.com/majorpeter/enum_class_stringify/actions/workflows/cmake-build-and-test.yml/badge.svg)](https://github.com/majorpeter/enum_class_stringify/actions/workflows/cmake-build-and-test.yml)
![GitHub License](https://img.shields.io/github/license/majorpeter/enum_class_stringify)

A header-only library to automatically stringify `enum class` values in **C++20**.

## Why

Error messages and logs are a lot more useful if values of _enum_'s - such as internal states and error responses - are human readable instead of numeric. Especially if those numeric values are subject to change between versions of the software. Have you ever had to debug an error _0x8000ffff_ on Windows?...

Higher level languages such as `C#` and `Java` support converting `enum` values to strings for printing but this _overhead_ has never been allowed in C++.

It used to be possible to build arrays of key-value pairs with macros in earlier C++ standards but with `costexpr` and `consteval` in C++20, it's possible to put the magic of enum class stringification in a single macro.

## Usage

Definition of a stringifiable `enum class` (sadly this still needs a macro):

```cpp
ENUM_CLASS_STR(TypeName, Value1, Value2, Value3)

// yields the following declaration (& creates the ToString/FromString functions)
enum class TypeName { Value1, Value2, Value3 };
```

Stringify:

```cpp
enumToString(TypeName::Value1)
// or
TypeNameToString(TypeName::Value1)
// yields a std::string_view with the content of "Value1"


enumToStringScoped(TypeName::Value1)
// yields a std::string_view with the content of "TypeName::Value1"
```

Enum value from string:

```cpp
TypeNameFromString("Value1")
// yields TypeName::Value1
```

The `ENUM_CLASS_STR` macro may be used in the global scope, inside namespaces or classes (or both). It defines the `enum class` as expected and also puts the `enumToString`, `<TypeName>ToString`, `<TypeName>FromString` functions in the same scope:

```cpp
class MyClass
{
    //...
public:
    ENUM_CLASS_STR(MyState, Initial, Pending, Accepted, Rejected)
    //...
};

void myPrint()
{
    std::cout << MyClass::enumToString(MyClass::MyState::Pending) << std::endl;

    std::string s;
    std::cin >> s;
    try {
        const MyClass::MyState state = MyClass::MyStateFromString(s);
        // ...
    } catch (std::invalid_argument& e) {
        // user input may be invalid, always handle
        //...
    }
}
```

### Exceptions

`enumToString` (`<name>ToString`) uses a compile-time created `std::array` to collect the compile-time created `std::string_view`'s. Thus indexing out of this array will throw a `std::out_of_range` exception. This may happen due to incorrect casting or the variable getting by a memory safety issue corrupted etc.

`<name>FromString` tries to find the matching value in the same `std::array`, if it isn't found, the function throws a `std::invalid_argument` exception, make sure to catch this exception when working with user inputs.

## Running tests

```sh
cmake -B build && (cd build/ ; make all && ./runUnitTests )
```
