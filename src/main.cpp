#include "main.h"
#include "setup.h"

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
	Chassis::DriveStraight(3050, 750);	//650 Drive towards neutral mo-go
	FrontMoGoLift.SetTarget(-3100);		//Lower front mo-go lift to pick up neutral mo-go
	delay(500);

	BackMoGoLift.SetTarget(-2800);		//Lower back mo-go lift in preperation for aliance mo-go
	delay(1000);

	FrontMoGoLift.SetTarget(-100);		//Raise front mo-go lift to hold neutral mo-go // 100
	delay(1000);

	Chassis::Rotate(-40);				//Rotate robot towards aliance mo-go
	delay(1000);

	Chassis::DriveStraight(-1200, 750);	//Reverse robot to aliance mo-go
	BackMoGoLift.SetTarget(-3200);		//lower lift all way down for 
	delay(750);

	BackMoGoLift.SetTarget(50);			//Raise back lift to put aliance mo-go in tray
	delay(750);
	
	FrontMoGoLift.SetTarget(50);		//Raise front lift to place neutral mo-go in tray
	delay(750);

	BackMoGoLift.SetTarget(-15);		//Stop lift from pressing into tray
	Chassis::Rotate(-30);				//Rotate robot to face centre mo-go
	delay(500);

	// Chassis::DriveStraight(1000);		//Drive robot to centre neutral mo-go
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
