#include "../enum_class_stringify.h"
#include "gtest/gtest.h"

ENUM_CLASS_STR(Numbers, Zero, One, Two, Three)
ENUM_CLASS_STR(OneValueOnly, Value)

namespace test_namesp
{
    ENUM_CLASS_STR(enumeration, off, on)
} // namespace test_namesp

TEST(enum_class_stringify, happy_path)
{
    EXPECT_STREQ(std::string{enumToString(Numbers::Zero)}.c_str(), "Zero");
    EXPECT_STREQ(std::string{enumToString(Numbers::One)}.c_str(), "One");
    EXPECT_STREQ(std::string{enumToString(Numbers::Two)}.c_str(), "Two");
    EXPECT_STREQ(std::string{enumToString(Numbers::Three)}.c_str(), "Three");

    EXPECT_STREQ(std::string{NumbersToString(Numbers::Zero)}.c_str(), "Zero");
    EXPECT_STREQ(std::string{NumbersToString(Numbers::One)}.c_str(), "One");
    EXPECT_STREQ(std::string{NumbersToString(Numbers::Two)}.c_str(), "Two");
    EXPECT_STREQ(std::string{NumbersToString(Numbers::Three)}.c_str(), "Three");
}

TEST(enum_class_stringify, one_value_only)
{
    EXPECT_STREQ(std::string{enumToString(OneValueOnly::Value)}.c_str(), "Value");
    EXPECT_STREQ(std::string{OneValueOnlyToString(OneValueOnly::Value)}.c_str(), "Value");
}

TEST(enum_class_stringify, out_of_bounds_throws)
{
    static constexpr auto count = NumbersStrings.size();
    EXPECT_NO_THROW(enumToString(static_cast<Numbers>(0)));
    EXPECT_THROW(enumToString(static_cast<Numbers>(count)), std::out_of_range);
    EXPECT_THROW(enumToString(static_cast<Numbers>(-1)), std::out_of_range);
    EXPECT_THROW(NumbersToString(static_cast<Numbers>(-1)), std::out_of_range);
}

TEST(enum_class_stringify, namespace)
{
    EXPECT_STREQ(std::string{enumToString(test_namesp::enumeration::off)}.c_str(), "off");
    EXPECT_STREQ(std::string{enumToString(test_namesp::enumeration::on)}.c_str(), "on");

    EXPECT_STREQ(std::string{test_namesp::enumToString(test_namesp::enumeration::off)}.c_str(), "off");
    EXPECT_STREQ(std::string{test_namesp::enumToString(test_namesp::enumeration::on)}.c_str(), "on");

    EXPECT_STREQ(std::string{test_namesp::enumerationToString(test_namesp::enumeration::off)}.c_str(), "off");
    EXPECT_STREQ(std::string{test_namesp::enumerationToString(test_namesp::enumeration::on)}.c_str(), "on");
}

TEST(enum_class_stringify, enumFromStr)
{
    EXPECT_EQ(NumbersFromString("Zero"), Numbers::Zero);
    EXPECT_EQ(NumbersFromString("One"), Numbers::One);
    EXPECT_EQ(NumbersFromString("Two"), Numbers::Two);
    EXPECT_EQ(NumbersFromString("Three"), Numbers::Three);
}

TEST(enum_class_stringify, enumFromStr_namesp)
{
    EXPECT_EQ(test_namesp::enumerationFromString("off"), test_namesp::enumeration::off);
    EXPECT_EQ(test_namesp::enumerationFromString("on"), test_namesp::enumeration::on);
}

TEST(enum_class_stringify, invalid_argument_throws)
{
    EXPECT_NO_THROW(NumbersFromString("Zero"));
    EXPECT_NO_THROW(NumbersFromString("One"));
    EXPECT_NO_THROW(NumbersFromString("Two"));
    EXPECT_NO_THROW(NumbersFromString("Three"));
    EXPECT_THROW(NumbersFromString("OtherString"), std::invalid_argument);
}
