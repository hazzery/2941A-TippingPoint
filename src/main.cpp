#include "main.h"
#include "setup.h"
#include "PID.h"
#include "MotorContainer.h"

PID FrontLiftPID(19, 0, 0, 0, 700, "Front Lift PID");
PID BackLiftPID (19, 0, 0, 0, 700, "Back Lift PID");

// MotorContainer liftMotors[4] = {{&FrontLeftLiftMotor, &FrontLiftPID, &FrontLeftLiftEncoder, 0},
// 								{&FrontRightLiftMotor, &FrontLiftPID, &FrontRightLiftEncoder, 0},
// 								{&BackLeftLiftMotor, &BackLiftPID, &BackLeftLiftEncoder, 0},
// 								{&BackRightLiftMotor, &BackLiftPID, &BackRightLiftEncoder, 0}};

MotorContainer liftMotors[2] = {{&FrontLeftLiftMotor, &FrontLiftPID, &FrontLeftLiftEncoder, 0},
								{&FrontRightLiftMotor, &FrontLiftPID, &FrontRightLiftEncoder, 0}};

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
static float leftSpeed() { return controller.getAnalog(ControllerAnalog::leftY) * 12000; }
static float rightSpeed() { return controller.getAnalog(ControllerAnalog::rightY) * 12000; }

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
	//All MoGo related motors to use lock position when stopped
	// FrontLeftLiftMotor.setBrakeMode(AbstractMotor::brakeMode::hold);
	// FrontRightLiftMotor.setBrakeMode(AbstractMotor::brakeMode::hold);
	// BackLeftLiftMotor.setBrakeMode(AbstractMotor::brakeMode::hold);
	// BackRightLiftMotor.setBrakeMode(AbstractMotor::brakeMode::hold);

	while (true)
	{
		//Drives robot using tank control.
		LeftDrive.moveVoltage(leftSpeed());
		RightDrive.moveVoltage(rightSpeed());

		//Simple mo-go lift control
		// if(RightUpTrigger.isPressed())
		// 	FrontMoGoLift.moveVoltage(11000);
		// else if(RightDownTrigger.isPressed())
		// 	FrontMoGoLift.moveVoltage(-5000);
		// else
		// 	FrontMoGoLift.moveVoltage(0);
			
		// if(LeftUpTrigger.isPressed())
		// 	BackMoGoLift.moveVoltage(11000);
		// else if(LeftDownTrigger.isPressed())
		// 	BackMoGoLift.moveVoltage(-11000);
		// else
		// 	BackMoGoLift.moveVoltage(0);

		//Slightly more complex Mo-go lift control
		if(RightUpTrigger.isPressed())
			FrontLiftPID.IncrementTarget(15);
		else if(RightDownTrigger.isPressed())
			FrontLiftPID.IncrementTarget(-15);

		if(LeftUpTrigger.isPressed())
			BackLiftPID.IncrementTarget(15);
		else if(LeftDownTrigger.isPressed())
			BackLiftPID.IncrementTarget(-15);

			cout << endl << endl << "Left: " << endl;
			liftMotors[0].outputPower = liftMotors[0].pid->Calculate(liftMotors[0].encoder->get());
			liftMotors[0].motor->moveVoltage(liftMotors[0].outputPower);

			cout << endl << endl << "Right: " << endl;
			liftMotors[1].outputPower = liftMotors[1].pid->Calculate(liftMotors[1].encoder->get());
			liftMotors[1].motor->moveVoltage(liftMotors[1].outputPower);

		// for(MotorContainer& container : liftMotors)
		// {
		// 	container.outputPower = container.pid->Calculate(container.encoder->get());
		// 	container.motor->moveVoltage(container.outputPower);
		// 	// cout << container.pid->Name << " - Target: " << container.pid->GetTarget() << " Output Power: " << container.pid->GetTarget() << endl;
		// }

		delay(50);//Waits 50 milliseconds before rerunning.
	}
}
