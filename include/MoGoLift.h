#pragma once
#include "main.h"
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

        Motor motor;
        const IntegratedEncoder encoder;
    };
    
    side left;
    side right;

    StepperPID pid;

    ControllerButton *const upButton;
    ControllerButton *const downButton;
};