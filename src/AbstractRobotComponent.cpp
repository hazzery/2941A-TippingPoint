#include "AbstractRobotComponent.h"

AbstractRobotComponent::AbstractRobotComponent(int8_t _firstMotorPort, int8_t _secondMotorPort, AbstractMotor::gearset _gearset, PID _pid)
    : first(_firstMotorPort), second(_secondMotorPort), pid(_pid)
{
    first.motor.setGearing(_gearset);
    second.motor.setGearing(_gearset);
}

void AbstractRobotComponent::PowerMotors(int16_t _voltage)
{
    first.motor.moveVoltage(_voltage);
    second.motor.moveVoltage(_voltage);
}

void AbstractRobotComponent::SetTarget(int16_t _target)
{
    ResetSensors();
    pid.SetTarget(_target);
}

void AbstractRobotComponent::SetTarget(int16_t _target, uint32_t _time)
{
    ResetSensors();
    pid.SetTarget(_target, _time);
}

void AbstractRobotComponent::ResetSensors()
{
    first.encoder.reset();
    second.encoder.reset();
}

int16_t AbstractRobotComponent::CalculatePID()
{
    return pid.Calculate(first.encoder.get());
}

bool AbstractRobotComponent::IsDone()
{
    return pid.Done();
}