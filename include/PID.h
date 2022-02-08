#pragma once
#include <string>
#include "main.h"

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
        PID (float _kP, float _kI, float _kD, AbstractMotor::gearset _motorGearset, std::string _name);

        /**
         * @brief Calculate power output for motor, given sensor value
         *
         * @param _sensorVal current value of affiliated sensor
         * 
         * @return The power for related motor
        **/
        int16_t Calculate(double _sensorVal);
        
        /**
         * @brief Has the PID control finished?
         * 
         * @return true is PID is completed, flase if not
        **/
        bool Done() const;
        
        /**
         * @brief Set a new target (set point) for the PID controller with specified time limit
         *
         * @param _target the desired finishing sensor value
         * @param _time the maximum time allowed for the movement
        **/
        void SetTarget(int16_t _target, uint32_t _time, uint16_t _max_output);

        /**
         * @brief Set a new target (set point) for the PID controller
         *
         * @param _target the desired finishing sensor value
        **/
        void SetTarget(int16_t _target, uint16_t _max_output);

        /**
         * @brief Getter function for the PID's target
         * 
         * @return the PID target
        **/
        int16_t GetTarget() const;
    
    protected:
        int16_t target = 0; 
        const std::string name;
        
    private:
        const float kP;
        const float kI;
        const float kD;
        const uint16_t motorRPM;
        const uint16_t ticksPerRev;

        int error;

        uint32_t startTime;
        uint32_t maxTime;
        uint16_t maxOutput = 12000;

        static constexpr uint8_t minDerivative = 2;
        static constexpr uint16_t integralLimit = 5000;
        static constexpr uint8_t maxCompletionError = 20;
};