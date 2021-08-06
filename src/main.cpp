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
	MoGoLift.moveVoltage(-6500);	//Lifts MoGo lift out the way of the MoGo hook
	delay(500);
	MoGoLift.moveVoltage(-2000);	//Slow the MoGo lift
	delay(100);
	MoGoHook.moveVoltage(-2500);	//Move MoGo hook out from underneath MoGolift
	delay(500);
	MoGoHook.moveVoltage(0);		//Stop the MoGo lift and hook
	MoGoLift.moveVoltage(0);
}


//Converts controller joystick value to voltage for motors.
float leftSpeed() { return controller.getAnalog(ControllerAnalog::leftY) * 12000; }
float rightSpeed() { return controller.getAnalog(ControllerAnalog::rightY) * 12000; }

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
	bool goalHolding;//If the MoGo hook holding a MoGo?

	//All MoGo related motors to use lock position when stopped
	MoGoLift.setBrakeMode(AbstractMotor::brakeMode::hold);
	MoGoHook.setBrakeMode(AbstractMotor::brakeMode::hold);
	MoGoHold.setBrakeMode(AbstractMotor::brakeMode::hold);

	while (true)
	{
		//Drives robot using tank control.
		LDrive.moveVoltage(leftSpeed());
		RDrive.moveVoltage(rightSpeed());

		//Simple MoGo lift control
		if(rightUp.isPressed())
			MoGoLift.moveVoltage(11000);
		else if(rightDown.isPressed())
			MoGoLift.moveVoltage(-5000);
		else
			MoGoLift.moveVoltage(0);
			

		//Simple MoGo hook control
		if(controller.getDigital(ControllerDigital::L1))
			MoGoHook.moveVoltage(4500);
		else if(controller.getDigital(ControllerDigital::L2))
			MoGoHook.moveVoltage(-4500);
		else
			MoGoHook.moveVoltage(0);

		//Toggle control for MoGo hook
		if(ABtn.changedToPressed())
		{
			if(!goalHolding)//If hook not holding a MoGo...
			{
				MoGoHold.moveAbsolute(-250, 55);//...raise hook to hold a goal.
				goalHolding = true;
			}
			else//If hook is holding a MoGo...
			{
				MoGoHold.moveAbsolute(0, 100);//...lower hook to release MoGo.
				goalHolding = false;
			}
		}

		delay(50);//Waits 50 milliseconds before rerunning.
	}
}
