#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor leftDriveMotor = motor(PORT1, ratio18_1, true);
motor rightDriveMotor = motor(PORT10, ratio18_1, false);
/*vex-vision-config:begin*/
signature Camera__RED_BALL = signature (1, 7971, 9717, 8844, -825, -259, -542, 3.6, 0);
signature Camera__BLUE_BALL = signature (2, -1947, -1467, -1707, 7831, 9413, 8622, 5.8, 0);
signature Vision__SIG_3 = signature (3, 0, 0, 0, 0, 0, 0, 3, 0);
signature Vision__SIG_4 = signature (4, 0, 0, 0, 0, 0, 0, 3, 0);
signature Vision__SIG_5 = signature (5, 0, 0, 0, 0, 0, 0, 3, 0);
signature Vision__SIG_6 = signature (6, 0, 0, 0, 0, 0, 0, 3, 0);
signature Vision__SIG_7 = signature (7, 0, 0, 0, 0, 0, 0, 3, 0);
vision vision = vision (PORT5, 50, Camera__RED_BALL, Camera__BLUE_BALL); 
/*vex-vision-config:end*/

// VEXcode generated functions



/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}