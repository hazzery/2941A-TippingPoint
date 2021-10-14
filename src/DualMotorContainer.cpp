#include "DualMotorContainer.h"

DualMotorContainer::DualMotorContainer(int8_t _firstMotorPort, int8_t _secondMotorPort, AbstractMotor::gearset _gearset)
    : first(_firstMotorPort), second(_secondMotorPort)
{ 
    first.motor.setGearing(_gearset);
    second.motor.setGearing(_gearset);
}

void DualMotorContainer::PowerMotors(volt_t _voltage)
{
    int16_t voltage = _voltage.convert<scalar_t>();
    first.motor.moveVoltage(voltage);
    second.motor.moveVoltage(voltage);
}

inch_t DualMotorContainer::GetAverageSensor()
{
    green_revolution_t firstEncoder = (green_revolution_t)first.encoder.get();
    green_revolution_t secondEncoder = (green_revolution_t)second.encoder.get();
    degree_t avg = (firstEncoder + secondEncoder) / 2;
    return ticksToInches(avgTicks);
}

void DualMotorContainer::ResetSensors()
{
    first.encoder.reset();
    second.encoder.reset();
}