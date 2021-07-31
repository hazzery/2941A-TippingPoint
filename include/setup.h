#pragma once
#include "main.h"

extern Controller controller;

extern ControllerButton upBtn;
extern ControllerButton downBtn;
extern ControllerButton leftBtn;
extern ControllerButton rightBtn;
extern ControllerButton ABtn;
extern ControllerButton BBtn;
extern ControllerButton XBtn;
extern ControllerButton YBtn;
extern ControllerButton leftUp;
extern ControllerButton leftDown;
extern ControllerButton rightUp;
extern ControllerButton rightDown;

extern IntegratedEncoder LFEncode;
extern IntegratedEncoder LBEncode;
extern IntegratedEncoder RFEncode;
extern IntegratedEncoder RBEncode;

extern Motor MoGoHook;
extern Motor MoGoHold;

extern Motor MoGoLift1;
extern Motor MoGoLift2;

extern MotorGroup LDrive;
extern MotorGroup RDrive;
extern MotorGroup MoGoLift;