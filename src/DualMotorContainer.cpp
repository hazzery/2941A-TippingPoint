#include "DualMotorContainer.h"

DualMotorContainer::DualMotorContainer(int8_t _firstMotorPort, int8_t _secondMotorPort, AbstractMotor::gearset _gearset)
    : first(_firstMotorPort), second(_secondMotorPort)
{
    first.motor.setGearing(_gearset);
    second.motor.setGearing(_gearset);
}

void DualMotorContainer::PowerMotors(int16_t _voltage)
{
    first.motor.moveVoltage(_voltage);
    second.motor.moveVoltage(_voltage);
}

double DualMotorContainer::GetAverageSensor()
{
    return ( first.encoder.get() + second.encoder.get()) / 2;
}

void DualMotorContainer::ResetSensors()
{
    first.encoder.reset();
    second.encoder.reset();
}