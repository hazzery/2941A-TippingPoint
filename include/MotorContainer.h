#pragma once
#include "main.h"
#include "PID.h"

struct MotorContainer
{
    MotorContainer(int _portNumber);

    bool operator==(MotorContainer& _otherSide);

    Motor motor;
    const IntegratedEncoder encoder;
};