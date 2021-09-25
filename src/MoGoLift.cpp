#include "MoGoLift.h"

#define abs(n) (n < 0) ? -n : n

bool MoGoLift::side::operator==(side _otherSide)
{
    return (motor.getPort() == _otherSide.motor.getPort()) ? true : false;
}

MoGoLift::MoGoLift(int8_t _leftPort, int8_t _rightPort, StepperPID _pid, ControllerButton *const _upButton, ControllerButton *const _downButton)
    : left(_leftPort), right(_rightPort), pid(_pid), upButton(_upButton), downButton(_downButton)
{
    left.motor.setGearing(AbstractMotor::gearset::red);
    right.motor.setGearing(AbstractMotor::gearset::red);
}

MoGoLift::side* MoGoLift::sideInTheLead()
{
    return (lastMoveDirection * (left.encoder.get() - right.encoder.get())) > 0 ? &left : &right;
}

bool MoGoLift::isInTheLead(const side& _side)
{
    if (left == _side)
        return (lastMoveDirection * (left.encoder.get() - right.encoder.get())) > 0;
    else
        return (lastMoveDirection * (left.encoder.get() - right.encoder.get())) < 0;
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


    cout << endl << "Left: " << endl;
    left.motor.moveVoltage( pid.Calculate( left.encoder.get() ) );

    cout << endl << "Right: " << endl;
    right.motor.moveVoltage( pid.Calculate( right.encoder.get() ) );
}

short MoGoLift::error()
{
    return abs(left.encoder.get() - right.encoder.get());
}