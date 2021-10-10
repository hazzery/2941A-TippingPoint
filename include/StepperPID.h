#pragma once
#include "PID.h"

class StepperPID : public PID
{
public:
    /**
     * @brief Initialize new PID object with PID constants
     *
     * @param _kP Proportional multiplier
     * @param _kI Integral multiplier
     * @param _kD Derivative multipler
     * @param _minPosition Sensor value of harware at minimum position
     * @param _maxPosition Sensor value of harware at maximum position
     * @param _gearset The AbstractMotor::gearset inside the motor this is controlling
     * @param _name Name of component PID is controlling
    **/
    StepperPID (double _kP, double _kI, double _kD, double _minPosition, double _maxPosition, AbstractMotor::gearset _gearset, std::string _name);

    /**
     * @brief Increments PID target position by specified ammount.
     * 
     * @param _increment The amount to increment target by, can be positive or negative
    **/
    void IncrementTarget(const int8_t _increment);

    using PID::Calculate;
    using PID::Done;
    using PID::GetTarget;
    using PID::SetTarget;

private:
    const double minPosition;
    const double maxPosition;
};