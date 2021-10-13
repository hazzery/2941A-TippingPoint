#include "MoGoLift.h"

#define abs(n) (n < 0) ? -(n) : n

MoGoLift::MoGoLift(int8_t _leftPort, int8_t _rightPort, AbstractMotor::gearset _gearset, StepperPID _pid, ControllerButton *const _upButton, ControllerButton *const _downButton)
    :AbstractRobotComponent(_leftPort, _rightPort, _gearset, _pid.pid), upButton(_upButton), downButton(_downButton), stepperPID(_pid) {}

void MoGoLift::RunPID()
{
    // cout << endl << "Left: " << endl;
    first.motor.moveVoltage( pid.Calculate( first.encoder.get() ) );
    
    // cout << endl << "Right: " << endl;
    second.motor.moveVoltage( pid.Calculate( second.encoder.get() ) );
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

#define PID_INCREMENT 50

void MoGoLift::RunUserControl()
{
    if(upButton->isPressed())
    {
        lastMoveDirection = Forwards;
        stepperPID.IncrementTarget(PID_INCREMENT);
    }
    else if(downButton->isPressed())
    {
        lastMoveDirection = Backwards;
        stepperPID.IncrementTarget(-PID_INCREMENT);
    }
    else if (upButton->changedToReleased() || downButton->changedToReleased())
    {
        pid.SetTarget( sideInTheLead()->encoder.get() );
    }

    RunPID();
}

void MoGoLift::RunBangBang()
{
    if (first.encoder.get() < bangBangTarget)
        first.motor.moveVoltage(12000);
    else
        first.motor.moveVoltage(3500);

    if (second.encoder.get() < bangBangTarget)
        second.motor.moveVoltage(12000);
    else
        second.motor.moveVoltage(3500);
}

void MoGoLift::SetBangBangTarget(int16_t _target)
{
    bangBangTarget = _target;
}

double MoGoLift::distanceBetweenSides()
{
    return abs(first.encoder.get() - second.encoder.get());
}