#pragma once
#include "main.h"
#include "PID.h"

struct MotorContainer
{
    MotorContainer(int _portNumber) : motor(_portNumber), encoder(motor) {}

    bool operator==(MotorContainer _otherSide);

    Motor motor;
    const IntegratedEncoder encoder;
};