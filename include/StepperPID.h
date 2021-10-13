#pragma once
#include "PID.h"

class StepperPID
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
    StepperPID (float _kP, float _kI, float _kD, int16_t _minPosition, int16_t _maxPosition, AbstractMotor::gearset _gearset, std::string _name);

    /**
     * @brief Increments PID target position by specified ammount.
     * 
     * @param _increment The amount to increment target by, can be positive or negative
    **/
    void IncrementTarget(const int8_t _increment);

    PID pid;
private:
    const int16_t minPosition;
    const int16_t maxPosition;

};