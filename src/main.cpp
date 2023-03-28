/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       HanleyP                                                   */
/*    Created:      2/1/2023, 8:25:43 AM                                      */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"

#define bs Brain.Screen
#define cs Controller1.Screen

using namespace vex;

std::string lobster = "🦞";

// A global instance of competition
competition Competition;


// define your global instances of motors and other devices here

// Pi
double pi = 3.14159265358979323846;


//bool disk_detected = ((Distance.objectDistance(mm) >= 0) && (Distance.objectDistance(mm) <= 20));




///////////////////////////////////Odometry Tracking WIP /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



/*---------------------------------------------------------------------------*/
/*                               Controller Print                            */
/*---------------------------------------------------------------------------*/

int controller_print_task()
{
  cs.clearScreen();
  while (1)
  {

    cs.setCursor(0, 0);
    cs.print("Current: ");
    cs.print(flyWheel.velocity(pct));
    cs.newLine();
    cs.print("Target: ");
    cs.print(target);
    cs.newLine();
    cs.print("Battery: ");
    cs.print(Brain.Battery.capacity());
    cs.print(" %");
    wait(300, msec);
    //cs.clearScreen();
    

   



   
   

   


  return 10;
}
}

/*---------------------------------------------------------------------------*/
/*                                  Intakes Task                             */
/*---------------------------------------------------------------------------*/

int intakesTask()
{

  // Turns light on to 100%
  Optical.setLightPower(100, percent);
  Optical.setLight(ledState::on);

  // If R1 is held down, intakes spin fwd
  if (Controller1.ButtonR1.pressing())
  {
    intakes.spin(fwd, 100, pct);
  }
  // If R2 is held down, Intakes spin rev
  else if (Controller1.ButtonR2.pressing())
  {
    intakes.spin(directionType::rev, 600, rpm);
  }
  else if (Controller1.ButtonL2.pressing())
  {
    intakes.spin(reverse, 300, rpm);
  }
  // Under any other circumstance, intakes are still
  else
  {
    intakes.stop(brakeType::brake);
  }
  return 10;
}

/*---------------------------------------------------------------------------*/
/*                          Autonnomous Selection Task                       */
/*---------------------------------------------------------------------------*/

// Used to select the desred auton before a match
int autoSelectorTask()
{

  // If limit switch is pressed, then the limitSelector function is used
  limit1.pressed(limitSelector);

  // Infinite while loop
  while (1)
  {
    // Clears screen, and tells it to print text in the top right corner of the
    // brain screen
    Brain.Screen.clearScreen();
    Brain.Screen.setCursor(4000, 4000);
    // If limitSelect is 1, then print "Win Point"
    if (limitSelect == 1)
    {
      Brain.Screen.print("1");
    }

    // The Following code is just used to print the title of the selected auto
    // to the brain screen If limitSelect is 2, then print "Roller"
    else if (limitSelect == 2)
    {
      Brain.Screen.print("2");
    }
    // If limitSelect is 3, then print "Roller 2";
    else if (limitSelect == 3)
    {
      Brain.Screen.print("3");
    }
    else if (limitSelect == 4)
    {
      Brain.Screen.print("4");
    }
    else if (limitSelect == 5)
    {
      Brain.Screen.print("2 Disk Left");
    }
    wait(500, msec);
  }

  return 10;
}

#define sb square_button
#define ip isPressed
#define df transparent, yellow
// Create Buttons Here

// Red
sb start_pos_1;
sb start_pos_2;
// Blue
sb start_pos_3;
sb start_pos_4;

sb red_roller_1;
sb red_roller_2;

sb blue_roller_1;
sb blue_roller_2;

sb red_high_goal;
sb blue_hight_goal;

sb endgame;

int button_task()
{

  while (1)
  {
    // Activate Buttons Here
    bs.drawImageFromFile("field.png", 0, 0);
    bs.printAt(480 / 2, 0, "Please Select Start Position");

    start_pos_1.activate(df), start_pos_2.activate(df), start_pos_3.activate(df), start_pos_4.activate(df);

    if (start_pos_1.ip)
    {
      while (1)
      {
        bs.printAt(480 / 2, 0, "Please Select Auton Targets");
        red_roller_1.activate(df), red_roller_2.activate(df), red_high_goal.activate(df);
        if (red_roller_1.ip && red_high_goal.ip)
        {
          auton = 1;
        }
      }
    }
  }

  return 10;
}

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void)
{
  task i(intakesTask);
  task b(bangBangFlywheel);
  task p(getFly);
  task c(controller_print_task);

  inertial1.calibrate();
  while(inertial1.isCalibrating()) {
    wait(10, msec);
  }
  Brain.Screen.drawRectangle(1, 1, 50, 10, green);
  

  
  
}

//
// Main will set up the competition functions and callbacks.
//
int main()
{
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true)
  {
    wait(100, msec);
  }
}
