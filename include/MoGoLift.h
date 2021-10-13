#pragma once
#include "main.h"
#include "Direction.h"
#include "StepperPID.h"
#include "MotorContainer.h"

class MoGoLift
{
public:
    /**
     * @brief Contstructs a new Mo-Go lift
     * 
     * @param _leftPort The number of the V5 Brain port that the lift's left motor is plugged into
     * @param _rightPort The number of the V5 Brain port that the lift's right motor is plugged into
     * @param _pid A stepper PID instance that will be used to control the position of the lift
     * @param _upButton A pointer to a ControllerButton object which should move the lift upwards when pressed
     * @param _downButton A pointer to a ControllerButton object which should move the lift downwards when pressed
    **/
    MoGoLift(int8_t _leftPort, int8_t _rightPort, StepperPID _pid, ControllerButton *const _upButton, ControllerButton *const _downButton);

    /**
     * @brief Enables PID assisted control over the lift using the specified controller buttons
    **/
    void RunUserControl();

    /**
     * @brief Sends PID output as power to both lift motors based on their encoder values
    **/
    void CalculatePID();

    /**
     * @brief Sets PID target position relative to the lift's current position
     * 
     * @param _target The number of encoder units to move the lift by
    **/
    void SetTarget(int16_t _target);

    /**
     * @brief Zeros the encoder value of both of the lift's motors
    **/
    void ResetSensors();

    /**
     * @brief Checks to see if the lift has reach its set target
     * 
     * @return true if the lift has completed its movement to the target, otherwise false
    **/
    bool IsDone();

    void RunBangBang();     //DO NOT USE WITH RunUserControl() simultaneously
    void SetBangBangTarget(int16_t _target);

private:
    
    StepperPID pid;

    MotorContainer left;
    MotorContainer right;

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

    Direction lastMoveDirection;

    /**
     * @brief Gets the difference in position of the two sides of the lift
     * 
     * @return The lift's error in encoder units
    **/
    double distanceBetweenSides();

    ControllerButton *const upButton;
    ControllerButton *const downButton;

    int16_t bangBangTarget;
};