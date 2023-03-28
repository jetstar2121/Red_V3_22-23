#include "vex.h"
#include <iostream>
#include <vector>
#include <map>

using vex::blue;
using vex::red;

using namespace vex;

double hue = Optical.hue();




// Optical
void opticalRed()
{

  while (Optical.hue() <= 20 && Optical.hue() >= 0)
  {
    intakes.spin(reverse, 50, rpm);
  }
  intakes.stop();
}

void sequential_search_for(vex::color c)
{

  if (c == red)
  {

    for (int pos = 0; (Optical.hue() > 198 && Optical.hue() < 240) && pos <= 360; pos++)
    {
      intakes.spinToPosition(pos, deg);
    }
  }
}

vex::color positions[361];

std::map<int, vex::color> Positions;

/*
void search_for(vex::color c)
{
  intakes.setPosition(0, deg);

  for (int pos = 1; pos <= 360; pos++)
  {
    intakes.spinToPosition(pos, deg);

    if (Optical.hue() > 198 && Optical.hue() < 240)
    {
      Positions.insert({pos, blue});
    }
    else if (Optical.hue() > 0 && Optical.hue() < 20)
    {
      Positions.insert({pos, red});
    }
  }

  if (c == red)
  {

    for (it = symbolTable.begin(); it != symbolTable.end(); it++)
    {
      std::cout << it->first // string (key)
                << ':'
                << it->second // string's value
                << std::endl;
    }
  }
}
*/


void opticalBlue()
{

  while (Optical.hue() <= 240 && Optical.hue() >= 198)
  {

    intakes.spin(reverse, 50, rpm);
  }
  intakes.stop();
}

// Custom Drive Functions for Auton

// Stop Function
void stop(brakeType BT)
{
  rightDrive.stop(BT);
  leftDrive.stop(BT);
}

// General Drive Functions
void drive(double dis, double speed)
{
  

  rightDrive.spinFor(fwd, dis, deg, speed, rpm, false);
  leftDrive.spinFor(fwd, dis, deg, speed, rpm);
  stop(brake);
}

void screenTest(std::string text)
{
  Brain.Screen.clearScreen();
  Brain.Screen.setFont(mono60);
}
void screenTest(int num)
{
  Brain.Screen.clearScreen();
  Brain.Screen.setFont(mono60);
  Brain.Screen.print(num);
}

double constrainAngle(double x)
{
  x = fmod(x + 180, 360);
  if (x < 0)
    x += 360;
  return x - 180;
}

double turnAngle()
{
  return constrainAngle(inertial1.rotation(degrees));
}

void timeout(double time)
{
  double startTime = Brain.Timer.value();
  while (1)
  {
    if (Brain.Timer.value() > startTime + time)
    {
      break;
    }
    wait(5, msec);
  }
}

// Self correcting turn using inertial sensor
void turnTo(double angle, double speed, double timeout)
{
  double startTime = Brain.Timer.value();

  while (fabs(angle - turnAngle()) > 1)
  { // abs value of angle degree - angle > aceptable error 1 degree

    if (Brain.Timer.value() > startTime + timeout)
    {
      break;
    }

    // if angle is this turn right/left
    // The drivetrain turns right
    rightDrive.spin(fwd, speed * -1 * (angle - turnAngle()) / fabs(angle - turnAngle()), rpm);
    leftDrive.spin(fwd, speed * (angle - turnAngle()) / fabs(angle - turnAngle()), rpm);
    wait(5, msec);
  }
  stop(brake);
}

// After either scenario has been run, the drivetrain is stopped

// New Flywheel Function with one editable variable

void regTurn(vex::turnType dir, double angle, double speed)
{
  if (dir == right)
  {
    leftDrive.spinFor(fwd, angle, degrees, speed, rpm, false);
    rightDrive.spinFor(reverse, angle, degrees, speed, rpm);
  }
  else if (dir == left)
  {
    leftDrive.spinFor(reverse, angle, degrees, speed, rpm, false);
    rightDrive.spinFor(fwd, angle, degrees, speed, rpm);
  }
}

