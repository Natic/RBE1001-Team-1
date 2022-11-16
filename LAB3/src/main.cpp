#include "vex.h"

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// leftDriveMotor       motor         1               
// rightDriveMotor      motor         10              
// Vision               vision        5               
// ---- END VEXCODE CONFIGURED DEVICES ----


#define TARGET  150

bool moving = false;

void turnDrive(int speed){
  int leftDrive = speed;
  int rightDrive = speed;

  if(speed != 0)
    moving=true;
  else
    moving=false;
  leftDriveMotor.spin(fwd, leftDrive, pct);
  rightDriveMotor.spin(fwd, rightDrive, pct);
}


void visionControl() {
  while(1) {

    int numberObjects = Vision.takeSnapshot(REDBALL);

    if( numberObjects > 0 ) {

      vex::vision::object obj = Vision.objects[0];

      if( obj.centerY != 0 && obj.width > 20 && obj.height > 20 ) {
        int error = obj.centerY - TARGET;

        int drive = error;
        if( drive > 50 ) drive = 50;
        if( drive < -50 ) drive = -50;

        if( obj.centerY > (TARGET-15) && obj.centerY < (TARGET+15) ) {
          turnDrive(0);
        }
        else {
          turnDrive( drive );
        }
      } 
    }
    else {
      turnDrive( 50 );
    }
    

    vex::this_thread::sleep_for(50);
  }
}

int main() {        
 
    visionControl();

    Brain.Screen.clearScreen( vex::color::green );

    }   
