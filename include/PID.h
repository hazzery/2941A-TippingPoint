#pragma once
#include <string>
#include "main.h"

// #define DISABLE_PREDEFINED_UNITS
#define ENABLE_PREDEFINED_VOLTAGE_UNITS
#define ENABLE_PREDEFINED_LENGTH_UNITS
#define ENABLE_PREDEFINED_ANGULAR_VELOCITY_UNITS

#include "units.h"

using namespace units::length;
using namespace units::voltage;
using namespace units::angular_velocity;
using namespace units::dimensionless;


class PID
{
    
    public:
        /**
         * @brief Initialize new PID object with PID constants
         *
         * @param _kP Proportional multiplier
         * @param _kI Integral multiplier
         * @param _kD Derivative multipler
         * @param _motorGearset The Okapi::AbstractMotor::gearset being used in the motor being controled
         * @param _name name of component PID is controlling
        **/
        PID (scalar_t _kP, scalar_t _kI, scalar_t _kD, AbstractMotor::gearset _motorGearset, std::string _name);

        /**
         * @brief Calculate power output for motor, given sensor value
         *
         * @param _sensorVal current value of affiliated sensor
         * 
         * @return The power for related motor
        **/
        volt_t Calculate(inch_t _sensorVal);
        
        /**
         * @brief Has the PID control finished?
         * 
         * @return true is PID is completed, flase if not
        **/
        bool Done();
        
        /**
         * @brief Set a new target (set point) for the PID controller with specified time limit
         *
         * @param _target the desired finishing sensor value
         * @param _time the maximum time allowed for the movement
        **/
        void SetTarget(inch_t _target, millisecond_t _time);

        /**
         * @brief Set a new target (set point) for the PID controller
         *
         * @param _target the desired finishing sensor value
        **/
        void SetTarget(inch_t _target);

        /**
         * @brief Getter function for the PID's target
         * 
         * @return the PID target
        **/
        inch_t GetTarget();
    
    protected:
        inch_t target = (inch_t)0; 
        const std::string name;
        
    private:
        const scalar_t kP;
        const scalar_t kI;
        const scalar_t kD;
        const revolutions_per_minute_t motorRPM;
        const scalar_t ticksPerRev;

        inch_t error;

        millisecond_t startTime;
        millisecond_t maxTime;

        static constexpr scalar_t minDerivative = 2;
        static constexpr scalar_t integralLimit = 5000;
        static constexpr inch_t maxCompletionError = (inch_t)20;
        static constexpr volt_t maxOutput = (volt_t)12000;
};