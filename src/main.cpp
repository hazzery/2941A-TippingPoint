#include "main.h"
#include "setup.h"
#include "StepperPID.h"

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
 * Runs asyncronously during Autonomous the period
 * Must be paused upon the start of user control.
 */ 
void AutonBackgroundTask()
{
    while(true)
    {
        Chassis::RunPID();

        FrontMoGoLift.RunPID();
        BackMoGoLift.RunPID();

        delay(15); //Wait 15 milliseconds before rerunning.
    }
}
pros::Task poweringTheMotors(AutonBackgroundTask);

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
	FrontMoGoLift.SetTarget(-3300);
	Chassis::DriveStraight(3500, 650);
	delay(500);
	BackMoGoLift.SetTarget(-3300);
	delay(3000);
	Chassis::Rotate(-800);
	delay(2000);
	Chassis::Rotate(400);
	delay(500);
	Chassis::DriveStraight(500);
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
	poweringTheMotors.remove();

	while (true)
	{
		//Drives robot using tank control.
		Chassis::Tank(&controller);
		
		FrontMoGoLift.RunUserControl();
		BackMoGoLift.RunUserControl();

		delay(15);//Wait 15 milliseconds before rerunning.
	}
}
