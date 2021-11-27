#include "MoGoLift.h"

#define abs(n) (n < 0) ? -(n) : n

PID MoGoLift::pid
(
    40, 0.1, 0,
    AbstractMotor::gearset::green,
    "Mo-go lift PID"
);

MoGoLift::MoGoLift(int8_t _leftPort, int8_t _rightPort, AbstractMotor::gearset _gearset, ControllerButton *const _upButton, ControllerButton *const _downButton)
    :DualMotorContainer(_leftPort, _rightPort, _gearset), upButton(_upButton), downButton(_downButton) {}

void MoGoLift::SetTarget(int16_t _position)
{
    target = _position;
}

void MoGoLift::incrementTarget(int8_t _increment)
{
    target += _increment;

    if(target < minPosition)
        target = minPosition;
    else if(target > maxPosition)
        target = maxPosition;
}

#define PID_INCREMENT 50

void MoGoLift::RunUserControl()
{
    if(upButton->isPressed())
    {
        lastMoveDirection = Forwards;
        incrementTarget(PID_INCREMENT);
    }
    else if(downButton->isPressed())
    {
        lastMoveDirection = Backwards;
        incrementTarget(-PID_INCREMENT);
    }
    else if (upButton->changedToReleased() || downButton->changedToReleased())
    {
        pid.SetTarget( sideInTheLead()->encoder.get() );
    }

    RunPID();
}

void MoGoLift::PrintPositions()
{
    cout << "Left: " << first.encoder.get() << "  Right: " << second.encoder.get() << endl;
}

void MoGoLift::RunPID()
{   
    pid.SetTarget(target);
    
    // cout << endl << "Left ";
    int leftPower = pid.Calculate( first.encoder.get() );
    first.motor.moveVoltage( leftPower < 2000 ? 0 : leftPower );
    
    // cout << endl << "Right ";
    int rightPower = pid.Calculate( second.encoder.get() );
    second.motor.moveVoltage( rightPower < 2000 ? 0 : rightPower );
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