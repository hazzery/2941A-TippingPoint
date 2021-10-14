#pragma once
#include "DualMotorContainer.h"

// #define DISABLE_PREDEFINED_UNITS
#define ENABLE_PREDEFINED_VOLTAGE_UNITS
#define ENABLE_PREDEFINED_LENGTH_UNITS
#define ENABLE_PREDEFINED_TIME_UNITS
#define ENABLE_PREDEFINED_AGLE_UNITS

using namespace units::length;
using namespace units::voltage;
using namespace units::angle;
using namespace units::time;
using namespace units::literals;

class Chassis
{
public:
    /**
     * @brief Sets the robot's distance target.
     * 
     * This function is only effective if you are
     * looping `Chassis::RunPID()` in a background task
     * 
     * @param _distance The number of encoder units to drive the robot
    **/
    static void DriveStraight(inch_t _distance);
    
    /**
     * @brief Set's the robot's distance and time targets.
     * 
     * This function is only effective if you are
     * looping `Chassis::RunPID()` in a background task
     *  
     * @param _distance The number of encoder units to drive the robot
     * @param _time The maximum amount of time the movement should take
    **/
    static void DriveStraight(inch_t _distance, millisecond_t _time);

    /**
     * @brief Sets the robot's rotate target
     * 
     * This function is only effective if you are
     * looping `Chassis::RunPID()` in a background task
     * 
     * @param _angle The number of encoder units to rotate the robot
    **/
    static void Rotate(radian_t _angle);

    /**
     * @brief Sets the robot's rotate and time targets.
     * 
     * This function is only effective if you are
     * looping `Chassis::RunPID()` in a background task
     * 
     * @param _angle The number of encoder units to rotate the robot
     * @param _time The maximum amount of time the movement should take
    **/
    static void Rotate(radian_t _angle, millisecond_t _time);

    /**
     * @brief Drives the robot using tank drive conrolls.
     * 
     * This function needs to be constantly looped to be effective
     * 
     * @param _controller A pointer to an okapi::Controller
    **/
    static void Tank(Controller *const _controller);

    /**
     * @brief Drives the robot using aracde conrolls.
     * 
     * This function needs to be constantly looped to be effective
     * 
     * @param _controller A pointer to an okapi::Controller
    **/
    static void Arcade(Controller *const _controller);

    /**
     * @brief Executes the targeted actions.
     * 
     * This function needs to be constantly looped to be effective
    **/
    static void RunPID();

private:
    static DualMotorContainer leftDrive;
    static DualMotorContainer rightDrive;

    static PID rotatePID;
    static PID straightPID;
    
    static bool rotating;
};