#include "vex.h"
using namespace vex;

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

// Toggle Switch Variables
bool status = false;
bool status2 = false;
bool statusH = false;

bool status3 = false;

// Toggle Switch Functions, Used in pnuematics
void toggle() { status = !status; }

void toggle2() { status2 = !status2; }

void toggleH() { statusH = !statusH; }

void toggle3() {status3 = !status3; }

void usercontrol(void)
{

  isRev = false;

  target = 64;

  while (1)
  {
    
    front_left.spin(directionType::fwd,
                    (Controller1.Axis3.value() + Controller1.Axis4.value()),
                    velocityUnits::pct);
    mid_left.spin(directionType::fwd,
                  (Controller1.Axis3.value() + Controller1.Axis4.value()),
                  velocityUnits::pct);
    back_left.spin(directionType::fwd,
                   (Controller1.Axis3.value() + Controller1.Axis4.value()),
                   velocityUnits::pct);

    front_right.spin(directionType::fwd,
                     (Controller1.Axis3.value() - Controller1.Axis4.value()),
                     velocityUnits::pct);
    mid_right.spin(directionType::fwd,
                   (Controller1.Axis3.value() - Controller1.Axis4.value()),
                   velocityUnits::pct);
    back_right.spin(directionType::fwd,
                    (Controller1.Axis3.value() - Controller1.Axis4.value()),
                    velocityUnits::pct);

    if (Controller1.ButtonX.pressing()) {
      target = 100;
    }

    else if (Controller1.ButtonA.pressing()) {
      target = 80;
    }

    else if (Controller1.ButtonB.pressing()) {
      target = 70;
    }

    else if (Controller1.ButtonY.pressing()) {
      target = 55;
    }

    else if (Controller1.ButtonUp.pressing()) {
      target = 0;
    }

    // Pnuematic Controls

    if (Controller1.ButtonLeft.pressing()) {
      toggle();
      wait(300, msec);
    }
    if (Controller1.ButtonRight.pressing()) {
      toggle2();
      wait(300, msec);
    }

    

    if (status == true) {
      end1.open();
    } else {
      end1.close();
    }

    if (status2 == true) {
      end2.open();
    } else {
      end2.close();
    }

    // Controller1.ButtonLeft.pressed(stat1F);
    // Controller1.ButtonL1.pressed(toggleH);
    if (statusH == true) {
      hood.open();
    } else {
      hood.close();
    }

    

    if (Controller1.ButtonL1.pressing()) {
      toggleH();
      wait(500, msec);
    }

    if(Controller1.ButtonR1.pressing()) {
      intakes.spin(fwd, 600, rpm);
    }
    else if(Controller1.ButtonR2.pressing()) {
      intakes.spin(reverse, 600, rpm);
    }
    else {
      intakes.stop(brake);
    }

    

    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}