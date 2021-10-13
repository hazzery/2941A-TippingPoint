#include "Chassis.h"

#define driveKP 17
#define driveKI 0
#define driveKD 0
#define driveGearset AbstractMotor::gearset::green

bool Chassis::rotating = false;

DriveTrain Chassis::leftDrive
(
    -15, -16,                       // frontLeftMotorPort, backLeftMotorPort
    driveGearset,
    {
        driveKP, driveKI, driveKD,  // kP, kI, kD
        driveGearset,               // AbstractMotor::gearset   
        "Left Drive PID"            // PIDname
    }
);

DriveTrain Chassis::rightDrive
(
    5, 6,                           // frontRightMotorPort, backRightMotorPort
    driveGearset,
    {
        driveKP, driveKI, driveKD,  // kP, kI, kD
        driveGearset,               // AbstractMotor::gearset
        "Right Drive PID"           // PIDname
    }
);

PID Chassis::rotatePID
(
    15, 0.07, 0,            // kP, kI, kD
    driveGearset,           // AbstractMotor::gearset
    "Chassis Rotate PID"    // PIDname
);

void Chassis::DriveStraight(int16_t _distance)
{
    rotating = false;
    
    leftDrive.SetTarget(_distance);
    rightDrive.SetTarget(_distance);

    rotatePID.SetTarget_(0);
}

void Chassis::DriveStraight(int16_t _distance, uint32_t _time)
{
    rotating = false;
    
    leftDrive.SetTarget (_distance, _time);
    rightDrive.SetTarget(_distance, _time);

    rotatePID.SetTarget_(0);
}

void Chassis::Rotate(int16_t _angle)
{
    rotating = true;
    leftDrive.ResetSensors();
    rightDrive.ResetSensors();
    
    rotatePID.SetTarget_(_angle);
}

void Chassis::RunPID()
{
    double rotatePower = rotatePID.Calculate(leftDrive.GetAverageSensor() - rightDrive.GetAverageSensor());

    if(!rotating)
    {

        leftDrive.PowerMotors (leftDrive.CalculatePID()  + rotatePower * (rotatePower < 0 ? 4 : 0) );
        rightDrive.PowerMotors(rightDrive.CalculatePID() - rotatePower * (rotatePower < 0 ? 0 : 4) );
    }
    else
    {
        leftDrive.PowerMotors(rotatePower);
        rightDrive.PowerMotors(-rotatePower);
    }
}

void Chassis::Tank(Controller *const _controller)
{
    leftDrive.PowerMotors (_controller->getAnalog(ControllerAnalog::leftY)  * 12000);
    rightDrive.PowerMotors(_controller->getAnalog(ControllerAnalog::rightY) * 12000);
}

void Chassis::Arcade(Controller *const _controller)
{
    float vertical   = _controller->getAnalog(ControllerAnalog::leftY);
    float horizontal = _controller->getAnalog(ControllerAnalog::rightX);

    leftDrive.PowerMotors( (vertical + horizontal) * 12000);
    rightDrive.PowerMotors((vertical - horizontal) * 12000);
}