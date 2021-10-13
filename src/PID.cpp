#include "PID.h"
#include "main.h"
using std::string;

//#define PID_DEBUG_OUTPUT

#define sgn(_n) (_n > 0) * 1 + (_n < 0) * -1

PID::PID(float _kP, float _kI, float _kD, AbstractMotor::gearset _gearset, string _name) :
    Name(_name), kP(_kP), kI(_kI), kD(_kD), motorRPM(_gearset == AbstractMotor::gearset::green ? 200 : 400), ticksPerRev(_gearset == AbstractMotor::gearset::green ? 900 : 1800) {}

//Returns power output for specified motor, given current sensor value.
int16_t PID::Calculate(double _sensorVal)
{
    static double pOut, iOut, dOut, output, pastSensorVal, integral, derivative;
    static uint64_t lastTime, currentTime, timeDifference;

    currentTime = pros::micros();
    timeDifference = currentTime - lastTime;
    lastTime = currentTime;
    
    error = target - _sensorVal;//Calculate error.
    
    //Calculate integral (If conditions are met).
    integral += error * timeDifference;

    if( (abs(error) > motorRPM) || (error == 0) || (sgn(integral) != sgn(error)) )
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
    if (abs(output) > maxOutput)
        output = maxOutput * sgn(output);

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
    if(pros::millis() - startTime > maxTime) // If movement timed out
    {
        std::cout << "Done for: pros::millis() - startTime > maxTime" << std::endl;
        return true;
    }
    // else if(_derivative < _minDerivative)//If Robot is stuck, and unable to move (change in error was very small)
    // {
    //     std::cout << "_derivative < _minDerivative" << std::endl;
    //     return true;
    // }    
    if (abs(error) < maxCompletionError)//If error within reasonable range
    {
        cout << "Done for: abs(error) < maxCompletionError" << endl;
        return true;
    }

    else return false;
}

void PID::SetTarget_(int16_t _target, uint32_t _time)
{
    target = _target;
    std::cout << "Target Has been set to: " << _target << std::endl;

    maxTime = _time;
    startTime = pros::millis();
}

//Changes the set point for the PID controler
void PID::SetTarget_(int16_t _target)
{
    // Divide revs per minute by 60,000 to get revs per millisecond
    // So no wacky (conversion) math needs to be done later when checking
    static uint32_t ticksPerMilliSecond = (motorRPM / 60 / 1000) * ticksPerRev;
    uint32_t time = (_target * 1.5) / ticksPerMilliSecond;
    //time (in ms) = (distance * reality factor) / (ticks per second)

    if (time < 1000) // Seems like a good idea to have some saftey for small moves
        time = 1000; // I choose 1 second at random, so feel free to adjust it

    SetTarget_(_target, time);
}

//Gets the target
int16_t PID::GetTarget()
{
    return target;
}