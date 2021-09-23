#include "main.h"
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


//Integrated encoder of left front motor
IntegratedEncoder FrontLeftDriveEncoder (-15);

//Integrated encoder of right front motor
IntegratedEncoder FrontRightDriveEncoder (6);

//Integrated encoder of left back motor
IntegratedEncoder BackLeftDriveEncoder (-16);

//Integrated encoder of right back motor
IntegratedEncoder BackRightDriveEncoder (6);


//Left drive train
MotorGroup LeftDrive ({-15, -16});

//Right drive train
MotorGroup RightDrive ({5, 6});


//Front mobile goal lifter
MoGoLift FrontMoGoLift
(
    11, -1,                             // leftMotorPort, rightMotorPort
    {
        35, 1, 0,                       // kP, kI, kD
        -1750, 25, "Front Lift PID"     // minPosition, maxPosition, name
    },
    &RightUpTrigger, &RightDownTrigger  // upButton, downButton
);

//Back mobile goal lifter
MoGoLift BackMoGoLift
(
    -20, 10,                            // leftMotorPort, rightMotorPort
    {
        35, 1, 0,                       // kP, kI, kD
        -1750, 25, "Back Lift PID"      // minPosition, maxPosition, name
    },
    &LeftUpTrigger, &LeftDownTrigger    // upButton, downButton
);