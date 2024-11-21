#include "testclass.h"
#include "gtest/gtest.h"

TestClass::TestClass(State initialState) : state(initialState)
{
}

std::string TestClass::getState() const
{
    return std::string{enumToString(state)};
}

TEST(test_class, default_ctor_param)
{
    TestClass tc;
    EXPECT_STREQ(tc.getState().c_str(), std::string{TestClass::enumToString(TestClass::State::Initial)}.c_str());
}

TEST(test_class, custom_ctor_param)
{
    TestClass tc(TestClass::State::Running);
    EXPECT_STREQ(tc.getState().c_str(), std::string{TestClass::enumToString(TestClass::State::Running)}.c_str());
}
