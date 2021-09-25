#pragma once
#include "main.h"
#include "Direction.h"
#include "StepperPID.h"

class MoGoLift
{
public:
    MoGoLift(int8_t leftPort, int8_t rightPort, StepperPID _pid, ControllerButton *const _upButton, ControllerButton *const _downButton);

    void RunUserControl();

private:
    struct side
    {
        side(int _portNumber) : motor(_portNumber), encoder(motor) {}

        bool operator==(side _otherSide);

        Motor motor;
        const IntegratedEncoder encoder;
    };
    
    StepperPID pid;

    side left;
    side right;

    side *sideInTheLead();
    bool isInTheLead(const side& _side);

    Direction lastMoveDirection;

    short error();

    ControllerButton *const upButton;
    ControllerButton *const downButton;
};