#include "PID.h"
#include "main.h"
using std::string;

short sgn(double _n)
{
    if (_n > 0)
        return 1;
    else if (_n = 0)
        return 0;
    else
        return -1;
}

/**
 * Initialize new PID object with PID constants
 *
 * @param _kp Proportional multiplier
 * @param _ki Integral multiplier
 * @param _kd Derivative multipler
 * @param _name Name of component PID is controlling
 */
PID::PID(double _kP, double _kI, double _kD, string _name = "untitled PID")
    :Name(_name), kP(_kP), kI(_kI), kD(_kD), minOutput(-12000), maxOutput(12000), maxTime(9999), maxError(5), integralLimit(9999), minDerivative(0) {}

PID::~PID() {}

/**
 * Calculate power output for motor, given sensor value
 *
 * @param _sensorVal current value of affiliated sensor
 * 
 * @return The power for related motor
 */
double PID::Calculate(double _sensorVal)
{
    cout << endl;
    cout << "---" << Name << "---------" << endl;
    cout << "Target is: " << Target << endl;
    cout << "Sensor is: " << _sensorVal << endl;

    error = Target - _sensorVal;//Calculate error.
    
    cout << "Error is: " << error << endl;
    
    //Calculate integral (If conditions are met).
    if(abs(error) > 750)
        integral = 0;
    else if (error == 0)
        integral = 0;
    else if(abs(integral) > integralLimit)
        integral = integralLimit * sgn(integral);
    else
        integral += error;

    cout << "Integral is: " << integral << endl;
    
    derivative = error - pastError;//Calculate derivative.
    
    //Calculate PID values.
    double pOut = kP * error;
    double iOut = kI * integral;
    double dOut = kI * derivative;
    
    double output = pOut + iOut + dOut;//Calculate output.
    
    //Restrict output to max/min.
    if (output > maxOutput)
        output = maxOutput;
    else if (output < minOutput)
        output = minOutput;
    
    cout << "Outputting : " << output << "mV" << endl;
    
    //Save previous error.
    pastError = error;
    
    return output;
}

/**
 * Has the PID control finished?
 * 
 * @return true is PID is completed, flase if not
 */
bool PID::Done() 
{
    // cout << "Checking for done..." << endl;
    // if(millis() - _startTime > _maxTime)
    // {
    //     std::cout << " Done for: millis() - _startTime > _maxTime" << std::endl;
    //     return true;
    // }
    // else if(_derivative < _minDerivative)//If Robot is stuck, and unable to move (change in error was very small)
    // {
    //     std::cout << "_derivative < _minDerivative" << std::endl;
    //     return true;
    // }    
    if (abs(error) <= maxError)//If error within reasonable range
    {
        cout << "Done for: abs(_error) <= _maxError" << endl;
        return true;
    }

    else return false;
}
/**
 * Gets PID error, given sensor value
 *
 * @param sensorValue current value of affiliated sensor
 * 
 * @return The current error of the PID controler
 */
double PID::CalculateError(double _sensorVal)
{
    error = Target - _sensorVal;//Calculate error.
    
    return error;
}

/**
 * Set a new target (set point) for the PID controller
 *
 * @param target the desired finishing sensor value
 */
void PID::SetTarget(double _target)
{
    Target = _target;
    std::cout << "Target Has been set to: " << _target << std::endl;
}

/**
 * Starts the PID timer
 * This allows for done() due to timeout
 */
void PID::StartTimer()
{
    std::cout << "Timer has started" << std::endl;
    startTime = pros::millis();
}

/**
 * Reset the error, integral, and derivative terms
 * 
 * This is for when a completely new target is being set,
 * and previos values need to be cleared.
 */
void PID::ResetPID()
{
    error = maxError + 1;
    pastError = 0;
    integral = 0;
    derivative = 0;
}