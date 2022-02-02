#pragma once
#include "main.h"

class Conveyor
{
public:
    static void MoveUp();
    static void MoveDown();
    static void Stop();
    
    static void RunUserControl();

private:
    static Motor motor;

    enum states : int8_t
    {
        up = 1,
        stopped = 0,
        down = -1
    };

    static states state;
};