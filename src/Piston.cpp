#include "Piston.h"

Piston::Piston(const char _adiPort)
    :digitalOut(_adiPort) {}

void Piston::Toggle()
{
    digitalOut.set_value(!state);
    state = !state;
}