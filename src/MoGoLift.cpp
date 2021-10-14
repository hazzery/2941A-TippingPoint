#include "MoGoLift.h"

#define abs(n) (n < 0) ? -(n) : n

StepperPID MoGoLift::pid
(
    40, 0.1, 0,    -1700, 30,
    AbstractMotor::gearset::green,
    "Mo-go lift PID"
);

MoGoLift::MoGoLift(int8_t _leftPort, int8_t _rightPort, AbstractMotor::gearset _gearset, ControllerButton *const _upButton, ControllerButton *const _downButton)
    :left(_leftPort), right(_rightPort), upButton(_upButton), downButton(_downButton)
{
    left.setGearing(_gearset);
    right.setGearing(_gearset);
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
        pid.SetTarget( sideInTheLead()->getPosition() );
    }

    RunPID();
}

void MoGoLift::RunPID()
{
    // cout << endl << "Left ";
    left.moveVoltage( pid.Calculate( left.getPosition() ) );
    
    // cout << endl << "Right ";
    right.moveVoltage( pid.Calculate( right.getPosition() ) );
}

Motor* MoGoLift::sideInTheLead()
{
    return (lastMoveDirection * (left.getPosition() - right.getPosition())) > 0 ? &left : &right;
}

double MoGoLift::distanceBetweenSides()
{
    return abs(left.getPosition() - right.getPosition());
}