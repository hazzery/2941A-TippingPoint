#include "Conveyor.h"
#include "Controller.h"

Motor Conveyor::motor (-1);

Conveyor::states Conveyor::state = stopped;

void Conveyor::MoveUp()
{
    motor.moveVoltage(12000 * 0.75);
    state = up;
}
void Conveyor::MoveDown()
{
    motor.moveVoltage(-12000 * 0.75);
    state = down;
}
void Conveyor::Stop()
{
    motor.moveVoltage(0);
    state = stopped;
}

void Conveyor::RunUserControl()
{
    if(LeftUpTrigger.changedToPressed())
    {
        if(state == down)
            Stop();
        else
            MoveUp();
    }
    else if(LeftDownTrigger.changedToPressed())
    {
        if(state == up)
            Stop();
        else
            MoveDown();
    }
}
