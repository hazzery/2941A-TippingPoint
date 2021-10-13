#include "MotorContainer.h"

MotorContainer::MotorContainer(int8_t _portNumber)
    : motor(_portNumber), encoder(motor) {}

bool MotorContainer::operator==(MotorContainer& _otherSide)
{
    return (motor.getPort() == _otherSide.motor.getPort()) ? true : false;
}

DualMotorContainer::DualMotorContainer(int8_t _first, int8_t _second)
    : first(_first), second(_second) {}