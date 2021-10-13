#pragma once
#include "PID.h"
#include "main.h"
#include "MotorContainer.h"
#include "AbstractRobotComponent.h"

class DriveTrain /*: public AbstractRobotComponent*/
{
public:
    DriveTrain(int8_t _frontMotorPort, int8_t _backMotorPort, PID _pid);

    int16_t RunPID();

    /**
     * @param _voltage The voltage to send to both drive motors in millivolts (-12000 to 12000)
    **/
    void PowerMotors(int16_t _voltage);
    double GetAverageSensor();

    void SetTarget(int16_t _target);

    void SetTarget(int16_t _target, uint32_t _time);

    void ResetSensors();

private:
    MotorContainer front;
    MotorContainer back;

    PID pid;
};