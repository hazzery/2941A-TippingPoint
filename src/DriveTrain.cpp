#include "DriveTrain.h"

double DriveTrain::GetAverageSensor()
{
    return ( first.encoder.get() + second.encoder.get()) / 2;
}