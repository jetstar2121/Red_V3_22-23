#include "v5.h"
#include "v5_vcs.h"

using namespace vex;

int bangBangFlywheel();

void drive(double dis, double speed);

void stop(brakeType BT);

void turnTo(double angle, double speed, double timeout);

void turn(vex::turnType dir, double angle, double speed);

void flywheelSpinCus(double speed);

void flywheelSpin100();

double constrainAngle(double x);

void limitSelector();
extern int limitSelect;

void colorIntakeRed();
void colorIntakeBlue();

extern bool status2;
extern bool status;

void toggle2();
void test();

void opticalSetup(int lightPower);

double turnAngle();

void stat1F();
void stat2F();

extern bool stat1;
extern bool stat2;
void reset();

extern int getFly();

extern double target;

extern void changeRed();
void regTurn(vex::turnType dir, double angle, double speed);
