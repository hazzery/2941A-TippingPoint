#include "Chassis.h"

#define driveKP 17
#define driveKI 0
#define driveKD 0
#define calculate_error_integral 200

bool Chassis::rotating = false;

DriveTrain Chassis::leftDrive
(
    -15, -16,    // frontLeftMotorPort, backLeftMotorPort
    {
        driveKP, driveKI, driveKD,
        calculate_error_integral,          
        "Left Drive PID"
    },
    ControllerAnalog::leftY    // leftDriveControllerAxis
);

DriveTrain Chassis::rightDrive
(
    5, 6,    // frontRightMotorPort, backRightMotorPort
    {
        driveKP, driveKI, driveKD,
        calculate_error_integral,
        "Right Drive PID"
    },
    ControllerAnalog::rightY    // rightDriveControllerAxis
);

PID Chassis::rotatePID
(
    15, 0.07, 0, 50,            // kP, kI, kD, errorIntegralCalculate
    "Chassis Rotate PID"        // name
);

void Chassis::DriveStraight(int _distance)
{
    rotating = false;
    
    leftDrive.SetTarget(_distance);
    rightDrive.SetTarget(_distance);

    rotatePID.SetTarget(0);
}

void Chassis::DriveStraight(int _distance, unsigned int _time)
{
    rotating = false;
    
    leftDrive.SetTarget(_distance, _time);
    rightDrive.SetTarget(_distance, _time);

    rotatePID.SetTarget(0);
}

void Chassis::Rotate(int _angle)
{
    rotating = true;
    leftDrive.ResetSensors();
    rightDrive.ResetSensors();
    
    rotatePID.SetTarget(_angle);
}

void Chassis::RunPID()
{
    double rotatePower = rotatePID.Calculate(leftDrive.GetAverageSensor() - rightDrive.GetAverageSensor());


    if(!rotating)
    {
        leftDrive.Move(leftDrive.RunPID() + rotatePower * 2);
        rightDrive.Move(rightDrive.RunPID() - rotatePower * 2);
    }
    else
    {
        leftDrive.Move(rotatePower);
        rightDrive.Move(-rotatePower);
    }
}

void Chassis::Tank(Controller *const _controller)
{
    leftDrive.RunUserControl(_controller);
    rightDrive.RunUserControl(_controller);
}