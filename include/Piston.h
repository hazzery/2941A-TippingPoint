#pragma once
#include "main.h"

class Piston
{
public:
    Piston(const char _adiPort);
    void Toggle();

private:
    pros::ADIDigitalOut digitalOut;
    bool state;
};