#include "StepperPID.h"

/**
 * @brief Initialize new PID object with PID constants
 *
 * @param _kP Proportional multiplier
 * @param _kI Integral multiplier
 * @param _kD Derivative multipler
 * @param _minPosition Sensor value of harware at minimum position
 * @param _maxPosition Sensor value of harware at maximum position
 * @param _name Name of component PID is controlling
**/
StepperPID::StepperPID (double _kP, double _kI, double _kD, double _minPosition, double _maxPosition, std::string _name)
    :PID(_kP, _kI, _kD, 650, _name), minPosition(_minPosition), maxPosition(_maxPosition) {}

/**
 * Adds the specified value to the PID target value
 * 
 * @param _increment amount to increment target by
**/
void StepperPID::IncrementTarget(const int8_t _increment)
{
    target += _increment;

    if(target < minPosition)
        target = minPosition;
    else if(target > maxPosition)
        target = maxPosition;
}