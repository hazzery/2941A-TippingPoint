#pragma once
#include "main.h"
#include "StepperPID.h"

class MoGoLift
{
public:
    MoGoLift(uint8_t leftPort, uint8_t rightPort, StepperPID _pid, ControllerButton *const _upButton, ControllerButton *const _downButton);

    void RunUserControl();

private:
    struct side
    {
        side(int _portNumber) : motor(_portNumber), encoder(_portNumber) {}

        Motor motor;
        const IntegratedEncoder encoder;
    };
    
    side left;
    side right;

    StepperPID pid;

    ControllerButton *const upButton;
    ControllerButton *const downButton;
};