void turn(vex::turnType dir, double angle, double speed)
{

  if (dir == right)
  {
    while (inertial1.rotation(degrees) < (inertial1.rotation(degrees) + angle))
    {
      rightDrive.spin(fwd, speed, rpm);
      leftDrive.spin(reverse, speed, rpm);
    }
    stop(brake);
  }
  else if (dir == left)
  {
    while (inertial1.rotation(degrees) > (inertial1.rotation(degrees) - angle))
    {
      rightDrive.spin(reverse, speed, rpm);
      leftDrive.spin(fwd, speed, rpm);
    }
    stop(brake);
  }
}

void flywheelSpinCus(double speed)
{

  // Flywheel spins at specified speed in percent
  flyWheel.spin(fwd, speed, pct);
  // If the speed of the flywheel is equal to the desired speed
  if (flyWheel.current(pct) == speed)
  {
    // Then intakes spin (pushing the disk into the flywheel)
    intakes.spin(fwd, 100, pct);
    // Intakes spin for 1 second
    wait(1000, msec);
    // The flywheel and intakes stop
    flyWheel.stop(coast), intakes.stop(brake);
  }
}

// New Flywheel function with set values for Usercontrol purposes

void flywheelSpin100()
{

  flyWheel.spin(fwd, 60, pct);

  if (flyWheel.velocity(rpm) >= -110)
  {
    Brain.Screen.setFont(mono60);
    Brain.Screen.print("Test");
    intakes.spin(fwd, 100, pct);
    wait(1000, msec);
    flyWheel.stop(coast), intakes.stop(brake);
  }
}

int getFly()
{

  while (true)
  {

    std::cout << "\n \n \n \n \n \n \n";
    // std::cout << "Touch Screen Coordinates: (" << Brain.Screen.xPosition() << ", " << Brain.Screen.yPosition() << ") \n";
    // std::cout << "Brain.Screen.pressing(): " << Brain.Screen.pressing() << "\n";
    std::cout << "Fly Wheel PCT: " << flyWheel.velocity(pct) << "\n";

    std::cout << "Target: " << target;

    wait(300, msec);
  }

  return 0;
}

// Limit Switch Variable

int limitSelect = 1;

void limitSelector()
{
  // If limitSelect variable is less than ten, then add one to limitSelect
  if (limitSelect < 10)
  {
    limitSelect++;
  }
  // If limitSelect goes above 10, then reset it to 1
  else
  {
    limitSelect = 1;
  }
}

/*
// Pnuematic Toggleswitch
bool status2 = false;
bool status = false;

void toggle() {
  status = !status;
}

void toggle2() {
  status2 = !status2;
}
*/

// Function used for Optical Sensor

void opticalSetup(int lightPower)
{
  Brain.Screen.setFont(mono60);
  Optical.setLightPower(100, percent);
  Optical.setLight(ledState::on);
}

double opticalValue = Optical.hue();

bool opticalOn = true;

// 197, 240

void colorIntakeBlue()
{
  if (opticalOn == true)
  {
    do
    {
      intakes.spin(fwd, 600, rpm);
    } while (Optical.hue() >= 197 && Optical.hue() <= 240);
  }
}

void colorIntakeRed()
{
  if (opticalOn == true)
  {
    while (Optical.hue() >= 0 && Optical.hue() <= 20)
    {
      intakes.spin(fwd, 600, rpm);
    }
  }
}

bool stat1 = false;
bool stat2 = false;

void stat1F()
{
  stat1 = !stat1;
}

void stat2F()
{
  stat2 = !stat2;
}

void reset()
{
  stat1 = false;
  stat2 = false;
}

void changeRed()
{
  while (Optical.hue() <= 20 && Optical.hue() >= 0)
  {
    intakes.spin(reverse, 75, rpm);
  }
  intakes.stop();
}

void changeTo(vex::color c)
{
  if (c == vex::red)
  {
    while (Optical.hue() <= 20 && Optical.hue() >= 0)
    {
      intakes.spin(reverse, 50, rpm);
    }
    intakes.stop();
  }
  else if (c == vex::blue)
  {
    while (Optical.hue() <= 240 && Optical.hue() >= 198)
    {
      intakes.spin(reverse, 50, rpm);
    }
    intakes.stop();
  }
}