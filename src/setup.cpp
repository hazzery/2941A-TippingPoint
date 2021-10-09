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


//Left half of chassis

Chassis Robot
(
    {
        -15, -16,                   // frontLeftMotorPort, backLeftMotorPort
        {
            17, 0, 0, 200,          // kP, kI, kD, errorIntegralCalculate
            "Left Drive PID"        // name
        },
        ControllerAnalog::leftY     // leftDriveControllerAxis
    },
    {
        5, 6,                       // frontRightMotorPort, backRightMotorPort
        {
            17, 0, 0, 200,          // kP, kI, kD, errorIntegralCalculate
            "Right Drive PID"       // name
        },
        ControllerAnalog::rightY    // rightDriveControllerAxis
    },
    {
        15, 0.07, 0, 50,            // kP, kI, kD, errorIntegralCalculate
        "Chassis Rotate PID"        // name
    }
);

//Front mobile goal lifter
MoGoLift FrontMoGoLift
(
    11, -1,                             // leftMotorPort, rightMotorPort
    {
        40, 0.1, 0,                       // kP, kI, kD
        // -3450, 30, "Front Lift PID"     // minPosition, maxPosition, name
        -1700, 30, "Front Lift PID"     // minPosition, maxPosition, name
    },
    &RightUpTrigger, &RightDownTrigger  // upButton, downButton
);

//Back mobile goal lifter
MoGoLift BackMoGoLift
(
    -20, 10,                            // leftMotorPort, rightMotorPort
    {
        40, 0.1, 0,                       // kP, kI, kD
        // -3450, 30, "Back Lift PID"      // minPosition, maxPosition, name
        -1700, 30, "Back Lift PID"      // minPosition, maxPosition, name
    },
    &LeftUpTrigger, &LeftDownTrigger    // upButton, downButton
);