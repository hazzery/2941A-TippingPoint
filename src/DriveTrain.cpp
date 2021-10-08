#include "DriveTrain.h"

DriveTrain::DriveTrain(int8_t _frontMotorPort, int8_t _backMotorPort, PID _pid, ControllerAnalog _controllerAxis)
    : front(_frontMotorPort), back(_backMotorPort), pid(_pid), controllerAxis(_controllerAxis) {}

void DriveTrain::RunUserControl(Controller *const _controller)
{
    front.motor.moveVoltage(_controller->getAnalog(controllerAxis) * 12000);
    back.motor.moveVoltage(_controller->getAnalog(controllerAxis) * 12000);
}

void DriveTrain::SetTarget(double _target)
{
    pid.SetTarget(_target);
}