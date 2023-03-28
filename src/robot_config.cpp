#include "vex.h"
using namespace vex;

brain Brain;
controller Controller1;

inertial inertial1(PORT9);

//Right Side
motor front_right(PORT13, ratio18_1, true);
motor mid_right(PORT15, ratio18_1, false);
motor back_right(PORT14, ratio18_1, false);
motor_group rightDrive(front_right, mid_right, back_right);

//Left Side
motor front_left(PORT17, ratio18_1, true);
motor mid_left(PORT16, ratio18_1, true);
motor back_left(PORT18, ratio18_1, false);
motor_group leftDrive(front_left, mid_left, back_left);

//Drive Train
motor_group DT(front_left, front_right, back_left, back_right);

optical Optical(PORT4);

motor flyWheel(PORT8, ratio18_1, false);

motor intakes(PORT7, ratio18_1);

motor rollers(PORT8, ratio18_1);

pneumatics end1(Brain.ThreeWirePort.A);

pneumatics end2(Brain.ThreeWirePort.B);

pneumatics hood(Brain.ThreeWirePort.D);

distance Distance(PORT5);

limit limit1(Brain.ThreeWirePort.C);
limit limit2(Brain.ThreeWirePort.E);

