#include "MotorContainer.h"

MotorContainer::MotorContainer(int _portNumber)
    : motor(_portNumber), encoder(motor) {}

bool MotorContainer::operator==(MotorContainer& _otherSide)
{
    return (motor.getPort() == _otherSide.motor.getPort()) ? true : false;
}