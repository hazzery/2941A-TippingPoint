#include "StepperPID.h"

StepperPID::StepperPID (double _kP, double _kI, double _kD, double _minPosition, double _maxPosition, AbstractMotor::gearset _gearset, std::string _name)
    :PID(_kP, _kI, _kD, _gearset, _name), minPosition(_minPosition), maxPosition(_maxPosition) {}

void StepperPID::IncrementTarget(const int8_t _increment)
{
    target += _increment;

    if(target < minPosition)
        target = minPosition;
    else if(target > maxPosition)
        target = maxPosition;
}