#pragma once
#include <string>

class PID {
    
    public:
        PID (double _kP, double _kI, double _kD, std::string _name = "untitled PID");
        ~PID();
        
        //Returns power output for specified motor, given current sensor value.
        double Calculate(double _sensorVal);
        
        //Returns true if robot has successfully reached its target.
        bool Done();
        
        //Returns PID error, given current sensor value value.
        double CalculateError(double _sensorVal);
        
        //Sets the robot's target distance. 
        void SetTarget(double _target);
        
        //Sets the PID's start time.
        void StartTimer();

        //Resets the private variables
        void ResetPID();

    public:
        double Target;
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
        double error = 11;
        double pastError;
        double integral;
        double derivative = 11;
        double startTime;
};