#include "main.h"
#include "Chassis.h"
#include "MoGoLift.h"
#include "StepperPID.h"

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

//Front mobile goal lifter
MoGoLift FrontMoGoLift
(
    11, -1,                             // leftMotorPort, rightMotorPort
    AbstractMotor::gearset::green,      // okapi::AbstractMotor::gearset
    &RightUpTrigger, &RightDownTrigger  // upButton, downButton
);

//Back mobile goal lifter
MoGoLift BackMoGoLift
(
    -20, 10,                            // leftMotorPort, rightMotorPort
    AbstractMotor::gearset::green,      // okapi::AbstractMotor::gearset
    &LeftUpTrigger, &LeftDownTrigger    // upButton, downButton
);