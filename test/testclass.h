#pragma once

#include "../enum_class_stringify.h"

class TestClass
{
public:
    ENUM_CLASS(State, Initial, Running, Waiting, Error);
    TestClass(State initialState = State::Initial);
    std::string getState() const;

private:
    State state;
};
