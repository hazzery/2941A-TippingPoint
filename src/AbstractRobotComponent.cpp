#include "AbstractRobotComponent.h"

AbstractRobotComponent::AbstractRobotComponent(int8_t _firstMotorPort, int8_t _secondMotorPort, AbstractMotor::gearset _gearset, float _kP, float _kI, float _kD, std::string _name)
    : PID(_kP, _kI, _kD, _gearset, _name), first(_firstMotorPort), second(_secondMotorPort)
{
    first.motor.setGearing(_gearset);
    second.motor.setGearing(_gearset);
}

void AbstractRobotComponent::PowerMotors(int16_t _voltage)
{
    first.motor.moveVoltage(_voltage);
    second.motor.moveVoltage(_voltage);
}

void AbstractRobotComponent::ResetSensors()
{
    first.encoder.reset();
    second.encoder.reset();
}

int16_t AbstractRobotComponent::CalculatePID()
{
    return Calculate(first.encoder.get());
}