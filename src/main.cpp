/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\jjm6c                                            */
/*    Created:      Wed Nov 02 2022                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// leftMotor            motor         1               
// rightMotor           motor         10              
// armMotor             motor         8               
// rangeFinderFront     sonar         A, B            
// leftLineTracker      line          C               
// rightLineTracker     line          D               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

const float Kp = 5;
const float setDistance = 11;

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  
  while (true){
    float error = rangeFinderFront.distance(inches) - setDistance;
    Brain.Screen.printAt(30, 30, "%f     \n", error);
    printf("Error = %g \n", error);
    leftMotor.setVelocity(Kp * error, rpm);
    rightMotor.setVelocity(Kp * error, rpm);
    leftMotor.spin(fwd);
    rightMotor.spin(fwd);
  }
  
}
