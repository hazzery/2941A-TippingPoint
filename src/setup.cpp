#include "main.h"

//The Vex V5 robot controller
Controller controller;


//Up button (↑)
ControllerButton upBtn (ControllerDigital::up);

//Down button (↓)
ControllerButton downBtn (ControllerDigital::down);

//Left button (←)
ControllerButton leftBtn (ControllerDigital::left);

//Right button (→)
ControllerButton rightBtn (ControllerDigital::right);

//Button (A)
ControllerButton ABtn (ControllerDigital::A);

//Button (B)
ControllerButton BBtn (ControllerDigital::B);

//Button (X)
ControllerButton XBtn (ControllerDigital::X);

//Button (Y)
ControllerButton YBtn (ControllerDigital::Y);

//Top left trigger (L1)
ControllerButton leftUp (ControllerDigital::L1);

//Bottom left trigger (L2)
ControllerButton leftDown (ControllerDigital::L2);

//Top right trigger (R1)
ControllerButton rightUp (ControllerDigital::R1);

//Bottom right trigger (R2)
ControllerButton rightDown (ControllerDigital::R2);


//Integrated encoder of left front motor
IntegratedEncoder LFEncode (20);

//Integrated encoder of left back motor
IntegratedEncoder LBEncode (10);

//Integrated encoder of right front motor
IntegratedEncoder RFEncode (11);

//Integrated encoder of right back motor
IntegratedEncoder RBEncode (1, true);


//Individual mobile goal lifter motors
Motor MoGoLift1 ({3, false, AbstractMotor::gearset::red, AbstractMotor::encoderUnits::degrees});
Motor MoGoLift2 ({4, true, AbstractMotor::gearset::red, AbstractMotor::encoderUnits::degrees});

//Mobile goal hook motor
Motor MoGoHook (7, true, AbstractMotor::gearset::red, AbstractMotor::encoderUnits::degrees);

//Hook on top of MoGo lift for holding goals in place.
Motor MoGoHold (11, false, AbstractMotor::gearset::red, AbstractMotor::encoderUnits::degrees);

//Left drive train
MotorGroup LDrive ({1, 2});

//Right drive train
MotorGroup RDrive ({-9, -10});

//Mobile goal lifter
MotorGroup MoGoLift ({MoGoLift1, MoGoLift2});
