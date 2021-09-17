#include "main.h"

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



//Integrated encoder for left motor of front mo-go lift
IntegratedEncoder FrontLeftLiftEncoder (11);

//Integrated encoder for right motor of front mo-go lift
IntegratedEncoder FrontRightLiftEncoder (1, true);

//Integrated encoder for left motor of back mo-go lift
IntegratedEncoder BackLeftLiftEncoder (20);

//Integrated encoder for right motor of back mo-go lift
IntegratedEncoder BackRightLiftEncoder (10, true);


//Left motor
Motor FrontLeftLiftMotor ({11, false, AbstractMotor::gearset::red, AbstractMotor::encoderUnits::degrees});

//Individual mobile goal lifter motors
Motor FrontRightLiftMotor ({1, true, AbstractMotor::gearset::red, AbstractMotor::encoderUnits::degrees});

//
Motor BackLeftLiftMotor ({20, false, AbstractMotor::gearset::red, AbstractMotor::encoderUnits::degrees});

//
Motor BackRightLiftMotor ({10, true, AbstractMotor::gearset::red, AbstractMotor::encoderUnits::degrees});


//Left drive train
MotorGroup LeftDrive ({-15, -16});

//Right drive train
MotorGroup RightDrive ({5, 6});

//Mobile goal lifter
MotorGroup FrontMoGoLift ({FrontLeftLiftMotor, FrontRightLiftMotor});
MotorGroup BackMoGoLift ({BackLeftLiftMotor, BackRightLiftMotor});
