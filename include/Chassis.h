#pragma once
#include "DriveTrain.h"

class Chassis
{
public:
    static void DriveStraight(int _distance);
    static void DriveStraight(int _distance, unsigned int _time);

    static void Rotate(int _distance);
    static void Rotate(int _distance, unsigned int _time);

    static void Tank(Controller *const _controller);
    static void RunPID();

private:
    static DriveTrain leftDrive;
    static DriveTrain rightDrive;
    static bool rotating;
    static PID rotatePID;

};