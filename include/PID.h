#pragma once
#include <string>

class PID
{
    
    public:
        /**
         * @brief Initialize new PID object with PID constants
         *
         * @param _kP Proportional multiplier
         * @param _kI Integral multiplier
         * @param _kD Derivative multipler
         * @param _errorIntegralCalculate The maximum error in which integral will begin being calculated
         * @param _name Name of component PID is controlling
        **/
        PID (double _kP, double _kI, double _kD, double _errorIntegralCalculate, std::string _name);
        ~PID();
        

        /**
         * @brief Calculate power output for motor, given sensor value
         *
         * @param _sensorVal current value of affiliated sensor
         * 
         * @return The power for related motor
        **/
        double Calculate(double _sensorVal);
        
        /**
         * @brief Has the PID control finished?
         * 
         * @return true is PID is completed, flase if not
        **/
        bool Done();
        
        /**
         * @brief Gets PID error, given sensor value
         *
         * @param _sensorValue current value of affiliated sensor
         * 
         * @return The current error of the PID controler
        **/
        double CalculateError(double _sensorVal);
        
        /**
         * @brief Set a new target (set point) for the PID controller with a max time limit
         *
         * @param _target the desired finishing sensor value
         * @param _time the time requires for the movement
        **/
        void SetTarget(double _target, uint32_t _time);

        /**
         * @brief Set a new target (set point) for the PID controller
         *
         * @param _target the desired finishing sensor value
        **/
        void SetTarget(double _target);
        
        /**
         * @brief Starts the PID timer, allowing for done() due to timeout
        **/
        void StartTimer();

        /**
         * @brief Getter function for the PID's target
         * 
         * @return the PID target
        **/
        int GetTarget();

    public:
        const std::string Name;
    
    protected:
        double target;
        
    private:
        const double kP;
        const double kI;
        const double kD;
        const double minOutput;
        const double maxOutput;
        const double maxCompletionError;
        const double integralLimit;
        const double minDerivative;
        const double errorIntegralCalculate;

        double error;

        uint32_t startTime;
        uint32_t maxTime;
};