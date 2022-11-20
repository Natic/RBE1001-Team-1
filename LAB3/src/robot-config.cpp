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
signature Vision__SIG_1 = signature (1, 7473, 9063, 8268, -745, -309, -527, 3.8, 0);
signature Vision__SIG_2 = signature (2, 0, 0, 0, 0, 0, 0, 3, 0);
signature Vision__SIG_3 = signature (3, 0, 0, 0, 0, 0, 0, 3, 0);
signature Vision__SIG_4 = signature (4, 0, 0, 0, 0, 0, 0, 3, 0);
signature Vision__SIG_5 = signature (5, 0, 0, 0, 0, 0, 0, 3, 0);
signature Vision__SIG_6 = signature (6, 0, 0, 0, 0, 0, 0, 3, 0);
signature Vision__SIG_7 = signature (7, 0, 0, 0, 0, 0, 0, 3, 0);
vision Vision = vision (PORT5, 50, Vision__SIG_1, Vision__SIG_2, Vision__SIG_3, Vision__SIG_4, Vision__SIG_5, Vision__SIG_6, Vision__SIG_7);
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