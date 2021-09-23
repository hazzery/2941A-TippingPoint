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
         * @param _name Name of component PID is controlling
        **/
        PID (double _kP, double _kI, double _kD, std::string _name);
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
         * @param _sensorValue current value of affiliated sensor
         * 
         * @return The current error of the PID controler
        **/
        double CalculateError(double _sensorVal);
        
        /**
         * Set a new target (set point) for the PID controller
         *
         * @param _target the desired finishing sensor value
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
         * Getter function for the PID's target
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
        const double maxTime;
        const double maxCompletionError;
        const double integralLimit;
        const double minDerivative;
        double error = 11;
        double pastError;
        double integral;
        double derivative = 11;
        double startTime;
};