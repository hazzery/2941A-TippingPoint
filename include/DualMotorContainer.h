#pragma once

#include "MotorContainer.h"

class DualMotorContainer
{
public:
    /**
     * @brief A DriveTrain object controls one half of your robot's chassis. (for a tank or H drive)
     * 
     * @param _frontMotorPort The port number that the front most motor is in on the Brain
     * @param _backMotorPort The port number that the back most motor is in on the Brain
     * @param _gearset The okaipi::AbstractMotor::gearset that is the component's motors
    **/
    DualMotorContainer(int8_t _firstMotorPort, int8_t _secondMotorPort, AbstractMotor::gearset _gearset);

    /**
     * @brief Sends specified volatage to both drive motors.
     * 
     * @param _voltage The voltage to send to both drive motors in millivolts (-12000 to 12000)
    **/
    void PowerMotors(int16_t _voltage);

    /**
     * @brief Gets the mean value of the front and back encoders.
     * 
     * @return Half the sum of the two encoder values
    **/
    double GetAverageSensor();

    /**
     * @brief Zeros the encoder value of both of the lift's motors
    **/
    void ResetSensors();

protected:
    MotorContainer first;
    MotorContainer second;
};