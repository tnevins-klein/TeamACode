using namespace vex;

extern brain Brain;

// VEXcode devices
extern drivetrain Drivetrain;
extern motor roller;
extern motor strafe;
extern motor flywheel;
extern digital_out expansion;
extern controller Controller1;
extern motor launch_conveyor;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );