#pragma once
#include "main.h"
#include "PID.h"

struct MotorContainer
{
    Motor *motor;
    PID *pid;
    IntegratedEncoder *encoder;

    int16_t outputPower;
};
