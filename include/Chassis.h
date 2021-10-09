#pragma once
#include "DriveTrain.h"

class Chassis
{
public:
    Chassis(DriveTrain _leftDrive, DriveTrain _rightDrive, PID _rotatePID);

    void DriveStraight(int _distance);
    void DriveStraight(int _distance, unsigned int _time);

    void Rotate(int _distance);
    void Rotate(int _distance, unsigned int _time);

    void Tank(Controller *const _controller);

    void RunPID();

private:
    DriveTrain leftDrive;
    DriveTrain rightDrive;

    bool rotating = false;

    PID rotatePID;
};