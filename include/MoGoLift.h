#pragma once
#include "main.h"
#include "Direction.h"
#include "AbstractRobotComponent.h"

class MoGoLift : public AbstractRobotComponent
{
public:
    /**
     * @brief Contstructs a new Mo-Go lift
     * 
     * @param _leftPort The number of the V5 Brain port that the lift's left motor is plugged into
     * @param _rightPort The number of the V5 Brain port that the lift's right motor is plugged into
     * @param _gearset The okapi::AbstractMotor::gearset that is in this lift's motors
     * @param _kP Proportional multiplier
     * @param _kI Integral multiplier
     * @param _kD Derivative multipler
     * @param _minPosition Sensor value of harware at minimum position
     * @param _maxPosition Sensor value of harware at maximum position
     * @param _name std::string name of component
     * @param _upButton A pointer to a ControllerButton object which should move the lift upwards when pressed
     * @param _downButton A pointer to a ControllerButton object which should move the lift downwards when pressed
    **/
    MoGoLift(int8_t _leftPort, int8_t _rightPort, AbstractMotor::gearset _gearset,
            float _kP, float _kI, float _kD, int16_t _minPosition, int16_t _maxPosition, std::string _name,
            ControllerButton *const _upButton, ControllerButton *const _downButton);

    using AbstractRobotComponent::SetTarget;
    using AbstractRobotComponent::PowerMotors;
    using AbstractRobotComponent::ResetSensors;

    /**
     * @brief Sends PID output as power to both lift motors based on their encoder values
    **/
    void RunPID();

    /**
     * @brief Enables PID assisted control over the lift using the specified controller buttons
    **/
    void RunUserControl();

    /**
     * @brief Increments PID target position by specified ammount.
     * 
     * @param _increment The amount to increment target by, can be positive or negative
    **/
    void IncrementTarget(const int8_t _increment);

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

    Direction lastMoveDirection;

    /**
     * @brief Gets the difference in position of the two sides of the lift
     * 
     * @return The lift's error in encoder units
    **/
    double distanceBetweenSides();

private:
    const int16_t minPosition;
    const int16_t maxPosition;

    ControllerButton *const upButton;
    ControllerButton *const downButton;

    int16_t bangBangTarget;
};