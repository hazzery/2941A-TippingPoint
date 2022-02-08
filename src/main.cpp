#include "main.h"
#include "Chassis.h"
#include "MoGoHold.h"
#include "MoGoLift.h"
#include "Conveyor.h"

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs asynchronously during Autonomous the period
 * Must be paused upon the start of user control.
 */ 
void AutonBackgroundTask()
{
    while(true)
    {
        Chassis::RunPID();

        MoGoLift::RunPID();

        delay(5); //Wait 15 milliseconds before rerunning.
    }
}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous()
{
	pros::Task poweringTheMotors(AutonBackgroundTask);

	uint32_t startTime = pros::millis();

    MoGoLift::SetTarget(MoGoLift::Bottom);

    Chassis::DriveStraight(3200);

    cout << "hello" << endl;

    MoGoLift::TogglePiston();
    delay(150);

    MoGoLift::SetTarget(MoGoLift::Middle);
    delay(150);

    Chassis::DriveStraight(-1950);

    // delay(700);

    Chassis::Rotate(-93, 5000);
    // delay(1500);

    Chassis::DriveStraight(-1050);
    // delay(1500);

    MoGoHold::TogglePiston();
    delay(500);

    Conveyor::MoveUp();
    
    Chassis::DriveStraight(200);

    // delay(100);
    Chassis::Rotate(90, 5000);
    // delay(1000);

    Chassis::DriveStraight(2100);
    // delay(600);





    // MoGoLift::SetTarget(MoGoLift::Bottom);

    // Chassis::DriveStraight(3150);
    // delay(1200);

    // MoGoLift::TogglePiston();
    // delay(1000); // 500

    // Chassis::DriveStraight(-2200);

    // MoGoLift::SetTarget(MoGoLift::Middle);
    // delay(1300);

    // Chassis::Rotate(-93);
    // delay(1500);

    // Chassis::DriveStraight(-1050);
    // delay(1500);

    // MoGoHold::TogglePiston();

    // Conveyor::MoveUp();
    
    // delay(100);
    // Chassis::Rotate(97);
    // delay(1000);

    // Chassis::DriveStraight(500);
    // delay(600);

    while(pros::millis() - startTime < 14900) // 14900
        delay(1);

	poweringTheMotors.remove();
}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol()
{
    MoGoLift::initMotor();

	while (true)
	{
		Chassis::HDrive();
		MoGoLift::RunUserControl();
		Conveyor::RunUserControl();
		MoGoHold::RunUserControl();
        MoGoLift::PrintPositions();

		delay(15);//Wait 15 milliseconds before rerunning.
	}
}
