#include "vex.h"


double maxPower = 12;
double minPower = 1;
bool isRev = false;
double target = 0;

/*---------------------------------------------------------------------------*/
/*                                  Flywheel Bang-Bang                       */
/*---------------------------------------------------------------------------*/
int bangBangFlywheel() {
  //Just a variable containing the velocity of the flywheel
  double vel = flyWheel.velocity(pct);

  

  while(1) {
    //Updates vel at the begining of each run of the loop
    vel = flyWheel.velocity(pct);
    //If vel is less than desired velocity, then flywheel will accelerate at max power
      if(isRev) {
        flyWheel.spin(reverse, 50, rpm);
      }
      else if(vel < target  - (target * .05) ) {
        flyWheel.spin(fwd, maxPower, volt);
      }
      //If not, flywheel will accelerate with minimum power
      else if(vel > target + (target * .05)) {
        flyWheel.spin(fwd, minPower, volt);
      }
      else {
        flyWheel.spin(fwd, 6, volt);
      }

      //Waits 10 Milliseconds
      this_thread::sleep_for(10);
    
  }
  return 10;
}