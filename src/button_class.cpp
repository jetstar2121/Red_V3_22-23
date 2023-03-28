#include "vex.h"
#include <iostream>

// V5 Brain: 480 x 240 pixels

#define inArea                                                                 \
  (current_x >= begin_x && current_x <= end_x) &&                              \
      (current_y >= begin_y && current_y <= end_y)



// Pixel Math
int square_button::kPixel = 19;

bool square_button::isPressing() {
  current_x = Brain.Screen.xPosition();
  current_y = Brain.Screen.yPosition();

  if ((current_x >= begin_x && current_x <= end_x) &&
      (current_y >= begin_y && current_y <= end_y)) {
    return true;

  } else {
    return false;
  }
}

// Simple Constructor
square_button::square_button(int bx, int by, int w, int h) {
  square_button::isPressed = false;

  begin_x = bx;
  begin_y = by;
  width = w;
  height = h;

  end_x = begin_x + width;
  end_y = begin_y + height;
}

square_button::square_button() {
  square_button::isPressed = false;

  begin_x = 0;
  begin_y = 0;
  width = 0;
  height = 0;

  end_x = begin_x + width;
  end_y = begin_y + height;
}

// Text Constructor
square_button::square_button(int bx, int by, int w, int h, std::string txt) {
  square_button::isPressed = false;

  square_button::pixelLength = text.length() * square_button::kPixel;

  begin_x = bx;
  begin_y = by;
  width = w;
  height = h;

  end_x = begin_x + width;
  end_y = begin_y + height;

  square_button::text = txt;
}

void square_button::activate(vex::color off, vex::color on) {
  offColor = off;
  onColor = on;

  if (Brain.Screen.pressing()) {  

    current_x = Brain.Screen.xPosition();
    current_y = Brain.Screen.yPosition();

    if (inArea && isPressed == false) {
      isPressed = true;
      wait(300, msec);
    } else if (inArea && isPressed == true) {
      isPressed = false;
      wait(300, msec);
    }
  }
  if (isPressed) {

    Brain.Screen.drawRectangle(begin_x, begin_y, width, height, onColor);
    Brain.Screen.printAt(((begin_x + width) / 2), (begin_y + height) / 2,
                         text.c_str());
  } else {

    Brain.Screen.drawRectangle(begin_x, begin_y, width, height, offColor);
    Brain.Screen.printAt(((begin_x + width) / 2), (begin_y + height) / 2,
                         text.c_str());
  }
}
