#pragma once
#include <string>

class PID {
    
    public:
        /**
         * Initialize new PID object with PID constants
         *
         * @param _kP Proportional multiplier
         * @param _kI Integral multiplier
         * @param _kD Derivative multipler
         * @param _minPosition Sensor value of harware at minimum position
         * @param _maxPosition Sensor value of harware at maximum position
         * @param _name Name of component PID is controlling
        **/
        PID (double _kP, double _kI, double _kD, double _minPosition, double _maxPosition, std::string _name);
        ~PID();
        

        /**
         * Calculate power output for motor, given sensor value
         *
         * @param _sensorVal current value of affiliated sensor
         * 
         * @return The power for related motor
        **/
        double Calculate(double _sensorVal);
        
        /**
         * Has the PID control finished?
         * 
         * @return true is PID is completed, flase if not
        **/
        bool Done();
        
        /**
         * Gets PID error, given sensor value
         *
         * @param sensorValue current value of affiliated sensor
         * 
         * @return The current error of the PID controler
        **/
        double CalculateError(double _sensorVal);
        
        /**
         * Set a new target (set point) for the PID controller
         *
         * @param target the desired finishing sensor value
        **/
        void SetTarget(double _target);
        
        /**
         * Starts the PID timer
         * This allows for done() due to timeout
        **/
        void StartTimer();

        /**
         * Reset the error, integral, and derivative terms
         * 
         * This is for when a completely new target is being set,
         * and previos values need to be cleared.
        **/
        void ResetPID();

        /**
         * Adds the specified value to the PID target value
         * 
         * @param _increment amount to increment target by
        **/
        void IncrementTarget(const int8_t _increment);

        /**
         * Getter function for the PID's target
         * 
         * @return the PID target
        **/
        int GetTarget();

    public:
        const std::string Name;
    
    private:
        const double kP;
        const double kI;
        const double kD;
        const double minOutput;
        const double maxOutput;
        const double maxTime;
        const double maxError;
        const double integralLimit;
        const double minDerivative;
        const double minPosition;
        const double maxPosition;
        double target;
        double error = 11;
        double pastError;
        double integral;
        double derivative = 11;
        double startTime;
};