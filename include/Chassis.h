#pragma once
#include "DriveTrain.h"

class Chassis
{
public:
    static void DriveStraight(int16_t _distance);
    
    static void DriveStraight(int16_t _distance, uint32_t _time);

    static void Rotate(int16_t _angle);

    static void Rotate(int16_t _angle, uint32_t _time);

    static void Tank(Controller *const _controller);

    static void Arcade(Controller *const _controller);

    static void RunPID();

private:
    static DriveTrain leftDrive;
    static DriveTrain rightDrive;
    static bool rotating;
    static PID rotatePID;
};