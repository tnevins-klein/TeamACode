/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       tnevins-klein                                             */
/*    Created:      Tue Feb 28 2023                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Drivetrain           drivetrain    4, 1, 5, 3      
// roller               motor         7               
// strafe               motor         2               
// flywheel             motor         8               
// expansion            digital_out   B               
// Controller1          controller                    
// launch_conveyor      motor         6               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include "skills.h"
#include "auton.h"
#include <iostream>

#define FLYWHEEL_INCREASE Controller1.ButtonR2
#define FLYWHEEL_DECREASE Controller1.ButtonR1
#define SPIN_LAUNCH_CONVEYOR Controller1.ButtonB

#define EXPANSION Controller1.ButtonA

using namespace vex;

/*
enum FlywheelMode {
  INTAKE,
  OFF,
  OUTTAKE
};

FlywheelMode mode = OFF;

int flywheelSpeed (FlywheelMode mode) {
  switch (mode) {
    case INTAKE:
      return 10;
    case OUTTAKE:
      return -6;
    default:
      return 0;
  }
}

*/
int flywheel_speed = 0;
bool wants_to_expand = false;

void writeControllerStatusLine() {
  Controller1.Screen.clearLine();
  Controller1.Screen.setCursor(1, 1);
  Controller1.Screen.print("F: %dV", flywheel_speed);
}

int process_inputs() {
  while (true) {
    strafe.setVelocity(Controller1.Axis4.position(percent), percent);
    strafe.spin(forward);
    }

  return 0;
}

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  writeControllerStatusLine();

  strafe.setVelocity(100, pct);
  roller.setVelocity(65, pct);
  launch_conveyor.setVelocity(90, pct);
  Drivetrain.setDriveVelocity(100, pct);

  
  FLYWHEEL_INCREASE.pressed([] {
    flywheel_speed += 4;
    flywheel.spin(forward, flywheel_speed, volt);

    writeControllerStatusLine();
  });

  FLYWHEEL_DECREASE.pressed([] {
    flywheel_speed -= 4;

    flywheel.spin(forward, flywheel_speed, volt);

    writeControllerStatusLine();
  });
  

  SPIN_LAUNCH_CONVEYOR.pressed([] {
    launch_conveyor.spinToPosition(793, degrees);
  });

  SPIN_LAUNCH_CONVEYOR.released([] {
    launch_conveyor.spinToPosition(0, degrees);
  });

  EXPANSION.pressed([] {
    if (wants_to_expand) {
      expansion.set(true);
      wants_to_expand = false;
      Controller1.rumble("...");
    } else {
      wants_to_expand = true;
      timer::event([] {
        wants_to_expand = false;
      }, 1000);
    }
  });
  
  Drivetrain.setStopping(brake);
  strafe.setStopping(brake);

  competition comp;
  comp.autonomous(autonomous);

  task proc_inputs(process_inputs);
  
}
