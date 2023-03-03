#include "vex.h"
#include "auton.h"
#include <iostream>

int strafeVelocityA = 100;
int drivetrainVelocityA = 65.0;
int drivetrainTraversalVelocityA = 75;
int rollerVelocityA = 60;

void autonomous() {
  // Motor config initalizations
  strafe.setVelocity(strafeVelocityA, pct);
  Drivetrain.setDriveVelocity(drivetrainVelocityA, pct);
  Drivetrain.setTurnVelocity(80, pct);
  roller.setVelocity(rollerVelocityA, pct);
  launch_conveyor.setVelocity(90, pct);

  // ==== START - OPERATION 1: Roller 1 ====
  // Align roller 1
  strafe.spinFor(reverse, 0.4, turns, true);
  Drivetrain.driveFor(forward, 3, inches, true);

  // Run roller 1
  roller.spinFor(forward, 0.3, turns, true);

  // ==== START - OPERATION 3: Fire pre loaded disc ====
  // Align to fire point
  Drivetrain.driveFor(reverse, 5, inches, true);
  Drivetrain.turnFor(right, 165, degrees, true);

  Drivetrain.setDriveVelocity(drivetrainTraversalVelocityA, pct);
  Drivetrain.driveFor(reverse, 30, inches, true);
  Drivetrain.setDriveVelocity(drivetrainVelocityA, pct);
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
}