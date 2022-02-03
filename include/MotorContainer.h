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
    MotorContainer(int8_t _portNumber);

    /**
     * @brief == operator for comparing two MotorContainers
     * 
     * @return true if both port numbers are same, otherwise false 
    **/
    bool operator==(MotorContainer& _otherSide) const;

    Motor motor;
    IntegratedEncoder encoder;
};