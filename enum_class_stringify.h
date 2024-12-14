// MIT License
//
// Copyright (c) 2024 Peter Major <majorpeter29@gmail.com>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//
// Repository: https://github.com/majorpeter/enum_class_stringify

#pragma once

#include <string_view>
#include <string>
#include <array>

constexpr std::string_view _enumClassSplitStringView(const char *text, int index)
{
    while (index > 0)
    {
        while (*text && *text != ',')
        {
            text++;
        }
        if (*text == ',')
        {
            text += 2;
        }
        index--;
    }

    const char *end = text + 1;
    while (*end && *end != ',')
    {
        end++;
    }
    return {text, static_cast<size_t>(end - text)};
}

consteval int _enumClassCountFields(const char *text)
{
    int count = 1;
    while (*text != '\0')
    {
        if (*text == ',')
        {
            count++;
        }
        text++;
    }
    return count;
}

template <class T, int count>
consteval auto _enumClassConstructStrArray(const char *text)
{
    std::array<std::string_view, count> v;
    for (int i = 0; i < count; i++)
    {
        v[static_cast<int>(i)] = _enumClassSplitStringView(text, i);
    }
    return v;
}

#define ENUM_CLASS(name, ...)                                                                                                   \
    enum class name                                                                                                             \
    {                                                                                                                           \
        __VA_ARGS__                                                                                                             \
    };                                                                                                                          \
    static constexpr auto name##Strings = _enumClassConstructStrArray<name, _enumClassCountFields(#__VA_ARGS__)>(#__VA_ARGS__); \
    static constexpr std::string_view enumToString(const name v) { return name##Strings.at(static_cast<size_t>(v)); }           \
    static std::string enumToStringScoped(const name v)                                                                         \
    {                                                                                                                           \
        auto result = std::string{#name "::"};                                                                                  \
        result.append(enumToString(v));                                                                                         \
        return result;                                                                                                          \
    }                                                                                                                           \
    static constexpr std::string_view name##ToString(const name v) { return name##Strings.at(static_cast<size_t>(v)); }         \
    static name name##FromString(const std::string &s)                                                                          \
    {                                                                                                                           \
        for (auto i = 0; i < name##Strings.size(); i++)                                                                         \
        {                                                                                                                       \
            if (s.compare(name##Strings.at(i)) == 0)                                                                            \
            {                                                                                                                   \
                return static_cast<name>(i);                                                                                    \
            }                                                                                                                   \
        }                                                                                                                       \
                                                                                                                                \
        std::__throw_invalid_argument("argument not in " #name " values");                                                      \
        /* not actually reached because of throw, but needed to silence 'control reaches end of non-void function */            \
        return static_cast<name>(0);                                                                                            \
    }
