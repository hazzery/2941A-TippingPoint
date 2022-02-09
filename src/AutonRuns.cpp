#include "main.h"
#include "Chassis.h"
#include "Conveyor.h"
#include "MoGoLift.h"
#include "MoGoHold.h"

void RightSide()
{
    MoGoLift::SetTarget(MoGoLift::Bottom); // Raise lift off of ground

    Chassis::DriveStraight(3200); // Drive toward neutral MoGo

    MoGoLift::TogglePiston(); // Hook onto neutral MoGo
    delay(150);

    MoGoLift::SetTarget(MoGoLift::Middle); // Lift neutral MoGo
    delay(150);

    Chassis::DriveStraight(-1950, 2000); // Reverse

    Chassis::Rotate(-93, 2500); // Rotate toward aliance MoGo

    Chassis::DriveStraight(-1050, 0, 10000); // Drive toward aliance MoGo

    MoGoHold::TogglePiston(); // Hook onto aliance MoGo
    delay(500);

    Conveyor::MoveUp(); // Drop preloads onto aliance MoGo
    
    Chassis::DriveStraight(350); // Drive forward a little

    Chassis::Rotate(94, 5000); // Rotate toward line of rings

    Chassis::DriveStraight(2300, 0, 4500); // Drive forward to collect rings

    Chassis::DriveStraight(-3000, 3000); // Reverse into aliance home zone

    Conveyor::Stop(); // Stop the conveyor because its not needed

    MoGoHold::TogglePiston(); // Drop the aliance MoGo

    Chassis::DriveStraight(200); // Move away from the aliance MoGo
}

void LeftSide()
{
    MoGoLift::SetTarget(MoGoLift::Bottom); // Raise lift off of ground

    Chassis::DriveStraight(3300); // Drive toward neutral MoGo

    MoGoLift::TogglePiston(); // Hook onto neutral MoGo
    delay(150);

    MoGoLift::SetTarget(MoGoLift::Middle); // Lift neutral MoGo
    delay(150);

    Chassis::DriveStraight(-3350, 2000); // Reverse

    Chassis::Rotate(-85, 5000); // Rotate toward aliance MoGo

    Chassis::DriveStraight(-450, 2500);

    Conveyor::MoveUp();

    delay(750);

    Chassis::DriveStraight(300);
}

void WinPoint()
{
    MoGoLift::SetTarget(MoGoLift::Top); // Lift the lift off of the ground
	Conveyor::MoveUp(); // Start the conveyor to drop the first preload into the aliance MoGo
	delay(550);	// Wait for ring to fall out

	Conveyor::Stop(); // Stop conveyor so other preloads dont drop

	delay(100);

	Chassis::DriveStraight(1800);

	Chassis::DriveStraight(-400);

	Chassis::Rotate(-45); // Rotate robot to align for next move

	Chassis::DriveStraight(-2200); // Reverse robot to align for next move

	Chassis::Rotate(38); // Rotate robot to align for next move

	Chassis::DriveStraight(-6100); // Reverse all the way to aliance MoGo

	delay(1700);

	MoGoHold::TogglePiston(); // Hook onto the aliance MoGo
    Conveyor::MoveUp(); // Spin up conveyor to drop remaining preloads
	delay(600);
	Chassis::DriveStraight(1300); // Move back to left half of field
	Conveyor::Stop();
	MoGoHold::TogglePiston(); // Drop aliance MoGo
	MoGoLift::SetTarget(MoGoLift::Bottom);
	
	Chassis::DriveStraight(400); // Drive away from aliance MoGo
}