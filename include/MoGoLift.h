#pragma once
#include "StepperPID.h"
#include "main.h"
#include "Direction.h"
#include "DualMotorContainer.h"

class MoGoLift : public DualMotorContainer
{
public:
    /**
     * @brief Contstructs a new Mo-Go lift
     * 
     * @param _leftPort The number of the V5 Brain port that the lift's left motor is plugged into
     * @param _rightPort The number of the V5 Brain port that the lift's right motor is plugged into
     * @param _gearset The okapi::AbstractMotor::gearset that is in this lift's motors
     * @param _upButton A pointer to a ControllerButton object which should move the lift upwards when pressed
     * @param _downButton A pointer to a ControllerButton object which should move the lift downwards when pressed
    **/
    MoGoLift(int8_t _leftPort, int8_t _rightPort, AbstractMotor::gearset _gearset, ControllerButton *const _upButton, ControllerButton *const _downButton);

    using DualMotorContainer::PowerMotors;
    using DualMotorContainer::ResetSensors;

    /**
     * @brief Sets the lift's target position.
     * 
     * This function is only effective if you are
     * looping `MoGoLift::RunPID()` in a background task
     * 
     * @param _position The position (absolute) to move the lift to
    **/
    static void SetTarget(int16_t _distance);

    /**
     * @brief Enables PID assisted control over the lift using the specified controller buttons
    **/
    void RunUserControl();

    /**
     * @brief Sends PID output as power to both lift motors based on their encoder values
    **/
    void RunPID();

private:
    /**
     * The "leading" side of the lift is the side which is the furthest in the last moved direction.
     * Last moved direction is set each time the user presses the up and down buttons on the controller.
     * Direction::Forwards is up, for lifting a goal to the tray; and Backwards is down, for lowering the lift.
     * 
     * @brief Gets the side of the lift in the lead (See declaration for more info)
     * 
     * @return A MotorContainer pointer for the side of the lift which is currently "leading"
    **/
    MotorContainer *sideInTheLead();

    /**
     * The "leading" side of the lift is the side which is the furthest in the last moved direction.
     * Last moved direction is set each time the user presses the up and down buttons on the controller.
     * Direction::Forwards is up, for lifting a goal to the tray; and Backwards is down, for lowering the lift.
     *  
     * @brief Determines wether the specified side of the lift has moved further than the other (See declaration for more info)
     * 
     * @return true if the specified side has moved the furthest, otherwise false
    **/
    bool isInTheLead(MotorContainer& _side);

    /**
     * @brief Gets the difference in position of the two sides of the lift
     * 
     * @return The lift's error in encoder units
    **/
    double distanceBetweenSides();

private:
    static StepperPID pid;

    ControllerButton *const upButton;
    ControllerButton *const downButton;

    Direction lastMoveDirection;
};