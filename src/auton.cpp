#include "vex.h"

using namespace vex;

#define cv waitUntil((flyWheel.velocity(pct) <= target + 2) && (flyWheel.velocity(pct) >= target - 2))

bool disk_detected = (Distance.objectDistance(mm) <= 20);

double distance = Distance.objectDistance(mm);

MiniPID pidDrive = MiniPID(0.4, 0.0007, 0.6);
MiniPID pidTurn = MiniPID(.5, .9, .8);

int auton = 16;

// Add timeout
void drivePID(double dis, double speed, double timeout)
{

  DT.resetPosition();
  pidDrive.setOutputLimits(-speed, speed);
  double currentPos = 0;
  currentPos = (front_left.position(deg) + front_right.position(deg)) / 2;
  double output = pidDrive.getOutput(currentPos, dis);

  // Note to self, find correct value
  while (fabs(output) > 25)
  {
    currentPos = (front_left.position(deg) + front_right.position(deg)) / 2;
    output = pidDrive.getOutput(currentPos, dis);
    DT.spin(fwd, output, rpm);
  }
  stop(brake);
}

void drivePIDLong(double dis, double speed, double timeout)
{

  DT.resetPosition();
  pidDrive.setOutputLimits(-speed, speed);
  double currentPosLeft = 0;
  double currentPosRight = 0;
  currentPosLeft = front_left.position(deg);
  currentPosRight = front_right.position(deg);
  double outputLeft = pidDrive.getOutput(currentPosLeft, dis);
  double outputRight = pidDrive.getOutput(currentPosRight, dis);

  // Note to self, find correct value
  while (fabs(outputLeft) > 25 && fabs(outputRight) > 25)
  {
    currentPosLeft = front_left.position(deg);
    currentPosRight = front_right.position(deg);
    outputLeft = pidDrive.getOutput(currentPosLeft, dis);
    outputRight = pidDrive.getOutput(currentPosRight, dis);
    leftDrive.spin(fwd, outputLeft, rpm);
    rightDrive.spin(fwd, outputRight, rpm);
  }
  stop(brake);
}

void turnPID(double dis, double speed, double timeout)
{
  pidTurn.setOutputLimits(-speed, speed);
  double currentPos = 0;
  currentPos = turnAngle();
  double output = 3 * (pidTurn.getOutput(currentPos, dis));

  // Note to self, find correct value
  while (fabs(output) > 1)
  {
    currentPos = turnAngle();
    output = 3 * (pidTurn.getOutput(currentPos, dis));
    leftDrive.spin(fwd, output, rpm);
    rightDrive.spin(fwd, -output, rpm);
  }
  stop(brake);
}

