using namespace vex;

extern brain Brain;

// VEXcode devices
extern motor leftMotor;
extern motor rightMotor;
extern motor armMotor;
extern sonar rangeFinderFront;
extern line leftLineTracker;
extern line rightLineTracker;
extern controller Controller1;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );