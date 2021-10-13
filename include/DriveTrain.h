#pragma once
#include "PID.h"
#include "main.h"
#include "AbstractRobotComponent.h"

class DriveTrain : public AbstractRobotComponent<PID>
{
public:
    using AbstractRobotComponent<PID>::AbstractRobotComponent;
    
    using AbstractRobotComponent<PID>::SetTarget;
    using AbstractRobotComponent<PID>::CalculatePID;
    using AbstractRobotComponent<PID>::PowerMotors;
    using AbstractRobotComponent<PID>::ResetSensors;

    /**
     * @brief Gets the mean value of the front and back encoders.
     * 
     * @return Half the sum of the two encoder values
    **/
    double GetAverageSensor();
};