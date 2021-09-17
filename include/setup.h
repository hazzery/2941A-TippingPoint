#pragma once
#include "main.h"

extern Controller controller;

extern ControllerButton UpButton;
extern ControllerButton DownButton;
extern ControllerButton LeftButton;
extern ControllerButton RightButton;
extern ControllerButton AButton;
extern ControllerButton BButton;
extern ControllerButton XButton;
extern ControllerButton YBButton;
extern ControllerButton LeftUpTrigger;
extern ControllerButton LeftDownTrigger;
extern ControllerButton RightUpTrigger;
extern ControllerButton RightDownTrigger;

extern IntegratedEncoder FrontLeftDriveEncoder;
extern IntegratedEncoder FrontRightDriveEncoder;
extern IntegratedEncoder BackLeftDriveEncoder;
extern IntegratedEncoder BackRightDriveEncoder;

extern IntegratedEncoder FrontLeftLiftEncoder;
extern IntegratedEncoder FrontRightLiftEncoder;
extern IntegratedEncoder BackLeftLiftEncoder;
extern IntegratedEncoder BackRightLiftEncoder;

extern Motor FrontLeftLiftMotor;
extern Motor FrontRightLiftMotor;
extern Motor BackLeftLiftMotor;
extern Motor BackRightLiftMotor;

extern MotorGroup LeftDrive;
extern MotorGroup RightDrive;

extern MotorGroup FrontMoGoLift;
extern MotorGroup BackMoGoLift;