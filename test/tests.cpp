#include "../enum_class_stringify.h"
#include "gtest/gtest.h"

ENUM_CLASS(Numbers, Zero, One, Two, Three)
ENUM_CLASS(OneValueOnly, Value)

namespace test_namesp
{
    ENUM_CLASS(enumeration, off, on);
} // namespace test_namesp

TEST(enum_class_stringify, happy_path)
{
    EXPECT_STREQ(std::string{enumToString(Numbers::Zero)}.c_str(), "Zero");
    EXPECT_STREQ(std::string{enumToString(Numbers::One)}.c_str(), "One");
    EXPECT_STREQ(std::string{enumToString(Numbers::Two)}.c_str(), "Two");
    EXPECT_STREQ(std::string{enumToString(Numbers::Three)}.c_str(), "Three");
}

TEST(enum_class_stringify, one_value_only)
{
    EXPECT_STREQ(std::string{enumToString(OneValueOnly::Value)}.c_str(), "Value");
}

TEST(enum_class_stringify, out_of_bounds_throws)
{
    static constexpr auto count = NumbersStrings.size();
    EXPECT_THROW(enumToString(static_cast<Numbers>(count)), std::out_of_range);
    EXPECT_THROW(enumToString(static_cast<Numbers>(-1)), std::out_of_range);
}

TEST(enum_class_stringify, namespace)
{
    EXPECT_STREQ(std::string{enumToString(test_namesp::enumeration::off)}.c_str(), "off");
    EXPECT_STREQ(std::string{enumToString(test_namesp::enumeration::on)}.c_str(), "on");
}
