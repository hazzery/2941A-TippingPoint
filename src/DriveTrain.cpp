#include "DriveTrain.h"

DriveTrain::DriveTrain(int8_t _frontMotorPort, int8_t _backMotorPort, PID _pid)
    : front(_frontMotorPort), back(_backMotorPort), pid(_pid) {}

void DriveTrain::SetTarget(int16_t _target)
{
    ResetSensors();
    pid.SetTarget(_target);
}

void DriveTrain::SetTarget(int16_t _target, uint32_t _time)
{
    ResetSensors();
    pid.SetTarget(_target, _time);
}

void DriveTrain::ResetSensors()
{
    front.encoder.reset();
    back.encoder.reset();
}

void DriveTrain::PowerMotors(int16_t _voltage)
{
    front.motor.moveVoltage(_voltage);
    back.motor.moveVoltage(_voltage);
}

int16_t DriveTrain::RunPID()
{
    return pid.Calculate(back.encoder.get());
}

double DriveTrain::GetAverageSensor()
{
    return ( front.encoder.get() + back.encoder.get()) / 2;
}