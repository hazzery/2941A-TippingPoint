#pragma once
#include "PID.h"
#include "main.h"
#include "Piston.h"

class MoGoLift
{
public:
    enum LiftPosition : int16_t
    {
        Top = 1000,
        Middle = 500,
        Bottom = 0
    };
    /**
     * @brief Sets the lift's target position.
     * 
     * This function is only effective if you are
     * looping `MoGoLift::RunPID()` in a background task
     * 
     * @param _position The `MoGoLift::LiftPosition` to move the lift to
    **/
    static void SetTarget(LiftPosition _position);

    /**
     * @brief Enables PID assisted control over the lift using the specified controller buttons
    **/
    static void RunUserControl();

    /**
     * @brief Sends PID output as power to lift motor based on its encoder value
    **/
    static void RunPID();

    /**
     * @brief Prints the lift motor's encoder position to console
    **/
    static void PrintPositions();

    /**
     * @brief Lifts the lift.
     * 
     * This function is only effective if you are
     * looping `MoGoLift::RunPID()` in a background task
     * 
    **/
    static void incrementTarget();

    /**
     * @brief Lowers the lift.
     * 
     * This function is only effective if you are
     * looping `MoGoLift::RunPID()` in a background task
     * 
    **/
    static void decrementTarget();

private:
    static PID pid;

    static LiftPosition target;

    static Motor liftMotor;
    static Piston hookPiston;
};