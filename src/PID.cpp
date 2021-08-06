#include "PID.h"
#include "main.h"
using std::string;

short sgn(double n)
{
    if (n > 0)
        return 1;
    else if (n = 0)
        return 0;
    else if (n < 0)
        return -1;
}

/**
 * Initialize new PID object with PID constants
 *
 * @param kp Proportional multiplier
 * @param ki Integral multiplier
 * @param kd Derivative multipler
 * @param name Name of component PID is controlling
 */
PID::PID(double kp, double ki, double kd, string name)
    :Name(name), _Kp(kp), _Ki(ki), _Kd(kd), _min(-12000), _max(12000), _maxTime(9999), _maxError(5), _integralLimit(9999), _minDerivative(0) {}

PID::~PID() {}

/**
 * Calculate power output for motor, given sensor value
 *
 * @param sensorVal current value of affiliated sensor
 */
double PID::calculate(double sensorVal)
{
    cout << endl;
    cout << "---" << Name << "---------" << endl;
    cout << "Target is: " << _target << endl;
    cout << "Sensor is: " << sensorVal << endl;

    _error = _target - sensorVal;//Calculate error.
    
    cout << "Error is: " << _error << endl;
    
    //Calculate integral (If conditions are met).
    if(abs(_error) > 750)
        _integral = 0;
    else if (_error == 0)
        _integral = 0;
    else if(abs(_integral) > _integralLimit)
        _integral = _integralLimit * sgn(_integral);
    else
        _integral += _error;

    cout << "Integral is: " << _integral << endl;
    
    _derivative = _error - _pastError;//Calculate derivative.
    
    //Calculate PID values.
    double pOut = _Kp * _error;
    double iOut = _Ki * _integral;
    double dOut = _Kd * _derivative;
    
    double output = pOut + iOut + dOut;//Calculate output.
    
    //Restrict output to max/min.
    if (output > _max)
        output = _max;
    else if (output < _min)
        output = _min;
    
    cout << "Outputting : " << output << "mV" << endl;
    
    
    //Save previous error.
    _pastError = _error;
    
    return output;
}

/**
 * Has the PID control finished?
 */
bool PID::done() 
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
    if (abs(_error) <= _maxError)//If error within reasonable range
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
 */
double PID::calculateError(double sensorVal)
{
    _error = _target - sensorVal;//Calculate error.
    
    return _error;
}

/**
 * Set a new target (set point) for the PID controller
 *
 * @param target the desired finishing sensor value
 */
void PID::setTarget(double target)
{
    _target = target;
    std::cout << "Target Has been set to: " << _target << std::endl;
}

/**
 * Starts the PID timer
 * This allows for done() due to timeout
 */
void PID::startTimer()
{
    std::cout << "Timer has started" << std::endl;
    _startTime = pros::millis();
}

/**
 * Reset the error, integral, and derivative terms
 * 
 * This is for when a completely new target is being set,
 * and previos values need to be cleared.
 */
void PID::resetPID()
{
    _error = _maxError + 1;
    _pastError = 0;
    _integral = 0;
    _derivative = 0;
}