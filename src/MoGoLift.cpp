#include "MoGoLift.h"

MoGoLift::MoGoLift(uint8_t _leftPort, uint8_t _rightPort, StepperPID _pid, ControllerButton *const _upButton, ControllerButton *const _downButton)
    : left(_leftPort), right(-_rightPort), pid(_pid), upButton(_upButton), downButton(_downButton)
{
    left.motor.setGearing(AbstractMotor::gearset::red);
    right.motor.setGearing(AbstractMotor::gearset::red);
}

#define PID_INCREMENT 20

void MoGoLift::RunUserControl()
{
    if(upButton->isPressed())
        pid.IncrementTarget(PID_INCREMENT);

    else if(downButton->isPressed())
        pid.IncrementTarget(-PID_INCREMENT);

    else if (upButton->changedToReleased())
    {
        int leftSensor = left.encoder.get();
        int rightSensor = right.encoder.get();
        pid.SetTarget( (leftSensor > rightSensor) ? leftSensor : rightSensor );
    }
    else if (downButton->changedToReleased())
    {
        int leftSensor = left.encoder.get();
        int rightSensor = right.encoder.get();
        pid.SetTarget( (leftSensor < rightSensor) ? leftSensor : rightSensor );
    }


    cout << endl << "Left: " << endl;
    left.motor.moveVoltage( pid.Calculate( left.encoder.get() ) );

    cout << endl << "Right: " << endl;
    right.motor.moveVoltage( pid.Calculate( right.encoder.get() ) );
}