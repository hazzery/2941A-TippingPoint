#include "PID.h"
#include "main.h"
using std::string;

#define PID_DEBUG_OUTPUT

short sgn(double _n)
{
    if (_n > 0)
        return 1;
    else if (_n = 0)
        return 0;
    else
        return -1;
}

PID::PID(double _kP, double _kI, double _kD, string _name)
    :Name(_name), kP(_kP), kI(_kI), kD(_kD), minOutput(-12000), maxOutput(12000), maxTime(9999), maxError(5), integralLimit(9999), minDerivative(0) {}

PID::~PID() {}

//Returns power output for specified motor, given current sensor value.
double PID::Calculate(double _sensorVal)
{
    error = target - _sensorVal;//Calculate error.
    
    //Calculate integral (If conditions are met).
    if(abs(error) > 650)
        integral = 0;
    else if (error == 0)
        integral = 0;
    else if(abs(integral) > integralLimit)
        integral = integralLimit * sgn(integral);
    else
        integral += error;

    
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

#ifdef PID_DEBUG_OUTPUT
    cout << endl;
    cout << "---" << Name << "---------" << endl;
    cout << "Target is: " << target << endl;
    cout << "Sensor is: " << _sensorVal << endl;
    cout << "Error is: " << error << endl;
    cout << "Integral is: " << integral << endl;
    cout << "Outputting : " << output << "mV" << endl;
#endif

    //Save previous error.
    pastError = error;
    
    return output;
}

//Returns true if robot has successfully reached its target.
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

//Returns PID error, given current sensor value value.
double PID::CalculateError(double _sensorVal)
{
    error = target - _sensorVal;//Calculate error.
    
    return error;
}

//Changes the set point for the PID controler
void PID::SetTarget(double _target)
{
    target = _target;
    std::cout << "Target Has been set to: " << _target << std::endl;
}

//Sets the PID's start time.
void PID::StartTimer()
{
    std::cout << "Timer has started" << std::endl;
    startTime = pros::millis();
}

//Resets the private variables
void PID::ResetPID()
{
    error = maxError + 1;
    pastError = 0;
    integral = 0;
    derivative = 0;
}

//Gets the target
int PID::GetTarget()
{
    return target;
}