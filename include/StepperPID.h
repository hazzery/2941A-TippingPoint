#pragma once
#include "PID.h"

class StepperPID : public PID
{
public:
    StepperPID (double _kP, double _kI, double _kD, double _minPosition, double _maxPosition, std::string _name);

    /**
     * @brief Increments PID target position by specified ammount.
     * 
     * @param _increment The amount to increment target by, can be positive or negative
    **/
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