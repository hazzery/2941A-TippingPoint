#include "Chassis.h"

#define driveGearset AbstractMotor::gearset::green

MotorGroup Chassis::leftDrive ({-15, -16});
MotorGroup Chassis::rightDrive ({5, 6});

PID Chassis::rotatePID
(
    15, 0.07, 0,            // kP, kI, kD
    driveGearset,           // AbstractMotor::gearset
    "Chassis Rotate PID"    // PIDname
);

PID Chassis::straightPID
(
    17, 0.1, 0,            // kP, kI, kD
    driveGearset,           // AbstractMotor::gearset
    "Chassis Straight PID"    // PIDname
);

bool Chassis::rotating = false;

void Chassis::DriveStraight(int16_t _distance)
{
    rotating = false;
    
    straightPID.SetTarget (_distance);
    rotatePID.SetTarget(0);
}

void Chassis::DriveStraight(int16_t _distance, uint32_t _time)
{
    rotating = false;
    
    straightPID.SetTarget (_distance, _time);
    rotatePID.SetTarget(0);
}

void Chassis::Rotate(int16_t _angle)
{
    rotating = true;

    leftDrive.tarePosition();
    rightDrive.tarePosition();
    
    rotatePID.SetTarget(_angle);
}

void Chassis::Tank(Controller *const _controller)
{
    leftDrive.moveVoltage (_controller->getAnalog(ControllerAnalog::leftY)  * 12000);
    rightDrive.moveVoltage(_controller->getAnalog(ControllerAnalog::rightY) * 12000);
}

void Chassis::Arcade(Controller *const _controller)
{
    float vertical   = _controller->getAnalog(ControllerAnalog::leftY);
    float horizontal = _controller->getAnalog(ControllerAnalog::rightX);

    leftDrive.moveVoltage( (vertical + horizontal) * 12000);
    rightDrive.moveVoltage((vertical - horizontal) * 12000);
}

void Chassis::RunPID()
{
    double rotatePower = rotatePID.Calculate(leftDrive.getPosition() - rightDrive.getPosition());

    if(!rotating)
    {

        leftDrive.moveVoltage (straightPID.Calculate( leftDrive.getPosition()) + rotatePower * (rotatePower < 0 ? 4 : 0) );
        rightDrive.moveVoltage(straightPID.Calculate(rightDrive.getPosition()) - rotatePower * (rotatePower < 0 ? 0 : 4) );
    }
    else
    {
        leftDrive.moveVoltage(rotatePower);
        rightDrive.moveVoltage(-rotatePower);
    }
}