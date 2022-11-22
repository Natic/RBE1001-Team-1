// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// leftDriveMotor       motor         1               
// rightDriveMotor      motor         10              
// Vision               vision        5               
// ---- END VEXCODE CONFIGURED DEVICES ----
#include "vex.h"

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// leftDriveMotor       motor         1
// rightDriveMotor      motor         10
// Vision               vision        5
// ---- END VEXCODE CONFIGURED DEVICES ----

const int TARGET_POS = 150;
const int TARGET_WIDTH = 30;

bool moving = false;

void turnDrive(int turn, int move)
{
  // POSITIVE TURN MEANS TURN RIGHT.
  int leftDrive  = move + turn;
  int rightDrive = move - turn;

  if (turn != 0 || move != 0)
    moving = true;
  else
    moving = false;
  leftDriveMotor.spin(reverse, leftDrive, pct);
  rightDriveMotor.spin(reverse, rightDrive, pct);
}

void visionControl()
{
  while (1)
  {

    int numberObjects = Vision.takeSnapshot(Vision__SIG_1);

    if (numberObjects > 0)
    {

      vex::vision::object obj = Vision.objects[0];

      if (obj.centerY != 0 && obj.width > 10)
      {
        int side_error = obj.centerX - TARGET_POS; // THE MORE RIGHT, THE MORE ERROR
        Brain.Screen.setCursor(1, 10);
        Brain.Screen.print(obj.centerX);
        Brain.Screen.setCursor(1, 20);
        Brain.Screen.print(side_error);
        float front_error = obj.width - TARGET_WIDTH; // THE CLOSER, THE MORE ERROR
        Brain.Screen.setCursor(2, 10);
        Brain.Screen.print(obj.width);
        Brain.Screen.setCursor(2, 20);
        Brain.Screen.print(front_error);

        int turn_spd = side_error; // THE MORE ERROR, THE MORE TURN RIGHT
        if (turn_spd > 20)
          turn_spd = 20;
        if (turn_spd < -20)
          turn_spd = -20;

        bool horizontally_aligned = obj.centerY > (TARGET_POS - 5) && obj.centerY < (TARGET_POS + 5);
        bool distance_aligned = obj.width > (TARGET_WIDTH - 5) && obj.width < (TARGET_WIDTH + 5);

        int turn_value;
        int move_value;
        
        if (!horizontally_aligned)
        {
          turn_value = turn_spd / 3;
          Brain.Screen.setCursor(1, 1);
          Brain.Screen.print("|!HO|");
        }else{
          turn_value = 0;
          Brain.Screen.setCursor(1, 1);
          Brain.Screen.print("|HO|");
        }
        if (!distance_aligned)
        {
          move_value = front_error * 2; // THE MORE ERROR, THE MORE MOVE FORWARD
          Brain.Screen.setCursor(2, 1);
          Brain.Screen.print("|!DA|");
        }else{
          move_value = 0;
          Brain.Screen.setCursor(2, 1);
          Brain.Screen.print("|DA|");
        }

        turnDrive(turn_value, move_value);
        
      }
    }else{
      turnDrive(0, 0);
    }
    Brain.Screen.setCursor(3, 1);
    Brain.Screen.print("|DONE|");

    vex::this_thread::sleep_for(20);
    Brain.Screen.clearScreen();
  }
}

int main()
{

  visionControl();

  Brain.Screen.clearScreen(vex::color::green);
}
