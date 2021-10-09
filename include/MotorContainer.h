#pragma once
#include "main.h"
#include "PID.h"

struct MotorContainer
{
    /**
     * @brief A container which holds a motor and its integrated encoder
     * 
     * @param _portnumber The port number on the V5 Brain which the motor is plugged into
    **/
    MotorContainer(int _portNumber);

    /**
     * @brief == operator for comparing two MotorContainers
    **/
    bool operator==(MotorContainer& _otherSide);

    Motor motor;
    IntegratedEncoder encoder;
};