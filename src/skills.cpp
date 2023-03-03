#include "skills.h"
#include "vex.h"
#include <iostream>

int strafeVelocity = 100;
int drivetrainVelocity = 65.0;
int drivetrainTraversalVelocity = 75;
int rollerVelocity = 60;

void skills() {
  // Motor config initalizations
  strafe.setVelocity(strafeVelocity, pct);
  Drivetrain.setDriveVelocity(drivetrainVelocity, pct);
  Drivetrain.setTurnVelocity(80, pct);
  roller.setVelocity(rollerVelocity, pct);
  launch_conveyor.setVelocity(90, pct);

  // ==== START - OPERATION 1: Roller 1 ====
  // Align roller 1
  strafe.spinFor(reverse, 0.4, turns, true);
  Drivetrain.driveFor(forward, 3, inches, true);

  // Run roller 1
  roller.spinFor(forward, 0.3, turns, true);

  // ==== START - OPERATION 2: Roller 2 ====
  // Align roller 2
  Drivetrain.driveFor(reverse, 27, inches, true);
  Drivetrain.turnFor(left, 165, degrees, true);
  Drivetrain.driveFor(forward, 31, inches, true);

  // Run roller 2
  roller.spinFor(forward, 0.2, turns, true);

  // ==== START - OPERATION 3: Fire pre loaded disc ====
  // Align to fire point
  Drivetrain.setDriveVelocity(drivetrainTraversalVelocity, pct);
  Drivetrain.driveFor(reverse, 40, inches, true);
  Drivetrain.setDriveVelocity(drivetrainVelocity, pct);
  Drivetrain.turnFor(left, 165*2, degrees, true);
  Drivetrain.driveFor(forward, 38, inches, true);

  // Starting spinning
  flywheel.spin(forward, 10, volt);

  Drivetrain.turnFor(right, 165, degrees, true);
  Drivetrain.driveFor(reverse, 35, inches, true);
  Drivetrain.driveFor(forward, 19.4, inches, true);

  // Fire
  launch_conveyor.spinToPosition(793, degrees, true);
  launch_conveyor.spinToPosition(0, degrees, true);
  wait(1, seconds);
  flywheel.stop();

  // ==== START - OPERATION 4: Traverse to other set of rollers ====
  // Move
  Drivetrain.setDriveVelocity(drivetrainTraversalVelocity, pct);
  Drivetrain.driveFor(forward, 90, inches, true);
  Drivetrain.setDriveVelocity(drivetrainVelocity, pct);
}