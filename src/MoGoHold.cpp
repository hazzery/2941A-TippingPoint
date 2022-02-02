#include "MoGoHold.h"
#include "Controller.h"

Piston MoGoHold::piston ('B');

void MoGoHold::RunUserControl()
{
    if(BButton.changedToPressed())
        piston.Toggle();
}