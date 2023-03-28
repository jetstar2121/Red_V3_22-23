/*

#include <iostream>
#include "vex.h"


class Toggleswitch {
public:
  bool status;
  vex::pneumatics p;



  Toggleswitch(vex::pneumatics controlled_pnuematic) {
    p = controlled_pnuematic;
    status = false;
  }

  void activate(vex::controller::button switch_button) {
    if(switch_button.pressing()) {
        status =! status;
        wait(300, msec);
    }

    if(status == true) {
        p.open();
    }
    else {
        p.close();
    }
    
  }
  



};


//Create Toggleswitch Objects Here 
Toggleswitch endgame1(end1);

int toggleswitches() {


    return 10;
}

*/
