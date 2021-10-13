#include "AbstractRobotComponent.h"
template <typename pidType>
AbstractRobotComponent<pidType>::AbstractRobotComponent(int8_t _firstMotorPort, int8_t _secondMotorPort, AbstractMotor::gearset _gearset, pidType _pid)
    : first(_firstMotorPort), second(_secondMotorPort), pid(_pid)
{
    first.motor.setGearing(_gearset);
    second.motor.setGearing(_gearset);
}

template <typename pidType>
void AbstractRobotComponent<pidType>::PowerMotors(int16_t _voltage)
{
    first.motor.moveVoltage(_voltage);
    second.motor.moveVoltage(_voltage);
}

template <typename pidType>
void AbstractRobotComponent<pidType>::SetTarget(int16_t _target)
{
    ResetSensors();
    pid.SetTarget(_target);
}

template <typename pidType>
void AbstractRobotComponent<pidType>::SetTarget(int16_t _target, uint32_t _time)
{
    ResetSensors();
    pid.SetTarget(_target, _time);
}

template <typename pidType>
void AbstractRobotComponent<pidType>::ResetSensors()
{
    first.encoder.reset();
    second.encoder.reset();
}

template <typename pidType>
int16_t AbstractRobotComponent<pidType>::CalculatePID()
{
    return pid.Calculate(first.encoder.get());
}

template <typename pidType>
bool AbstractRobotComponent<pidType>::IsDone()
{
    return pid.Done();
}