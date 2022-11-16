using namespace vex;

extern brain Brain;

using signature = vision::signature;

// VEXcode devices
extern motor leftDriveMotor;
extern motor rightDriveMotor;
extern signature Camera__RED_BALL;
extern signature Camera__BLUE_BALL;
extern signature Vision__SIG_3;
extern signature Vision__SIG_4;
extern signature Vision__SIG_5;
extern signature Vision__SIG_6;
extern signature Vision__SIG_7;
extern vision Vision;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );