#pragma once
#include "PID.h"

class StepperPID : public PID
{
public:
    StepperPID (double _kP, double _kI, double _kD, double _minPosition, double _maxPosition, std::string _name);

    //Increase the target by some value
    void IncrementTarget(const int8_t _increment);

    using PID::Calculate;
    using PID::CalculateError;
    using PID::Done;
    using PID::GetTarget;
    using PID::SetTarget;
    using PID::StartTimer;

private:
    const double minPosition;
    const double maxPosition;
};