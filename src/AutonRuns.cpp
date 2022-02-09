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

    Chassis::Rotate(-93, 5000); // Rotate toward aliance MoGo

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