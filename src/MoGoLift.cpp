#include "MoGoLift.h"

#define abs(n) (n < 0) ? -(n) : n

MoGoLift::MoGoLift
(
    int8_t _leftPort, int8_t _rightPort, AbstractMotor::gearset _gearset,
    float _kP, float _kI, float _kD, int16_t _minPosition, int16_t _maxPosition, std::string _name,
    ControllerButton *const _upButton, ControllerButton *const _downButton
)
: AbstractRobotComponent(_leftPort, _rightPort, _gearset, _kP, _kI, _kD, _name)
, minPosition(_minPosition), maxPosition(_maxPosition), upButton(_upButton), downButton(_downButton) {}

void MoGoLift::RunPID()
{
    // cout << endl << "Left: " << endl;
    first.motor.moveVoltage( Calculate( first.encoder.get() ) );
    
    // cout << endl << "Right: " << endl;
    second.motor.moveVoltage( Calculate( second.encoder.get() ) );
}

#define PID_INCREMENT 50

void MoGoLift::RunUserControl()
{
    if(upButton->isPressed())
    {
        lastMoveDirection = Forwards;
        IncrementTarget(PID_INCREMENT);
    }
    else if(downButton->isPressed())
    {
        lastMoveDirection = Backwards;
        IncrementTarget(-PID_INCREMENT);
    }
    else if (upButton->changedToReleased() || downButton->changedToReleased())
    {
        SetTarget( sideInTheLead()->encoder.get() );
    }

    RunPID();
}

void MoGoLift::IncrementTarget(const int8_t _increment)
{
    target += _increment;

    if(target < minPosition)
        target = minPosition;
    else if(target > maxPosition)
        target = maxPosition;
}

MotorContainer* MoGoLift::sideInTheLead()
{
    return (lastMoveDirection * (first.encoder.get() - second.encoder.get())) > 0 ? &first : &second;
}

bool MoGoLift::isInTheLead(MotorContainer& _side)
{
    if (first == _side)
        return (lastMoveDirection * (first.encoder.get() - second.encoder.get())) > 0;
    else
        return (lastMoveDirection * (first.encoder.get() - second.encoder.get())) < 0;
}

double MoGoLift::distanceBetweenSides()
{
    return abs(first.encoder.get() - second.encoder.get());
}