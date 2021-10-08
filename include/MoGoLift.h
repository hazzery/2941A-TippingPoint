#pragma once
#include "main.h"
#include "Direction.h"
#include "StepperPID.h"
#include "MotorContainer.h"

class MoGoLift
{
public:
    MoGoLift(int8_t _leftPort, int8_t _rightPort, StepperPID _pid, ControllerButton *const _upButton, ControllerButton *const _downButton);

    void RunUserControl();

private:
    
    StepperPID pid;

    MotorContainer left;
    MotorContainer right;

    MotorContainer *sideInTheLead();
    bool isInTheLead(const MotorContainer& _side);

    Direction lastMoveDirection;

    short error();

    ControllerButton *const upButton;
    ControllerButton *const downButton;
};