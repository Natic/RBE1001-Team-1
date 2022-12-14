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
// leftLineTracker      line          C               
// rightLineTracker     line          D               
// Controller1          controller                    
// rangeFinderFront     sonar         G, H            
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
using namespace vex;

const float Kp = .6;
// const float setDistance = 11;
const double dist_cm_first = 120 / 2.5;
const double dist_cm_second = 180 / 2.5;
const int accuracy = 20;
const int reflectivity_threshold = 50;
const int vel = 40;

const bool is_smart = true;

const double wheel_circ_cm = 10.48 * 3.14159;
const double turn_const = 0.02;

const double turn_rad_cm = 92.7;

void turn_custom(double percent, double distance_in, double turn_in);
void follow_line(double distance_param, double distance_two);
void find_next_line();

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  if(is_smart){
    //Sensor Based Code

    rangeFinderFront.distance(inches);

    wait(4, seconds);

    follow_line(dist_cm_first, 13.0); // follows the line until 12 inches from a wall

    Brain.Screen.print("Done with First Edge\n");

    wait(1, seconds);
    
    find_next_line(); // turns until it finds the corner

    Brain.Screen.print("Done with First Corner\n");

    wait(1, seconds);

    follow_line(dist_cm_second, 6.0);

    Brain.Screen.print("Done with Second Edge\n");

    wait(1, seconds);

    find_next_line();
    
    Brain.Screen.print("Done with Second Corner\n");

    wait(1, seconds);
    
    follow_line(dist_cm_first, 10.0);

    Brain.Screen.print("Done!");

  }else{
    // Dead Reckoning Code

    turn_custom(vel, dist_cm_first, 0);
    wait(.2, seconds);
    turn_custom(20, 0, -turn_rad_cm / 4);
    wait(.2, seconds);
    turn_custom(vel, dist_cm_second, 0);
    wait(.2, seconds);
    turn_custom(20, 0, -turn_rad_cm / 4);
    wait(.2, seconds);
    turn_custom(vel, dist_cm_first - 25.2, 0);
  }
  // LEFTOVER COODE FROM SENSOR DEBUGGING.
  // while(true){
  //   Brain.Screen.print(rangeFinderFront.distance(inches));
  //   wait(4, seconds);
  // }
}

void turn_custom(double percent_set, double distance_cm, double turn_cm){
  
  // Turns given a speed, distance to cover, and distance to turn.

  double left_dist = distance_cm + turn_cm;
  double right_dist = distance_cm - turn_cm;

  double ratio = left_dist/right_dist;
  if(ratio > 1){
    ratio = 1/ ratio;
    leftMotor.setVelocity(percent_set, pct);
    rightMotor.setVelocity(ratio * percent_set, pct);
  }else{
    leftMotor.setVelocity(ratio * percent_set, pct);
    rightMotor.setVelocity(percent_set, pct);
  }

  leftMotor.spinFor(reverse, 360 * left_dist / wheel_circ_cm, degrees, false);
  rightMotor.spinFor(reverse, 360 * right_dist / wheel_circ_cm, degrees, true);

}
void follow_line(double distance_param, double distance_two){

  // Follows the line until 10 inches away from a wall.

  while(rangeFinderFront.distance(inches) > distance_two){

    double proportionality = rangeFinderFront.distance(inches) / distance_param * Kp; // Division is there to keep the values between 0 and Kp, and making Kp more general. It also prevents the motors from being told to run over 100%.

    int32_t left_power = leftLineTracker.reflectivity(); // percent Value between 0 and 100, higher on the black lines, so when the values reduce (meaning it's on white now), the robot turns in that direction to correct.
    int32_t right_power = rightLineTracker.reflectivity();

    leftMotor.spin(forward, ((float)left_power/2 + 50) * (float)proportionality, pct);
    rightMotor.spin(forward, ((float)right_power/2 + 50) * (float)proportionality, pct);
  }
  leftMotor.stop();
  rightMotor.stop();
}

void find_next_line(){

  // Turns until it's about 72 degrees away from its previous orientation, and then continues to turnn until it's on a line again. This is to get it off of the previous line, and make it find the new one.

  turn_custom(20, 0, - turn_rad_cm / 5);

  wait(.2, seconds);

  while(leftLineTracker.reflectivity() > reflectivity_threshold){
    rightMotor.spinFor(reverse, 60, degrees);
    wait(.2, seconds);
  }
}