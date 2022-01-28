#include "Chassis.h"
#include "setup.h"
#define DEG_TO_RAD 0.01745329

#define driveGearset AbstractMotor::gearset::green

pros::IMU Chassis::gyro(16);
RotationSensor Chassis::trackingWheel(15);
double Chassis::trackingWheelOffset = 0;

DualMotorContainer Chassis::leftDrive (12, -19, driveGearset);
DualMotorContainer Chassis::rightDrive (2, -9, driveGearset);

PID Chassis::rotatePID
(
    9.5, 0.016, 0,          // kP, kI, kD
    driveGearset,           // AbstractMotor::gearset
    "Chassis Rotate PID"    // PIDname
);

PID Chassis::straightPID
(
    17, 0.1, 0,             // kP, kI, kD
    driveGearset,           // AbstractMotor::gearset
    "Chassis Straight PID"  // PIDname
);

bool Chassis::rotating = false;

void Chassis::DriveStraight(int16_t _distance, uint32_t _time)
{
    rotating = false;

    leftDrive.ResetSensors();
    rightDrive.ResetSensors();
    
    _time == 0 ? straightPID.SetTarget (_distance) : straightPID.SetTarget (_distance, _time);

    rotatePID.SetTarget(0);
}

void Chassis::Rotate(int16_t _angle)
{
    _angle *= 19.44444444;
    rotating = true;

    leftDrive.ResetSensors();
    rightDrive.ResetSensors();
    
    rotatePID.SetTarget(_angle);
}

void Chassis::Tank(Controller *const _controller)
{
    leftDrive.PowerMotors (_controller->getAnalog(ControllerAnalog::leftY)  * 12000);
    rightDrive.PowerMotors(_controller->getAnalog(ControllerAnalog::rightY) * 12000);
}

void Chassis::Arcade(Controller *const _controller)
{
    float vertical   = _controller->getAnalog(ControllerAnalog::leftY);
    float horizontal = _controller->getAnalog(ControllerAnalog::rightX);

    leftDrive.PowerMotors( (vertical + horizontal) * 12000);
    rightDrive.PowerMotors((vertical - horizontal) * 12000);
}

void Chassis::RunPID()
{
    double rotatePower = rotatePID.Calculate(leftDrive.GetAverageSensor() - rightDrive.GetAverageSensor());

    if(!rotating)
    {

        leftDrive.PowerMotors (straightPID.Calculate( leftDrive.GetAverageSensor()) + rotatePower * (rotatePower < 0 ? 4 : 0) );
        rightDrive.PowerMotors(straightPID.Calculate(rightDrive.GetAverageSensor()) - rotatePower * (rotatePower < 0 ? 0 : 4) );
    }
    else
    {
        leftDrive.PowerMotors(rotatePower);
        rightDrive.PowerMotors(-rotatePower);
    }
}

void Chassis::ResetSensors()
{
    while(trackingWheel.get() == 0);

    while (gyro.is_calibrating());

    trackingWheelOffset = trackingWheel.get();
    cout << trackingWheelOffset << endl;

    leftDrive.ResetSensors();
    rightDrive.ResetSensors();
}

double Chassis::GetTrackingWheel()
{
    return (trackingWheel.get() - trackingWheelOffset) * 1.659448;
}