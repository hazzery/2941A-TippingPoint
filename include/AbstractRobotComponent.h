#pragma once

#include "MotorContainer.h"
#include "PID.h"

class AbstractRobotComponent : public PID
{
public:
    /**
     * @brief A DriveTrain object controls one half of your robot's chassis. (for a tank or H drive)
     * 
     * @param _frontMotorPort The port number that the front most motor is in on the Brain
     * @param _backMotorPort The port number that the back most motor is in on the Brain
     * @param _gearset The okaipi::AbstractMotor::gearset that is the component's motors
     * @param _kP Proportional multiplier
     * @param _kI Integral multiplier
     * @param _kD Derivative multipler
     * @param _name std::string name of component
    **/
    AbstractRobotComponent(int8_t _firstMotorPort, int8_t _secondMotorPort, AbstractMotor::gearset _gearset, float _kP, float _kI, float _kD, std::string _name);

    // using PID::Done;
    // using PID::SetTarget;
    // using PID::GetTarget;

    /**
     * @brief Sends specified volatage to both drive motors.
     * 
     * @param _voltage The voltage to send to both drive motors in millivolts (-12000 to 12000)
    **/
    void PowerMotors(int16_t _voltage);

    /**
     * @brief Zeros the encoder value of both of the lift's motors
    **/
    void ResetSensors();

    /**
     * @brief Runs the PID and returns its output.
     * 
     * @return The voltage output from the PID to be sent to the motors
    **/
    int16_t CalculatePID();

protected:
    MotorContainer first;
    MotorContainer second;
};