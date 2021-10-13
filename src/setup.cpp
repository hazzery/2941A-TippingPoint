#include "main.h"
#include "Chassis.h"
#include "MoGoLift.h"

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

#define liftKP 40
#define liftKI 0.1
#define liftKD 0
#define liftMin -1700
#define liftMax 30
#define liftGearset AbstractMotor::gearset::green

//Front mobile goal lifter
MoGoLift FrontMoGoLift
(
    11, -1, liftGearset,                // leftMotorPort, rightMotorPort
    liftKP, liftKI, liftKD,             // kP, kI, kD
    liftMin, liftMax,                   // minPosition, maxPosition
    "Front Lift PID",                   // PIDname
    &RightUpTrigger, &RightDownTrigger  // upButton, downButton
);

//Back mobile goal lifter
MoGoLift BackMoGoLift
(
    -20, 10, liftGearset,               // leftMotorPort, rightMotorPort
    liftKP, liftKI, liftKD,             // kP, kI, kD
    liftMin, liftMax,                   //minPosition, maxPosition
    "Back Lift PID",                    // PIDname
    &LeftUpTrigger, &LeftDownTrigger    // upButton, downButton
);