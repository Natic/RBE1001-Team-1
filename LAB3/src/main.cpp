#include "vex.h"

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// leftDriveMotor       motor         1
// rightDriveMotor      motor         10
// Vision               vision        5
// ---- END VEXCODE CONFIGURED DEVICES ----

#define TARGET_POS 150
#define TARGET_WIDTH 10

bool moving = false;

void turnDrive(int turn, int move)
{
  int leftDrive = turn + move;
  int rightDrive = move - turn;

  if (turn != 0)
    moving = true;
  else
    moving = false;
  leftDriveMotor.spin(fwd, leftDrive, pct);
  rightDriveMotor.spin(reverse, rightDrive, pct);
}

void visionControl()
{
  while (1)
  {

    int numberObjects = Vision.takeSnapshot(REDBALL);

    if (numberObjects > 0)
    {

      vex::vision::object obj = Vision.objects[0];

      if (obj.centerY != 0 && obj.width > 20 && obj.height > 20)
      {
        int side_error = obj.centerY - TARGET_POS;
        int front_error = obj.width - TARGET_WIDTH;

        int turn_spd = side_error;
        if (turn_spd > 50)
          turn_spd = 50;
        if (turn_spd < -50)
          turn_spd = -50;

        if (obj.centerY > (TARGET_POS - 15) && obj.centerY < (TARGET_POS + 15) && obj.width > (TARGET_WIDTH - 10) && obj.width < (TARGET_WIDTH + 10))
        {
          turnDrive(0, 0);
        }
        else if (obj.centerY > (TARGET_POS - 15) && obj.centerY < (TARGET_POS + 15))
        {
          turnDrive(0, front_error * 7);
        }
        else if (obj.width > (TARGET_WIDTH - 10) && obj.width < (TARGET_WIDTH + 10))
        {
          turnDrive(turn_spd, 0);
        }
        else
        {
          turnDrive(turn_spd, front_error * 7);
        }
      }
    }
    else
    {
      turnDrive(50);
    }

    vex::this_thread::sleep_for(50);
  }
}

int main()
{

  visionControl();

  Brain.Screen.clearScreen(vex::color::green);
}
