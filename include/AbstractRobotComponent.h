#pragma once

#include "MotorContainer.h"
#include "PID.h"

template <typename pidType>
class AbstractRobotComponent
{
public:
    /**
     * @brief A DriveTrain object controls one half of your robot's chassis. (for a tank or H drive)
     * 
     * @param _frontMotorPort The port number that the front most motor is in on the Brain
     * @param _backMotorPort The port number that the back most motor is in on the Brain
     * @param _gearset The okaipi::AbstractMotor::gearset that is the component's motors
     * @param _pid Use an initializer list to create a PID object
    **/
    AbstractRobotComponent(int8_t _firstMotorPort, int8_t _secondMotorPort, AbstractMotor::gearset _gearset, pidType _pid);

    /**
     * @brief Sends specified volatage to both drive motors.
     * 
     * @param _voltage The voltage to send to both drive motors in millivolts (-12000 to 12000)
    **/
    void PowerMotors(int16_t _voltage);

    /**
     * @brief Sets a new target position relative to the drive's current position.
     * 
     * @param _target The number of encoder units to move the lift by
    **/
    void SetTarget(int16_t _target);

    /**
     * @brief Sets a new target position with a specified time limit.
     * 
     * Calling this function resets both encoders and sets the PID's target
     * This means that movement amounts are relative to the drive's current position
     * Maximum time allowed is also set to alter velocity.
     *
     * @param _target the desired finishing sensor value
     * @param _time the maximum time allowed for the movement
    **/  
    void SetTarget(int16_t _target, uint32_t _time);

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

    /**
     * @brief Checks to see if the lift has reach its set target
     * 
     * @return true if the lift has completed its movement to the target, otherwise false
    **/
    bool IsDone();

protected:
    MotorContainer first;
    MotorContainer second;

    pidType pid;
};