#pragma once
#include "Piston.h"

class MoGoHold
{
public:
    static void RunUserControl();

    static void TogglePiston();

private:
    static Piston piston;
};