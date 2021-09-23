#include "main.h"
#include "setup.h"
#include "StepperPID.h"

enum Orientation : bool
{
	Forwards,
	Backwards
};

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
void autonomous() {}


//Converts controller joystick value to voltage for motors.
static float leftSpeed(Orientation orientation)
{
	if(orientation == Forwards)
		return controller.getAnalog(ControllerAnalog::leftY) * 12000;
	else
		return controller.getAnalog(ControllerAnalog::rightY) * -12000;
}

static float rightSpeed(Orientation orientation)
{ 
	if(orientation == Forwards)
		return controller.getAnalog(ControllerAnalog::rightY) * 12000;
	else
		return controller.getAnalog(ControllerAnalog::leftY) * -12000;
}

static float paceySpeed() { return controller.getAnalog(ControllerAnalog::rightX) * 12000; }

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
	Orientation orientation = Forwards;

	while (true)
	{
		//Drives robot using tank control.
		LeftDrive.moveVoltage(leftSpeed(orientation));
		RightDrive.moveVoltage(rightSpeed(orientation));

		//Drives robot using arcade control, because Pacey likes it for some reason.
		// LeftDrive.moveVoltage(leftSpeed(Forwards) + paceySpeed());
		// RightDrive.moveVoltage(leftSpeed(Forwards) - paceySpeed());

		if(AButton.changedToPressed())
			orientation = (Orientation)!orientation;
		
		FrontMoGoLift.RunUserControl();
		BackMoGoLift.RunUserControl();

		delay(15);//Wait 15 milliseconds before rerunning.
	}
}
