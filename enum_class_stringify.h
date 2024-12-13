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
