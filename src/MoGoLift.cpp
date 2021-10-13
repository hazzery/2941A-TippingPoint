#include "MoGoLift.h"

#define abs(n) (n < 0) ? -(n) : n

StepperPID MoGoLift::pid
(
    40, 0.1, 0,    -1700, 30,
    AbstractMotor::gearset::green,
    "Mo-go lift PID"
);

MoGoLift::MoGoLift(int8_t _leftPort, int8_t _rightPort, AbstractMotor::gearset _gearset, ControllerButton *const _upButton, ControllerButton *const _downButton)
    :DualMotorContainer(_leftPort, _rightPort, _gearset), upButton(_upButton), downButton(_downButton) {}

void MoGoLift::RunPID()
{
    // cout << endl << "Left: " << endl;
    first.motor.moveVoltage( pid.Calculate( first.encoder.get() ) );
    
    // cout << endl << "Right: " << endl;
    second.motor.moveVoltage( pid.Calculate( second.encoder.get() ) );
}

void MoGoLift::SetTarget(int16_t _position)
{
    pid.SetTarget (_position);
}

#define PID_INCREMENT 50

void MoGoLift::RunUserControl()
{
    if(upButton->isPressed())
    {
        lastMoveDirection = Forwards;
        pid.IncrementTarget(PID_INCREMENT);
    }
    else if(downButton->isPressed())
    {
        lastMoveDirection = Backwards;
        pid.IncrementTarget(-PID_INCREMENT);
    }
    else if (upButton->changedToReleased() || downButton->changedToReleased())
    {
        pid.SetTarget( sideInTheLead()->encoder.get() );
    }

    RunPID();
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