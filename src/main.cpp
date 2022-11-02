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

const double wheel_circ_cm = 10.48 * 3.14159;
const double turn_const = 0.05;

void turn_custom(double percent, double distance_in, double turn_in);

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  
  // while (true){
  //   // float error = rangeFinderFront.distance(inches) - setDistance;
  //   // Brain.Screen.printAt(30, 30, "%f     \n", error);
  //   // printf("Error = %g \n", error);
  //   // leftMotor.setVelocity(Kp * error, rpm);
  //   // rightMotor.setVelocity(Kp * error, rpm);
  //   // leftMotor.spin(fwd);
  //   // rightMotor.spin(fwd);

    

  // }

  double dist_cm = 138;

  int accuracy = 20;

  for(int i = 0; i < accuracy; i++){
    int32_t left_power = leftLineTracker.reflectivity();
    int32_t right_power = rightLineTracker.reflectivity();

    double turn_cm_param = (double)right_power - (double)left_power;

    turn_custom(100, dist_cm / (double)accuracy, turn_cm_param * turn_const);
  }
  
}

void turn_custom(double percent, double distance_cm, double turn_cm){
  double left_dist = distance_cm + turn_cm;
  double right_dist = distance_cm - turn_cm;

  double ratio = left_dist/right_dist;
  if(ratio > 1){
    ratio = 1/ ratio;
    leftMotor.setVelocity(100, pct);
    rightMotor.setVelocity(ratio * 100, pct);
  }else{
    leftMotor.setVelocity(ratio * 100, pct);
    rightMotor.setVelocity(100, pct);
  }

  leftMotor.spinFor(forward, 360 * left_dist / wheel_circ_cm, degrees);
  rightMotor.spinFor(forward, 360 * right_dist / wheel_circ_cm, degrees);

}

