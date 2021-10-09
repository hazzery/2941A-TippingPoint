#include "PID.h"
#include "main.h"
using std::string;

//#define PID_DEBUG_OUTPUT

#define sgn(_n) (_n > 0) * 1 + (_n < 0) * -1

PID::PID(double _kP, double _kI, double _kD, double _errorIntegralCalculate, string _name)
    :target(0), Name(_name), kP(_kP), kI(_kI), kD(_kD), minOutput(-12000), maxOutput(12000), maxCompletionError(20), integralLimit(5000), minDerivative(0), errorIntegralCalculate(50) {}

PID::~PID() {}

//Returns power output for specified motor, given current sensor value.
double PID::Calculate(double _sensorVal)
{
    static double pOut, iOut, dOut, output, pastSensorVal, integral, derivative;
    static uint64_t lastTime, currentTime, timeDifference;

    currentTime = pros::micros();
    timeDifference = currentTime - lastTime;
    lastTime = currentTime;
    
    error = target - _sensorVal;//Calculate error.
    
    //Calculate integral (If conditions are met).
    integral += error * timeDifference;

    if( (abs(error) > errorIntegralCalculate) || (error == 0) || (sgn(integral) != sgn(error)) )
        integral = 0;
    else if(abs(integral) > integralLimit)
        integral = integralLimit * sgn(integral);
    
    derivative = (_sensorVal - pastSensorVal) / timeDifference;//Calculate derivative.
    
    //Calculate PID values.
    pOut = kP * error;
    iOut = kI * integral;
    dOut = kD * derivative;

    output = pOut + iOut - dOut;//Calculate output.
    
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

    //Save previous sensor value.
    pastSensorVal = _sensorVal;
    
    return output;
}

//Returns true if robot has successfully reached its target.
bool PID::Done() 
{
    // cout << "Checking for done..." << endl;
    if(pros::millis() - startTime > maxTime)
    {
        std::cout << " Done for: millis() - _startTime > _maxTime" << std::endl;
        return true;
    }
    // else if(_derivative < _minDerivative)//If Robot is stuck, and unable to move (change in error was very small)
    // {
    //     std::cout << "_derivative < _minDerivative" << std::endl;
    //     return true;
    // }    
    if (abs(error) <= maxCompletionError)//If error within reasonable range
    {
        cout << "Done for: abs(_error) <= _maxError" << endl;
        return true;
    }

    else return false;
}

void PID::SetTarget(double _target, uint32_t _time)
{
    target = _target;
    maxTime = _time;
    StartTimer(); // Does this need to be a function?
    std::cout << "Target Has been set to: " << _target << std::endl;
}

//Changes the set point for the PID controler
void PID::SetTarget(double _target)
{
    // Might be helpful to know the rpm of the element controlled by the PID in the constructor
    // Divide rpm by 60 to get rps
    // So no wacky (conversion) math needs to be done later when checking
    // 100 - torque
    // 200 - speed
    // 600 - turbo
    uint32_t time = (_target * 1.5) / (200 / 60); // time (in ms) = (distance * reality factor) / (revs per second)

    if (time < 1000) // Seems like a good idea to have some saftey for small moves
        time = 1000; // I choose 1 second at random, so feel free to adjust it

    SetTarget(_target, time);
}

//Sets the PID's start time.
void PID::StartTimer()
{
    std::cout << "Timer has started" << std::endl;
    startTime = pros::millis();
}

//Gets the target
int PID::GetTarget()
{
    return target;
}