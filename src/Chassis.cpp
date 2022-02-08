#include "Chassis.h"
#include "Controller.h"
#define DEG_TO_RAD 0.01745329

#define driveGearset AbstractMotor::gearset::green

pros::IMU Chassis::gyro(16);
RotationSensor Chassis::trackingWheel(15);
double Chassis::trackingWheelOffset = 0;

DualMotorContainer Chassis::leftDrive (12, 11, driveGearset);
DualMotorContainer Chassis::rightDrive (-19, -20, driveGearset);

Motor Chassis::horizontalDrive (-13);

PID Chassis::rotatePID
(
    9.5, 0.3, 0,            // kP, kI, kD
    driveGearset,           // AbstractMotor::gearset
    "Chassis Rotate PID"    // PIDname
);

PID Chassis::straightPID
(
    17, 0.7, 0,             // kP, kI, kD
    driveGearset,           // AbstractMotor::gearset
    "Chassis Straight PID"  // PIDname
);

bool Chassis::rotating = false;

void Chassis::DriveStraight(int16_t _distance, uint32_t _time, uint16_t _max_output)
{
    rotating = false;

    leftDrive.ResetSensors();
    rightDrive.ResetSensors();
    
    _time == 0 ? straightPID.SetTarget (_distance, _max_output) : straightPID.SetTarget (_distance, _time, _max_output);

    rotatePID.SetTarget(0, 5000);

    while(!straightPID.Done())
        delay(1);
}

void Chassis::Rotate(int16_t _angle, uint32_t _time, uint16_t _max_output)
{
    _angle *= 19.44444444;
    rotating = true;

    leftDrive.ResetSensors();
    rightDrive.ResetSensors();
    
    _time == 0 ? rotatePID.SetTarget(_angle, _max_output) : rotatePID.SetTarget (_angle, _time, _max_output);

    while(!rotatePID.Done())
        delay(1);
}

void Chassis::HDrive()
{
    leftDrive.PowerMotors (controller.getAnalog(ControllerAnalog::leftY)  * 12000 * 0.97);
    rightDrive.PowerMotors(controller.getAnalog(ControllerAnalog::rightY) * 12000 * 0.97);

    if(LeftButton.isPressed())
        horizontalDrive.moveVoltage(12000);
    else if(RightButton.isPressed())
        horizontalDrive.moveVoltage(-12000);
    else
        horizontalDrive.moveVoltage(0);
}

void Chassis::RunPID()
{
    double rotatePower = rotatePID.Calculate(leftDrive.GetAverageSensor() - rightDrive.GetAverageSensor());

    if(!rotating)
    {
        leftDrive.PowerMotors (straightPID.Calculate( leftDrive.GetAverageSensor()) + rotatePower * (rotatePower < 0 ? 4 : 1) );
        rightDrive.PowerMotors(straightPID.Calculate(rightDrive.GetAverageSensor()) - rotatePower * (rotatePower < 0 ? 1 : 4) );
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