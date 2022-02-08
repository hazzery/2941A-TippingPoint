#include "MoGoHold.h"
#include "Controller.h"

Piston MoGoHold::piston ('A');

void MoGoHold::RunUserControl()
{
    if(BButton.changedToPressed())
        piston.Toggle();
}

void MoGoHold::TogglePiston()
{
    piston.Toggle();
}