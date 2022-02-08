#include "MoGoLift.h"
#include "Controller.h"

PID MoGoLift::pid
(
    40, 0.1, 0,
    AbstractMotor::gearset::green,
    "Mo-go lift PID"
);

MoGoLift::LiftPosition MoGoLift::target = Bottom;

Motor MoGoLift::liftMotor (-2);
Piston MoGoLift::hookPiston ('B');

void MoGoLift::SetTarget(LiftPosition _position)
{
    target = _position;
}

void MoGoLift::incrementTarget()
{
    if(target == Middle)
        target = Top;
    else if(target == Bottom)
        target = Middle;
}

void MoGoLift::decrementTarget()
{
    if(target == Top)
        target = Middle;
    else if(target == Middle)
        target = Bottom;
}

 void MoGoLift::RunUserControl()
 {
    static bool usePID = false;

     if(RightUpTrigger.isPressed())
     {
         liftMotor.moveVelocity(12000);
         usePID = false;
     }
     else if(RightDownTrigger.isPressed())
     {
         liftMotor.moveVelocity(-12000);
         usePID = false;
     }
     else if(usePID == false)
         liftMotor.moveVelocity(0);

    if(AButton.changedToPressed())
        hookPiston.Toggle();

    if(UpButton.changedToPressed())
    {
        incrementTarget();
         usePID = true;
    }
    else if(DownButton.changedToPressed())
    {
        decrementTarget();
        usePID = true;
    }

    if (usePID)
        RunPID();
 }

void MoGoLift::RunPID()
{
    pid.SetTarget(target);

    int16_t power = pid.Calculate( liftMotor.getPosition() );
    liftMotor.moveVoltage(power);
}

void MoGoLift::PrintPositions()
{
    cout << liftMotor.getPosition() << endl;
}

void MoGoLift::initMotor()
{
    liftMotor.setBrakeMode(AbstractMotor::brakeMode::hold);
}

void MoGoLift::TogglePiston()
{
    hookPiston.Toggle();
}