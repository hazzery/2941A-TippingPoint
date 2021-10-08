#include "main.h"
#include "MoGoLift.h"
#include "StepperPID.h"
#include "DriveTrain.h"

//The Vex V5 robot controller
Controller controller;


//Up button (↑)
ControllerButton UpButton (ControllerDigital::up);

//Down button (↓)
ControllerButton DownButton (ControllerDigital::down);

//Left button (←)
ControllerButton LeftButton (ControllerDigital::left);

//Right button (→)
ControllerButton RightButton (ControllerDigital::right);

//Button (A)
ControllerButton AButton (ControllerDigital::A);

//Button (B)
ControllerButton BButton (ControllerDigital::B);

//Button (X)
ControllerButton XButton (ControllerDigital::X);

//Button (Y)
ControllerButton YButton (ControllerDigital::Y);

//Top left trigger (L1)
ControllerButton LeftUpTrigger (ControllerDigital::L1);

//Bottom left trigger (L2)
ControllerButton LeftDownTrigger (ControllerDigital::L2);

//Top right trigger (R1)
ControllerButton RightUpTrigger (ControllerDigital::R1);

//Bottom right trigger (R2)
ControllerButton RightDownTrigger (ControllerDigital::R2);


//Left half of chassis
DriveTrain LeftDriveTrain
(
    -15, -16,
    {
        10, 0, 0,
        "Left Drive PID"
    },
    ControllerAnalog::leftY
);

//Right half of chassis
DriveTrain RightDriveTrain
(
    5, 6,
    {
        10, 0, 0,
        "Right Drive PID"
    },
    ControllerAnalog::rightY
);


//Front mobile goal lifter
MoGoLift FrontMoGoLift
(
    11, -1,                             // leftMotorPort, rightMotorPort
    {
        40, 1, 0,                       // kP, kI, kD
        -3450, 30, "Front Lift PID"     // minPosition, maxPosition, name
    },
    &RightUpTrigger, &RightDownTrigger  // upButton, downButton
);

//Back mobile goal lifter
MoGoLift BackMoGoLift
(
    -20, 10,                            // leftMotorPort, rightMotorPort
    {
        40, 1, 0,                       // kP, kI, kD
        -3450, 30, "Back Lift PID"      // minPosition, maxPosition, name
    },
    &LeftUpTrigger, &LeftDownTrigger    // upButton, downButton
);