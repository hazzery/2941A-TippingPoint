#pragma once
#include "PID.h"
#include "main.h"
#include "MotorContainer.h"
#include "AbstractRobotComponent.h"

class DriveTrain /*: public AbstractRobotComponent*/
{
public:
    DriveTrain(int8_t _frontMotorPort, int8_t _backMotorPort, PID _pid, ControllerAnalog _controllerAxis);

    void RunUserControl(Controller *const _controller);

    double RunPID();

    void Move(int _voltage);
    
    double GetAverageSensor();

    void SetTarget(double _target);
    void SetTarget(double _target, double _time);

    void ResetSensors();

private:
    MotorContainer front;
    MotorContainer back;

    PID pid;

    ControllerAnalog controllerAxis;
};