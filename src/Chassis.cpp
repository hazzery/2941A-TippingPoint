#include "Chassis.h"

Chassis::Chassis(DriveTrain _leftDrive, DriveTrain _rightDrive, PID _rotatePID)
    :leftDrive(_leftDrive), rightDrive(_rightDrive), rotatePID(_rotatePID) {}

void Chassis::DriveStraight(int _distance)
{
    rotating = false;
    
    leftDrive.SetTarget(_distance);
    rightDrive.SetTarget(_distance);

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