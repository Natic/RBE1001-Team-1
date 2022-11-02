#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor leftMotor = motor(PORT1, ratio18_1, true);
motor rightMotor = motor(PORT10, ratio18_1, false);
motor armMotor = motor(PORT8, ratio18_1, false);
sonar rangeFinderFront = sonar(Brain.ThreeWirePort.A);
line leftLineTracker = line(Brain.ThreeWirePort.C);
line rightLineTracker = line(Brain.ThreeWirePort.D);
controller Controller1 = controller(primary);

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}