void shoot(int disks_to_shoot)
{

  for (int i = 0; i < disks_to_shoot; i++)
  {
    waitUntil(flyWheel.velocity(pct) >= target - 2 && flyWheel.velocity(pct) <= target + 2);
    while (!(Distance.objectDistance(mm) < 20))
    {
      intakes.spin(fwd, 600, rpm);
    }
    intakes.stop();
  }
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void)
{

  inertial1.calibrate();

  // Left Side
  if (auton == 1)
  {
    isRev = true;
    drivePID(-50, 25.10, 10);
    wait(500, msec);
    while (Optical.hue() < 20 && Optical.hue() > 0)
    {
      intakes.spin(reverse, 50, rpm);
    }
    intakes.stop(brake);

    isRev = false;

    target = 90;

    wait(500, msec);

    drivePID(200, 50, 10);

    // DT.spinFor(fwd, 200, deg, 200, rpm);
    stop(coast);

    intakes.spinFor(reverse, 100, deg, 200, rpm);

    wait(500, msec);

    regTurn(left, 15, 50);
    stop(coast);

    wait(3000, msec);

    intakes.spinFor(fwd, 300, deg, 600, rpm);
    wait(2000, msec);
    intakes.spinFor(fwd, 300, deg, 600, rpm);
    wait(1500, msec);
    intakes.spinFor(fwd, 1000, deg, 600, rpm);
  }

  //
  else if (auton == 2)
  {
    isRev = true;
    drivePID(-50, 25.10, 10);
    wait(500, msec);
    while (Optical.hue() < 20 && Optical.hue() > 0)
    {
      intakes.spin(fwd, 50, rpm);
    }
    intakes.stop(brake);

    isRev = false;

    target = 100;

    // drivePID(200, 50, 10);

    DT.spinFor(fwd, 200, deg, 200, rpm);
    stop(coast);

    intakes.spinFor(reverse, 100, deg, 200, rpm);

    wait(500, msec);

    regTurn(left, 15, 50);
    stop(coast);

    wait(3000, msec);

    intakes.spinFor(fwd, 120, deg, 600, rpm);
    wait(1000, msec);
    intakes.spinFor(fwd, 300, deg, 600, rpm);
    wait(1000, msec);
    intakes.spinFor(fwd, 300, deg, 600, rpm);

    regTurn(right, 20, 50);

    // turn

    // drive

    // Intake 3-stack

    // turn

    // shoot
  }
  // Right Side
  else if (auton == 3)
  {
    isRev = true;
    drivePID(-50, 25.10, 10);
    wait(500, msec);
    while (Optical.hue() < 20 && Optical.hue() > 0)
    {
      intakes.spin(fwd, 50, rpm);
    }
    intakes.stop(brake);

    isRev = false;

    target = 100;

    drivePID(150, 100, 10);

    regTurn(right, 10, 100);

    wait(3000, msec);

    intakes.spinFor(fwd, 120, deg, 600, rpm);
    wait(1000, msec);
    intakes.spinFor(fwd, 300, deg, 600, rpm);
    wait(1000, msec);
    intakes.spinFor(fwd, 300, deg, 600, rpm);
  }
  else if (auton == 4)
  {

    isRev = true;
    drivePID(-50, 25.10, 10);
    wait(500, msec);
    while (Optical.hue() < 20 && Optical.hue() > 0)
    {
      intakes.spin(fwd, 50, rpm);
    }
    intakes.stop(brake);

    isRev = false;

    target = 100;

    drivePID(150, 100, 10);

    regTurn(right, 10, 100);

    wait(3000, msec);

    intakes.spinFor(fwd, 120, deg, 600, rpm);
    wait(1000, msec);
    intakes.spinFor(fwd, 300, deg, 600, rpm);
    wait(1000, msec);
    intakes.spinFor(fwd, 300, deg, 600, rpm);
  }
  else if (auton == 5)
  {

    target = 100;

    waitUntil(flyWheel.velocity(pct) >= 95 && flyWheel.velocity(pct) <= 105);

    while ((Distance.objectDistance(mm) < 20) == false)
    {
      intakes.spin(fwd, 600, rpm);

      if (Distance.objectDistance(mm) < 20)
      {
        intakes.stop();
        waitUntil(flyWheel.velocity(pct) >= 98 && flyWheel.velocity(pct) <= 105);
      }
    }
  }
  else if (auton == 6)
  {

    isRev = true;
    drivePID(-50, 25.10, 10);
    wait(500, msec);
    while (Optical.hue() < 20 && Optical.hue() > 0)
    {
      intakes.spin(reverse, 50, rpm);
    }
    intakes.stop(brake);

    drivePID(100, 100, 10);

    wait(300, msec);

    turnPID(-18, 100, 10);

    intakes.spin(reverse, 200, rpm);

    wait(300, msec);

    drive(450, 50);

    wait(300, msec);

    intakes.stop();

    turnPID(35, 100, 10);

    wait(300, msec);

    drivePID(-285, 100, 10);

    wait(500, msec);
    while (Optical.hue() < 20 && Optical.hue() > 0)
    {
      intakes.spin(reverse, 50, rpm);
    }
    intakes.stop(brake);

    wait(500, msec);

    drivePID(100, 100, 10);

    wait(300, msec);

    turnTo(50, 100, 10);

    wait(300, msec);

    // drivePID(700, 100, 10);
    drive(1600, 100);

    wait(300, msec);

    turnTo(45, 50, 10);

    wait(300, msec);

    hood.open();

    shoot(2);

    // shoot(2);

    /*

    drivePID(-50, 25.10, 10);
    wait(500, msec);
    while (Optical.hue() < 20 && Optical.hue() > 0)
    {
      intakes.spin(fwd, 50, rpm);
    }
    intakes.stop(brake);

    isRev = false;

    target = 75;

    drivePID(150, 100, 10);

    turnPID(-90, 100, 10);

    drivePID(500, 100, 10);

    shoot(2);
    */
  }

  else if (auton == 7)
  {

    turnPID(90, 100, 10);
    DT.stop(hold);
  }

  else if (auton == 11)
  {
    target = 85;

    inertial1.calibrate();

    intakes.spin(reverse, 600, rpm);

    wait(300, msec);

    drivePID(400, 100, 10);
    DT.stop(hold);

    wait(500, msec);

    intakes.stop();

    turnPID(-14, 50, 10);
    DT.stop(brake);

    intakes.stop();

    wait(500, msec);

    // shoot(3);

    wait(500, msec);

    turnPID(90, 50, 10);
    DT.stop(hold);

    wait(300, msec);

    intakes.spin(reverse, 200, rpm);

    drive(900, 100);
    DT.stop(hold);

    wait(300, msec);

    turnPID(-140, 50, 10);
    DT.stop(hold);

    // shoot(3);

    for (int i = 0; i < 3; i++)
    {
      waitUntil(flyWheel.velocity(pct) >= target - 2 && flyWheel.velocity(pct) <= target + 2);
      while (!(Distance.objectDistance(mm) < 20))
      {
        intakes.spin(fwd, 600, rpm);
      }
      intakes.stop();
    }

    wait(500, msec);

    turnPID(-90, 50, 10);
    DT.stop(hold);
  }
  else if (auton == 12)
  {
    target = 88;

    drivePID(-35, 50, 10);
    DT.stop(hold);

    wait(300, msec);

    wait(500, msec);
    while (Optical.hue() < 20 && Optical.hue() > 0)
    {
      intakes.spin(reverse, 35, rpm);
    }
    intakes.stop(hold);

    drivePID(65, 200, 10);
    DT.stop(hold);

    wait(300, msec);

    turnPID(15, 100, 10);
    DT.stop(hold);

    wait(300, msec);

    drive(600, 200);
    DT.stop(hold);

    wait(300, msec);

    drive(-159, 100);
    DT.stop(hold);

    wait(300, msec);

    turnPID(15, 100, 10);
    DT.stop(hold);

    wait(300, msec);

    for (int i = 0; i < 2; i++)
    {
      // waitUntil(flyWheel.velocity(pct) >= target - 2 && flyWheel.velocity(pct) <= target + 2);
      while (!(Distance.objectDistance(mm) < 20))
      {
        intakes.spin(fwd, 300, rpm);
      }
      intakes.stop(hold);
      wait(500, msec);
    }

    turnPID(5, 100, 10);
  }

  else if (auton == 15)
  {
  }

  else if (auton == 16)
  {

    target = 95;

    drive(-20, 25);
    DT.stop(hold);

    Brain.Screen.clearScreen();

    Brain.Screen.drawRectangle(0, 0, 50, 50, red);

    wait(600, msec);

    wait(500, msec);
    while (Optical.hue() < 20 && Optical.hue() > 0)
    {
      intakes.spin(reverse, 50, rpm);
    }
    intakes.stop(hold);

    drive(100, 50);
    DT.stop(hold);

    wait(300, msec);

    turnPID(-2.5, 15, 10);

    wait(500, msec);

    cv;

    intakes.spinFor(fwd, 300, deg, 600, rpm);

    wait(500, msec);

    cv;
    wait(1000, msec);

    intakes.spinFor(fwd, 300, deg, 600, rpm);

    turnPID(35, 15, 10);

    target = 90;

    wait(300, msec);

    drivePIDLong(600, 100, 10);

    intakes.spin(reverse, 200, rpm);

    wait(300, msec);

    drivePIDLong(500, 50, 10);

    wait(300, msec);

    turnPID(-21.5, 13, 10);

    intakes.stop();

    wait(500, msec);

    cv;

    intakes.spinFor(fwd, 300, deg, 600, rpm);

    wait(500, msec);

    cv;

    intakes.spinFor(fwd, 300, deg, 600, rpm);

    wait(1000, msec);

    cv;

    intakes.spinFor(fwd, 700, deg, 600, rpm);

    /*

    wait(300, msec);

    turnPID(25, 23, 20);

    wait(300, msec);

    intakes.spin(reverse, 200, rpm);

    drivePIDLong(1650, 257, 10);

    wait(300, msec);

    intakes.stop();

    turnPID(-90, 15, 20);

    wait(300, msec);

    drive(-230, 100);

    wait(500, msec);

    intakes.spinFor(reverse, 270, deg, 100, rpm);



    Brain.Screen.clearScreen();

    Brain.Screen.drawRectangle(0, 0, 50, 50, green);

    // DT.stop(hold);

    wait(300, msec);

    drivePID(600, 50, 10);
    DT.stop(hold);


    wait(300, msec);

    drivePID(-159, 50, 10);
    DT.stop(hold);

    wait(300, msec);

    turnPID(15, 25, 10);
    DT.stop(hold);

    wait(300, msec);

    for (int i = 0; i < 2; i++)
    {
      wait(500, msec);
      // waitUntil(flyWheel.velocity(pct) >= target - 2 && flyWheel.velocity(pct) <= target + 2);
      while (!(Distance.objectDistance(mm) < 20))
      {
        intakes.spin(fwd, 300, rpm);
      }
      intakes.stop(hold);
    }

    turnPID(-5, 10, 10);

    */
  }
  else if (auton == 17)
  {

    
  }
  else if(auton == 18) {
    target = 92;
    intakes.spin(reverse, 600, rpm);
    drivePID(400, 50, 10);

    wait(300, msec);

    turnPID(.75, 15, 10);

    intakes.stop();

    wait(1000, msec);

    cv;

    intakes.spinFor(fwd, 200, deg, 600, rpm);

    wait(1000, msec);

    cv;

    intakes.spinFor(fwd, 200, deg, 600, rpm);

    wait(2000, msec);

    waitUntil((flyWheel.velocity(pct) <= target + 2) && (flyWheel.velocity(pct) >= target - 2));

    intakes.spinFor(fwd, 300, deg, 600, rpm);

    wait(500, msec);

    turnTo(90, 25, 10);






  }
}