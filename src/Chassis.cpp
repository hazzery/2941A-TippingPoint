#include "Chassis.h"

#define driveGearset AbstractMotor::gearset::green

DualMotorContainer Chassis::leftDrive (-15, -16, driveGearset);
DualMotorContainer Chassis::rightDrive (5, 6, driveGearset);

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

void Chassis::DriveStraight(inch_t _distance)
{
    rotating = false;
    
    straightPID.SetTarget (_distance);
    rotatePID.SetTarget((radian_t)0);
}

void Chassis::DriveStraight(inch_t _distance, millisecond_t _time)
{
    rotating = false;
    
    straightPID.SetTarget (_distance, _time);
    rotatePID.SetTarget(0_rad);
}

void Chassis::Rotate(radian_t _angle)
{
    rotating = true;

    leftDrive.ResetSensors();
    rightDrive.ResetSensors();
    
    rotatePID.SetTarget(_angle);
}

void Chassis::Tank(Controller *const _controller)
{
    leftDrive.PowerMotors (_controller->getAnalog(ControllerAnalog::leftY)  * 12_V);
    rightDrive.PowerMotors(_controller->getAnalog(ControllerAnalog::rightY) * 12_V);
}

void Chassis::Arcade(Controller *const _controller)
{
    scalar_t vertical   = _controller->getAnalog(ControllerAnalog::leftY);
    scalar_t horizontal = _controller->getAnalog(ControllerAnalog::rightX);

    leftDrive.PowerMotors( (vertical + horizontal) * 12_V);
    rightDrive.PowerMotors((vertical - horizontal) * 12_V);
}

void Chassis::RunPID()
{
    volt_t rotatePower = rotatePID.Calculate(leftDrive.GetAverageSensor() - rightDrive.GetAverageSensor());

    if(!rotating)
    {

        leftDrive.PowerMotors (straightPID.Calculate( leftDrive.GetAverageSensor()) + rotatePower * (rotatePower < 0_V ? 4 : 0));
        rightDrive.PowerMotors(straightPID.Calculate(rightDrive.GetAverageSensor()) - rotatePower * (rotatePower < 0_V ? 0 : 4));
    }
    else
    {
        leftDrive.PowerMotors(rotatePower);
        rightDrive.PowerMotors(-rotatePower);
    }
}