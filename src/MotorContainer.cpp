#include "MotorContainer.h"

MotorContainer::MotorContainer(int8_t _portNumber)
    : motor(_portNumber), encoder(motor) {}

bool MotorContainer::operator==(MotorContainer& _otherSide) const
{
    return (motor.getPort() == _otherSide.motor.getPort());
}