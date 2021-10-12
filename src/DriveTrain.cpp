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
    ResetSensors();
    pid.SetTarget(_target);
}

void DriveTrain::SetTarget(double _target, double _time)
{
    ResetSensors();
    pid.SetTarget(_target, _time);
}

void DriveTrain::ResetSensors()
{
    front.encoder.reset();
    back.encoder.reset();
}

void DriveTrain::PowerMotors(int _voltage)
{
    front.motor.moveVoltage(_voltage);
    back.motor.moveVoltage(_voltage);
}

double DriveTrain::RunPID()
{
    return pid.Calculate(back.encoder.get());
}

double DriveTrain::GetAverageSensor()
{
    return ( front.encoder.get() + back.encoder.get()) / 2;
}