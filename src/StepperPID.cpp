#include "StepperPID.h"

StepperPID::StepperPID (float _kP, float _kI, float _kD, int16_t _minPosition, int16_t _maxPosition, AbstractMotor::gearset _gearset, std::string _name)
    :PID(_kP, _kI, _kD, _gearset, _name), minPosition(_minPosition), maxPosition(_maxPosition) {}

void StepperPID::IncrementTarget(const int8_t _increment)
{
    target += _increment;

    if(target < minPosition)
        target = minPosition;
    else if(target > maxPosition)
        target = maxPosition;
}