#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <vector>

#include "auton.h"
#include "user_control.h"
#include "robot_config.h"
#include "functions.h"
#include "MiniPID.h"
#include "button_class.h"
#include "FlywheelBangBang.h"


#include "v5.h"
#include "v5_vcs.h"


#define waitUntil(condition)                                                   \
  do {                                                                         \
    wait(5, msec);                                                             \
  } while (!(condition))

#define repeat(iterations)                                                     \
  for (int iterator = 0; iterator < iterations; iterator++)