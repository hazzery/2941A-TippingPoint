#pragma once

#include "MotorContainer.h"
#include "PID.h"

class AbstractRobotComponent
{
    AbstractRobotComponent(int8_t _firstMotorPort, int8_t _secondMotorPort, PID _pid);

    virtual void RunUserControl();

    virtual void RunPID();

    virtual void SetTarget(int16_t _target);
    virtual void ResetSensors();

private:
    MotorContainer first;
    MotorContainer second;

    PID pid;
};