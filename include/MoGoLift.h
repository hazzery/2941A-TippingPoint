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
    void RunPID();

    void RunBangBang();     //DO NOT USE WITH RunUserControl() simultaneously
    void SetBangBangTarget(int _target);

private:
    
    StepperPID pid;

    MotorContainer left;
    MotorContainer right;

    MotorContainer *sideInTheLead();
    bool isInTheLead(MotorContainer& _side);

    Direction lastMoveDirection;

    short error();

    ControllerButton *const upButton;
    ControllerButton *const downButton;

    int bangBangTarget;
};