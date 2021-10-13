#pragma once
#include "PID.h"
#include "main.h"
#include "AbstractRobotComponent.h"

class DriveTrain : public AbstractRobotComponent
{
public:
    using AbstractRobotComponent::AbstractRobotComponent;
    
    using AbstractRobotComponent::SetTarget;
    using AbstractRobotComponent::CalculatePID;
    using AbstractRobotComponent::PowerMotors;
    using AbstractRobotComponent::ResetSensors;

    /**
     * @brief Gets the mean value of the front and back encoders.
     * 
     * @return Half the sum of the two encoder values
    **/
    double GetAverageSensor();
};