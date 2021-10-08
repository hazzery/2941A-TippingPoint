#include "MoGoLift.h"

#define abs(n) (n < 0) ? -n : n

MoGoLift::MoGoLift(int8_t _leftPort, int8_t _rightPort, StepperPID _pid, ControllerButton *const _upButton, ControllerButton *const _downButton)
    : left(_leftPort), right(_rightPort), pid(_pid), upButton(_upButton), downButton(_downButton)
{
    left.motor.setGearing(AbstractMotor::gearset::red);
    right.motor.setGearing(AbstractMotor::gearset::red);
}

MotorContainer* MoGoLift::sideInTheLead()
{
    return (lastMoveDirection * (left.encoder.get() - right.encoder.get())) > 0 ? &left : &right;
}

bool MoGoLift::isInTheLead(MotorContainer& _side)
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

    RunPID();
}

void MoGoLift::RunPID()
{
    cout << endl << "Left: " << endl;
    left.motor.moveVoltage( pid.Calculate( left.encoder.get() ) );
    
    cout << endl << "Right: " << endl;
    left.motor.moveVoltage( pid.Calculate( left.encoder.get() ) );
}

void MoGoLift::RunBangBang()
{
    if (left.encoder.get() < bangBangTarget)
        left.motor.moveVoltage(12000);
    else
        left.motor.moveVoltage(3500);

    if (right.encoder.get() < bangBangTarget)
        right.motor.moveVoltage(12000);
    else
        right.motor.moveVoltage(3500);
}

void MoGoLift::SetBangBangTarget(int _target)
{
    bangBangTarget = _target;
}

short MoGoLift::error()
{
    return abs(left.encoder.get() - right.encoder.get());
}